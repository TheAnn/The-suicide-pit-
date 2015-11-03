#include "opencv2/opencv.hpp"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>


using namespace cv;
using namespace std;

class Answers{
	double tempx, tempy;
	double tempangle;
	double tempspeedRight = 0;
	double tempspeedLeft = 0;
	double temprotateSpeed = 0;
	int tempanswersSize;
	bool tempholding; //This bool should be taken from the grab() function
public:
	bool holding = tempholding; //This bool should be taken from the grab() function
	double x = tempx;
	double y = tempy;
	double angle = tempangle;
	double speedRight = tempspeedRight;
	double speedLeft = tempspeedLeft;
	double rotateSpeed = temprotateSpeed;
	int answersSize = tempanswersSize;
	//void spinningCircles(int, int answers[], int, double, int, int &baseline, double, double, int, double, double, Mat);
	void singleCircle(int answersSize, int answers[], int fontFace, double fontScale, int thickness, int &baseline, double x, double y, int radius, double angle, double speed, Mat img);
	void rotate(Mat src, double rotateAngle, Mat dst, int x, int y);
	void circulate(int, int);
	void drop();
	void grab();
};

void Answers::circulate(int x, int y){
	{
		//Vari from other classes
		int radiusOuter = 150;
		int radiusInner = 100;
		int answers[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

		//Declaring the array size, since c++ is stoopid
		//Also spacing numbers and delcaring start position
		answersSize = sizeof(answers) / sizeof(*answers);
		angle = 2 * M_PI / answersSize;
		x = radiusInner*sin(angle * answersSize) + 500 / 2;
		y = radiusInner*cos(angle * answersSize) + 500 / 2;

		//Initializing the unchanging features of the text
		int fontFace = FONT_HERSHEY_SIMPLEX;
		double fontScale = 0.7;
		int thickness = 3;
		int baseline = 0;

		Mat image = Mat::zeros(500, 500, CV_8UC3);

		for (;;)
		{
			//Creating the matrix for the source image (The one getting shown)
			

			speedRight += 0.02;
			speedLeft -= 0.02;
			rotateSpeed += 2.8;

			//The inner circle
			singleCircle(answersSize, answers, fontFace, fontScale, thickness, baseline, x, y, radiusInner, angle, speedRight, image);

			//The outer circle
			singleCircle(answersSize, answers, fontFace, fontScale, thickness, baseline, x, y, radiusOuter, angle, speedLeft, image);

			imshow("cool pic", image);

			if (waitKey(30) >= 0){
				break;
			}
		}
	}
}

void Answers::singleCircle(int answersSize, int answers[], int fontFace, double fontScale, int thickness, int &baseline, double x, double y, int radius, double angle, double speed, Mat img){
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
		circle(img, answerPos, 20, Scalar(0, 0, 255), 1, 1);
		putText(img, text, Point(x - textSize.width / 2, y + textSize.height / 2), fontFace, fontScale, Scalar::all(255), 1, 8);
		//rotate(textImg, rotateSpeed, textImg, x, y);
		//Adds the new text image to the source image
		//image = image + textImg;
	}
}

void Answers::drop(){
	if (holding == true)
	{
		//if (collide != objectID) //Checks if the collide function stopped returning an object ID
			//checkAnswer(); // Runs the checkAnswer function to see if the object is within the answer box.
			holding = false;
	}
}

void Answers::grab(){
	int collide = 1;
	if (collide % 2 == 1){
		//id.answer.posX = hand.x
		//id.answer.posY = hand.y
		holding = true;
	}
}


void Answers::rotate(Mat src, double rotateAngle, Mat dst, int x, int y)
{
	Mat r = cv::getRotationMatrix2D(Point(x, y), rotateAngle, 1.0);
	warpAffine(src, dst, r, Size(500, 500));
}

int main(int, char){
	Answers answers;
	answers.circulate(0, 0);
	return 0;
}