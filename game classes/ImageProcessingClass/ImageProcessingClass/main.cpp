/*
Author: Atanas Nikolov, MTA15345
Email Adress: aniko14@student.aau.dk
Description: Image processing program, using openCV libraries, to detect a hand and extract information such as size, gesture, and colour. 
*/


#include "opencv2/opencv.hpp"

using namespace cv;


class ImageProcessing
{
public:
			
	void thresholding()
	{
		cvtColor(frame, gray_frame, CV_RGB2GRAY);

		subtract(gray_frame, background, subtracted, noArray(), -1);
		medianBlur(subtracted, subtracted, 5);
		threshold(subtracted, thresholded, 30, 255, CV_THRESH_BINARY);
	}
	void contour()																			//find the external contours 
	{
		contour_frame = thresholded.clone();
		findContours(contour_frame,
			contours,
			CV_RETR_EXTERNAL,
			CV_CHAIN_APPROX_NONE);


	}
	void eliminteContours()																	//eliminate too short or too long contours and extract data from the rest
	{																						//Add more conditions to the if/else statement to remove noise
		std::vector<std::vector<cv::Point>>::
			const_iterator itc(contours.begin());
		int vec = 0;
		t = 0;
		while (itc != contours.end())
		{
			if (itc->size() < min_contour || itc->size() > max_contour)
				itc = contours.erase(itc);
			else
			{
				Rect r0(boundingRect(cv::Mat(contours[vec])));
				minEnclosingCircle(Mat(contours[vec]), center, radius);

				rec_x = r0.x;
				rec_y = r0.y;
				rec_height = r0.height;
				rec_width = r0.width;
				blobArea();
				if (blob_area < 2200||blob_area>6000)
					itc = contours.erase(itc);
				else{
					blob_perimeter = itc->size();
					circularity();
					blobColor();
					blobState();
					gameCode();
					draw();
					++vec;
					++itc;
				}
			}
		}
	}


	void blobArea()																			//caculate area of the blob
	{
		double yMax = rec_y + rec_height - 1;
		double xMax = rec_x + rec_width - 1;
		blob_area = 1;
		for (int y = rec_y; y < yMax; y++)
		{
			for (int x = rec_x; x < xMax; x++)
			{
				if (thresholded.at<unsigned char>(y, x)>0)
				{
					blob_area++;

				}
			}
		}
	}

	void circularity()																		//calculate the circularity of the blob
	{
		blob_sqrt_area = 2 * sqrt(3.14*blob_area);
		blob_circularity = blob_perimeter / blob_sqrt_area;
	}

	void blobColor()																		//find the color of the blob 1-blue, 2-green, 3-red
	{
		int blue = frame.at<Vec3b>(center.y, center.x)[0];
		int green = frame.at<Vec3b>(center.y, center.x)[1];
		int red = frame.at<Vec3b>(center.y, center.x)[2];

		if (blue > green)
			if (blue > red)
				blob_color = 1;
			else
				blob_color = 3;
		else if (green > red)
			blob_color = 2;
		else
			blob_color = 3;

	}

	void blobState()																		//get the state of the blob
	{
		if (blob_circularity > blob_circularity_precision)
			blob_state = 1;
		else
			blob_state = 2;
	}

	void gameCode()																			//Put game Code
	{
		
		std::cout << t << "\n";
		std::cout << blob_area<< "\n";
		std::cout << blob_circularity << "\n";
		std::cout << "\n";
		std::cout << "\n";
		t++;
	}
	void draw()																				//Draw contours
	{
		namedWindow("Result", CV_WINDOW_AUTOSIZE);
		Mat result(frame.size(), CV_8UC3, cv::Scalar(255,255,255));
		if (blob_state==1)
			rectangle(result, center, Point(center.x+1,center.y+1), CV_RGB(255, 0, 0), 10);
		else 
			rectangle(result, center, Point(center.x + 1, center.y + 1), CV_RGB(0, 0, 255), 10);

		drawContours(result, contours,
			-1, 
			cv::Scalar(0), 
			1);
		resize(result, result, cvSize(1920, 960));
		imshow("Result", result);
		
	}

	Mat frame,
		background,
		thresholded,
		gray_frame,
		subtracted,
		contour_frame;
	Point2f center;
	std::vector<std::vector<cv::Point>> contours;
	int min_contour=100,																	//Minimum size of the contour to be counted as objet of interest
		max_contour=600,																	//Maximum size of the contour to be counted as objet of interest
		min_area=2200,																		//Minimum area of the blob to be counted as objet of interest
		max_area=6000,																		//Maximum area of the blob to be counted as objet of interest
		blob_area,
		blob_color,
		blob_state,
		t;
	float radius;
	double rec_y,
		   rec_x,
		   rec_height,
		   rec_width,
		   blob_perimeter, 
		   blob_sqrt_area, 
		   blob_circularity,
		   blob_circularity_precision=1.0;													//Circularity threshold, determine state/gesture



};

int main(int, char)
{
	ImageProcessing IPGod;
	VideoCapture cap(2); 
	if (!cap.isOpened()) 
		return -1;
	cap >> IPGod.background;
	cvtColor(IPGod.background, IPGod.background, CV_RGB2GRAY);
	for (;;)
	{
		cap >> IPGod.frame;
		IPGod.thresholding();
		IPGod.contour();
		IPGod.eliminteContours();


		if (waitKey(30) >= 0)
			break;
	}
	return 0;
}