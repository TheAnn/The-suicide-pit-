#include "opencv2/opencv.hpp"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>


using namespace cv;
using namespace std;



void rotate(Mat src, double rotateAngle, Mat dst, int x, int y)
{
	Mat r = cv::getRotationMatrix2D(Point(x, y), rotateAngle, 1.0);
	warpAffine(src, dst, r, Size(500, 500));
}

int main(int, char)
{
	//Vari from other classes
	int radius = 150;
	int answers[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

	//Initializing all the variables
	double x, y;
	double angle;
	double speed = 0;
	double rotateSpeed = 0;
	int answersSize;

	//Declaring the array size, since c++ is stoopid
	//Also spacing numbers and delcaring start position
	answersSize = sizeof(answers) / sizeof(*answers);
	angle = 2*M_PI / answersSize;
	x = radius*sin(angle * answersSize) + 500 / 2;
	y = radius*cos(angle * answersSize) + 500 / 2;
	
	//Initializing the unchanging features of the text
	int fontFace = FONT_HERSHEY_SIMPLEX;
	double fontScale = 0.7;
	int thickness = 3;
	int baseline = 0;

	for (;;)
	{
		//Creating the matrix for the source image (The one getting shown)
		Mat image = Mat::zeros(500, 500, CV_8UC3);

		for (int i = 0; i < answersSize; i++)
		{
			//Initialzing the changing features inside the circle, such as text and position
			String text = to_string(answers[i]);
			Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
			baseline += thickness;

			//Creating matrixes for each of the different answers, to make them "rotateable". Currently not in use
			Mat textImg = Mat::zeros(image.rows, image.cols, image.type());

			//Declaring the position of the answer
			x = radius*sin(angle * i + speed) + 500 / 2;
			y = radius*cos(angle * i + speed) + 500 / 2;
			Point answerPos(x, y);

			//Creating the numbers to be shown
			circle(image, answerPos, 20, Scalar::all(255), 1, 1);
			putText(textImg, text, Point(x - textSize.width / 2, y + textSize.height / 2), fontFace, fontScale, Scalar::all(255), 1, 8);
			//rotate(textImg, rotateSpeed, textImg, x, y);
			//Adds the new text image to the source image
			image = image + textImg;
		}
		
		
		speed += 0.05;
		rotateSpeed += 2.8;
		
		imshow("cool pic", image);
		waitKey(0);
	}
	return 0;
}