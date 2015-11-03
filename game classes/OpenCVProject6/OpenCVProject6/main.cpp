#include "opencv2/opencv.hpp"

using namespace cv;

Mat field(Mat playField,int x, int y)
{
	if (x<playField.cols/2)
		rectangle(playField, Point(30, y), Point(50,y+100), CV_RGB(0, 0, 255), 3);	
	else 
		rectangle(playField, Point(450, y), Point(470, y + 100), CV_RGB(0, 0, 255), 3);

	imshow("It moves!!!", playField);

	return playField;
}

Mat contour(Mat frame)
{
	cv::Mat result(frame.size(), CV_8U, cv::Scalar(255));
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(frame,
		contours, // a vector of contours
		CV_RETR_EXTERNAL, // retrieve the external contours
		CV_CHAIN_APPROX_NONE); // all pixels of each contours

	// Eliminate too short or too long contours
	int cmin = 150; // minimum contour length
	int cmax = 550; // maximum contour length
	int vec = 0;
	std::vector<std::vector<cv::Point>>::
		const_iterator itc = contours.begin();
	Mat playField = Mat::zeros(500, 500, 1);
	while (itc != contours.end()) {
		if (itc->size() < cmin || itc->size() > cmax)
			itc = contours.erase(itc);
		else{
			std::cout << itc->size()<<"\n";
			//find the bounding box for each contour
			cv::Rect r0 = cv::boundingRect(cv::Mat(contours[vec]));
			cv::rectangle(result, r0, cv::Scalar(0), 2);

			float radius;
			cv::Point2f center;
			cv::minEnclosingCircle(cv::Mat(contours[vec]), center, radius);
			cv::circle(result, cv::Point(center),
				static_cast<int>(radius), cv::Scalar(0), 2);
			

			
			++itc;
			++vec;
		}
			
	}

	// Draw black contours on a white image
	
	cv::drawContours(result, contours,
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
		//frame = imread("E:/conHand.jpg", 0);
		cap >> frame; // get a new frame from camera
		Mat colorFrame(frame);
		cvtColor(frame, frame, CV_RGB2GRAY);
		subtract(frame, BG, frame, noArray(), -1); //subtract foreground from background
		medianBlur(frame, frame, 5); //apply blur
		//cvtColor(frame, frame, CV_RGB2GRAY);
		threshold(frame, frame, 30, 255, CV_THRESH_BINARY); // threshold the image 
		//find(frame); //fing the location of the most white pixels
		frame=contour(frame);
		imshow("Frame", frame);
		if (waitKey(30) >= 0)
			break;
	}
	return 0;
}
