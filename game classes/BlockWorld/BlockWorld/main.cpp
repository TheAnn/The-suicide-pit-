/*
Author: Atanas Nikolov, MTA15345
Email Adress: aniko14@student.aau.dk
Description: Math game test realm.
Update 1.0: Detect a hand and extract information such as size, gesture, and colour.
Update 1.1: Generate a number of blocks and move them by hand.
Update 1.2: Create a Pong class.
*/


#include "opencv2/opencv.hpp"

using namespace cv;
int sub_blue, sub_green;
Point2f center[10];
Mat background,
	frame,
	display_area;
int blob_state[10],
	blob_color[10];


class Pad{

	void draw();
	Point2f center;
};
class Block
{
public:
	Block(Point2f cent, int col);
	void draw(int n);
	
	void move(int m);

private:
	int color;
	Point2f	circle_center,
		goal_point;
	int object_color;


};

class ImageProcessing
{
public:
	void thresholding();																		//Remove the background and threshold the image.

	void contour();																				//Find the external contours.
	
	void eliminteContours();																	//Eliminate too short or too long contours and extract data from the rest
																								//Add more conditions to the if/else statement to remove noise.
		
	void blobArea();																			//Caculate area of the blob.
	
	void circularity();																			//Calculate the circularity of the blob.
	
	void blobColor();																			//Find the color of the blob 1-blue, 2-green, 3-red.

	void blobState();																			//Get the state of the blob.

	void gameCode();																			//Put game Code.

	void draw();																				//Draw contours.
	
	void whiteBalance(Point2f center);

	int getColor(Point2f center,int ch);
public:
	
	Mat thresholded,
		gray_frame,
		subtracted,
		contour_frame;
	std::vector<std::vector<cv::Point>> contours;
	int min_contour = 150,																		//Minimum size of the contour to be counted as objet of interest.
		max_contour = 350,																		//Maximum size of the contour to be counted as objet of interest.
		min_area = 2200,
		max_area = 5400,
		blob_area,
		vec;
	float radius;
	double rec_y,
		rec_x,
		rec_height,
		rec_width,
		blob_perimeter,
		blob_sqrt_area,
		blob_circularity,
		blob_circularity_precision = 1.2;														//Circularity threshold, determine state/gesture.



};



int main(int, char)
{
	Point2f a(200.0f, 200.0f), b(300.0f,300.0f);
	ImageProcessing IPGod;
	Block one(a,255), two(b,200);

	namedWindow("Game", CV_WINDOW_AUTOSIZE);
	waitKey(0);
	VideoCapture cap(2);
	if (!cap.isOpened())
		return -1;
	cap >> background;
	display_area = Mat::zeros(background.size(), background.type());
	cvtColor(background, background, CV_RGB2GRAY);
	for (;;)
	{

		cap >> frame;
		
		
		IPGod.thresholding();
		imshow("img", IPGod.thresholded);
		imshow("imgSub", IPGod.subtracted);
		IPGod.contour();
		IPGod.eliminteContours();
		display_area = Mat::zeros(frame.size(), frame.type());
		
		one.draw(0);
		two.draw(0);
		
		if (waitKey(30) >= 0){
			std::cout << "Sign\n";
			waitKey(0);
			IPGod.whiteBalance(center[0]);
			std::cout << "Second Sign\n";
		}
	}
	return 0;
}
//Pad
void Pad::draw()
{
	rectangle(display_area, center, Point(center.x + 10, center.y + 100), CV_RGB(0, 0, 255), 2);
}
//Block
Block::Block(Point2f cent,int col)
{
	color = col;
	circle_center = cent;
}
void Block::draw(int n)
{
	
	circle(display_area, circle_center, 25, CV_RGB(color,0,0), CV_FILLED);
	if (blob_state[n] == 1 && display_area.at<Vec3b>(center[n])[2] == color)
	{
		
		move(n);
	}
}
void Block::move(int m)
{
	
	circle_center = center[m];
}


//ImageProcessing

