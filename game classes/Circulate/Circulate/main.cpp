#include "opencv2/opencv.hpp"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>


using namespace cv;
using namespace std;



void spinningCircles(int answersSize, int answers[], int fontFace, double fontScale, int thickness, int &baseline, double x, double y, int radius, double angle, double speed, Mat img){
	for (int i = 0; i < answersSize; i++)
	{
		//Initialzing the changing features inside the circle, such as text and position
		String text = to_string(answers[i]);
		Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
		baseline += thickness;

		//Creating matrixes for each of the different answers, to make them "rotateable". Currently not in use
		//Mat textImg = Mat::zeros(image.rows, image.cols, image.type());

		//Declaring the position of the answer
		x = radius*sin(angle * i + speed) + 500 / 2;
		y = radius*cos(angle * i + speed) + 500 / 2;
		Point answerPos(x, y);

		//Creating the numbers to be shown
		circle(img, answerPos, 20, Scalar::all(255), 1, 1);
		putText(img, text, Point(x - textSize.width / 2, y + textSize.height / 2), fontFace, fontScale, Scalar::all(255), 1, 8);
		//rotate(textImg, rotateSpeed, textImg, x, y);
		//Adds the new text image to the source image
		//image = image + textImg;
	}
}
void rotate(Mat src, double rotateAngle, Mat dst, int x, int y)
{
	Mat r = cv::getRotationMatrix2D(Point(x, y), rotateAngle, 1.0);
	warpAffine(src, dst, r, Size(500, 500));
}

int main(int, char)
{
	//Vari from other classes
	int radiusOuter = 150;
	int radiusInner = 100;
	int answers[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

	//Initializing all the variables
	double x, y;
	double angle;
	double speedRight = 0;
	double speedLeft = 0;
	double rotateSpeed = 0;
	int answersSize;

	//Declaring the array size, since c++ is stoopid
	//Also spacing numbers and delcaring start position
	answersSize = sizeof(answers) / sizeof(*answers);
	angle = 2*M_PI / answersSize;
	x = radiusInner*sin(angle * answersSize) + 500 / 2;
	y = radiusInner*cos(angle * answersSize) + 500 / 2;
	
	//Initializing the unchanging features of the text
	int fontFace = FONT_HERSHEY_SIMPLEX;
	double fontScale = 0.7;
	int thickness = 3;
	int baseline = 0;

	for (;;)
	{
		//Creating the matrix for the source image (The one getting shown)
		Mat image = Mat::zeros(500, 500, CV_8UC3);
		
		speedRight += 0.05;
		speedLeft -= 0.05;
		rotateSpeed += 2.8;
		
			//The inner circle
			spinningCircles(answersSize, answers, fontFace, fontScale, thickness, baseline, x, y, radiusInner, angle, speedRight, image);
			
			//The outer circle
			spinningCircles(answersSize, answers, fontFace, fontScale, thickness, baseline, x, y, radiusOuter, angle, speedLeft, image);		
		
		imshow("cool pic", image);
		waitKey(0);
	}
	return 0;
}