#include "opencv2/opencv.hpp"

using namespace cv;


int handCol(Mat colFrame, int x,int y)
{
	int color=0;

	
	imshow("rng", colFrame);
	int blue =colFrame.at<Vec3b>(y,x)[0];
	int green = colFrame.at<Vec3b>(y, x)[1];
	int red = colFrame.at<Vec3b>(y, x)[2];

	if (blue > green)
		if (blue > red)
			color = 1;
		else
			color = 3;
	else if (green > red)
		color = 2;
	else
		color = 3;

	std::cout << color << "\n";
	return color;
}

int handArea(Mat frame,int xCoor,int yCoor,double height,double width)
{
	int area=0;
	double yMax=yCoor + height-1;
	double xMax=xCoor + width-1;
	for (int y=yCoor; y < yMax; y++)
	{
		for (int x=xCoor; x < xMax; x++)
		{
			if (frame.at<unsigned char>(y, x)>0)
			{
				area++;
				
			}
		}
	}
	
	return area;
}

bool circul(double radius, double size)
{
	double cirSize=2*sqrt(3.14*size);
	double cirPercent=size / cirSize;
	//std::cout <<cirPercent<<" "<< size << " "<<cirSize<<"\n";
	double precision=18;
	if (cirPercent > precision)								//change to increase precision of gesture
		return true;
	else
		return false;
	return false;
}

Mat contour(Mat frame,Mat colFrame)
{
	Mat seg=frame.clone();

	Mat result(frame.size(), CV_8U, cv::Scalar(255));
	std::vector<std::vector<cv::Point>> contours;
	
	findContours(frame,
		contours, // a vector of contours
		CV_RETR_EXTERNAL, // retrieve the external contours
		CV_CHAIN_APPROX_NONE); // all pixels of each contours
	// Eliminate too short or too long contours
	int cmin=150; // minimum contour length
	int cmax=550; // maximum contour length
	int vec=0;
	std::vector<std::vector<cv::Point>>::
		const_iterator itc( contours.begin());
	while (itc != contours.end())
	{
		if (itc->size() < cmin || itc->size() > cmax)
			itc = contours.erase(itc);
		else
		{
			//find the bounding box for each contour
			Rect r0( boundingRect(cv::Mat(contours[vec])));
			rectangle(result, r0, cv::Scalar(0), 2);

			float radius;
			Point2f center;																//HAND CENTER HERE (x, y)
			minEnclosingCircle(Mat(contours[vec]), center, radius);
			circle(result, Point(center),
				static_cast<int>(radius), cv::Scalar(0), 2);
			
			int hColor = handCol(colFrame, center.x, center.y);
			int hArea=handArea(seg, r0.x, r0.y, r0.height, r0.width);
			
			bool handState=circul(radius, hArea);										//HAND STATE HERE
			if (handState)
			{
				rectangle(seg, Point(0,0), Point(100,100), CV_RGB(0, 0, 255), 3);
			}
			else
			{
				rectangle(seg, Point(200, 200), Point(100, 100), CV_RGB(0, 0, 255), 3);
			}
			//(seg, Point(r0.x, r0.y), Point(r0.x + r0.width, r0.y + r0.height), CV_RGB(0, 0, 255), 3);
			

			++itc;
			++vec;
		}
			
	}

	// Draw black contours on a white image
	//imshow("Original", colFrame);
	//imshow("Segmented", seg);
	drawContours(result, contours,
		-1, // draw all contours
		cv::Scalar(0), // in black
		1); // with a thickness

		
	return result;
}

int main(int, char)
{
	VideoCapture cap(2); // open the default camera
	if (!cap.isOpened()) // check if we succeeded
		return -1;
	Mat BG;

	cap >> BG; //capture a background frame
	cvtColor(BG, BG, CV_RGB2GRAY);
	for (;;)
	{
		Mat frame;

		cap >> frame; // get a new frame from camera
		Mat colFrame=frame.clone();

		cvtColor(frame, frame, CV_RGB2GRAY);
		
		subtract(frame, BG, frame, noArray(), -1); //subtract foreground from background
		medianBlur(frame, frame, 5); //apply blur
		threshold(frame, frame, 30, 255, CV_THRESH_BINARY); // threshold the image 

		Mat result(contour(frame,colFrame));
		imshow("Frame", result);
		if (waitKey(30) >= 0)
			break;
	}
	return 0;
}