void ImageProcessing::gameCode()
{

}
void ImageProcessing::whiteBalance(Point2f center)
{
	sub_blue = 0;
	sub_green = 0;
	int color[3];
	for (int i = 0; i < 3; i++)
	{
		color[i] = getColor(center, i);
	}
	sub_blue = color[0] - color[2];
	sub_green = color[1] - color[2];
	std::cout <<"**************************************************"<< sub_blue << " " << sub_green <<" \n";

}
void ImageProcessing::eliminteContours()
{
	std::vector<std::vector<cv::Point>>::
		const_iterator itc(contours.begin());
	vec = 0;
	while (itc != contours.end())
	{
		if (itc->size() < min_contour || itc->size() > max_contour)
			itc = contours.erase(itc);
		else
		{
			//std::cout << vec << "\n";
			Rect r0(boundingRect(cv::Mat(contours[vec])));
			minEnclosingCircle(Mat(contours[vec]), center[vec], radius);

			rec_x = r0.x;
			rec_y = r0.y;
			rec_height = r0.height;
			rec_width = r0.width;

			blob_perimeter = itc->size();
			blobArea();
			if (blob_area < min_area || blob_area>max_area)
				itc = contours.erase(itc);
			else if (rec_width>150){
					itc = contours.erase(itc);
				}
				else{
				circularity();
				blobColor();
				center[blob_color[vec]+5] = center[vec];
				blobState();
				gameCode();
				draw();
				++vec;
				++itc;
			}
		}
	}
}
void ImageProcessing::thresholding()
{
	cvtColor(frame, gray_frame, CV_RGB2GRAY);

	subtract(gray_frame, background, subtracted, noArray(), -1);
	medianBlur(subtracted, subtracted, 5);
	threshold(subtracted, thresholded, 1, 255, CV_THRESH_BINARY);

}
void ImageProcessing::contour()
{
	contour_frame = thresholded.clone();
	findContours(contour_frame,
		contours,
		CV_RETR_EXTERNAL,
		CV_CHAIN_APPROX_NONE);

}
void ImageProcessing::blobArea()
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
int ImageProcessing::getColor(Point2f center,int ch)
{
	int color=0;
	for (int i = -1; i < 2; i++)
	{
		if (!center.x + i<0 || !center.x + i>640 || !center.y + i<0 || !center.y + i>480)
		color=+frame.at<Vec3b>(center.y-1, center.x+i)[ch]+
		frame.at<Vec3b>(center.y , center.x+i )[ch]+
		frame.at<Vec3b>(center.y +1, center.x+i)[ch];
	}

	return color;
}
void ImageProcessing::blobColor()
{
	int blue = getColor(center[vec],0)-sub_blue;
	int green = getColor(center[vec], 1)-sub_green;
	int red = getColor(center[vec], 2);


	std::cout << blue << " " << green << " " << red << " \n";
	if (blue > green)
		if (blue > red)
			blob_color[vec] = 1;
		else
			blob_color[vec] = 3;
	else if (green > red)
		blob_color[vec] = 2;
	else
		blob_color[vec] = 3;

}
void ImageProcessing::blobState()
{
	if (blob_circularity < blob_circularity_precision)
		blob_state[vec] = 1;
	else
		blob_state[vec] = 2;
}
void ImageProcessing::circularity()
{
	blob_sqrt_area = 2 * sqrt(3.14*blob_area);
	blob_circularity = blob_perimeter / blob_sqrt_area;
}
void ImageProcessing::draw()
{
	std::string vecS = std::to_string(blob_color[vec]);

	Mat result(frame.size(), CV_8UC3, cv::Scalar(255, 255, 255));
	if (blob_state[vec] == 1){
		//rectangle(display_area, center[vec], Point(center[vec].x + 1, center[vec].y + 1), CV_RGB(0, 255, 0), 10);
		putText(display_area, vecS, center[vec], FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255, 255, 255), 3, 8, false);
		//std::cout << blob_color[vec];
	}
	else{
		//rectangle(display_area, center[vec], Point(center[vec].x + 1, center[vec].y + 1), CV_RGB(0, 0, 255), 10);
		putText(display_area, vecS, center[vec], FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255, 0, 0), 3, 8, false);
		//std::cout << blob_color[vec];
	}

	drawContours(result, contours,
		-1,
		cv::Scalar(0),
		1);
	imshow("Game", display_area);
	

}
