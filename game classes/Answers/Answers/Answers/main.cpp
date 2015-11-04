#include "opencv2/opencv.hpp"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <ctime>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
using namespace cv;

class GameContainer
{
	Mat image1 = imread("C:/images/mathers.png", 1);
	int tempcollide = 1;
	int tempSizeX = image1.cols; // X-size of the gameboard
	int tempSizeY = image1.rows; // Y-size of the gameboard
	double tempPlaceX, tempPlaceY; //The placement of objects on the gameboard
	int tempName; //The id of objects
	int tempeqState = 1; //The placement of the equation.
	int temphandState = 1; //Determines if the hand is open or closed. 0 for closed, 1 for open
	int temphandPosX = 50; //The X pos of the hand on our game
	int temphandPosy = 50; ////The Y pos of the hand on our game
	int tempcircleRadius = 100; //The radius for the circles
	int tempplayerColor = 1; //The player color determines the players team. 0 for white team and 1 for pink team
public:
	int collide = tempcollide;
	int sizeX = tempSizeX;
	int sizeY = tempSizeY;
	int name = tempName;
	Mat image = Mat::zeros(sizeY, sizeX, CV_8UC3);
	//Mat image = Mat::zeros(sizeY, sizeX, CV_8UC3);
	double placeX = tempPlaceX;
	double placeY = tempPlaceY;
	int eqState = tempeqState;
	int handState = temphandState;
	int handPosX = temphandPosX;
	int handPosY = temphandPosy;
	int circleRadius = tempcircleRadius;
	int playerColor = tempplayerColor;
};

class Answers : GameContainer{
	double tempx, tempy;
	double tempangle;
	double tempspeedRight = 0;
	double tempspeedLeft = 0;
	double temprotateSpeed = 0;
	int tempanswersSize;
	double circleRadius = sizeY / 31.25;
	bool tempholding; //This bool should be taken from the grab() function
public:
	Mat image = Mat::zeros(sizeY, sizeX, CV_8UC3);
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
		double radiusOuter = sizeY / 2 - circleRadius * 6;
		double radiusInner = sizeY / 2 - circleRadius * 9;
		int answers[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

		//Declaring the array size, since c++ is stoopid
		//Also spacing numbers and delcaring start position
		answersSize = sizeof(answers) / sizeof(*answers);
		angle = 2 * M_PI / answersSize;

		//Initializing the unchanging features of the text
		int fontFace = FONT_HERSHEY_SIMPLEX;
		double fontScale = sizeY / 625.0;
		int thickness = 3;
		int baseline = 0;

		Mat newImage = Mat::zeros(sizeY, sizeX, CV_8UC3);
		image = newImage;

		speedRight += 0.02;
		speedLeft -= 0.02;
		rotateSpeed += 2.8;

		//The inner circle
		singleCircle(answersSize, answers, fontFace, fontScale, thickness, baseline, x, y, radiusInner, angle, speedRight, image);

		//The outer circle
		singleCircle(answersSize, answers, fontFace, fontScale, thickness, baseline, x, y, radiusOuter, angle, speedLeft, image);

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
		x = radius*sin(angle * i + speed) + sizeX / 2;
		y = radius*cos(angle * i + speed) + sizeY / 2;
		Point answerPos(x, y);

		//Creating the numbers to be shown
		circle(image, answerPos, circleRadius, Scalar(0, 0, 255), 1, 1);
		putText(image, text, Point(x - textSize.width / 2, y + textSize.height / 2), fontFace, fontScale, Scalar::all(255), 1, 8);
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
	if (collide % 2 == 1){
		//id.answer.posX = hand.x
		//id.answer.posY = hand.y
		holding = true;
	}
}


void Answers::rotate(Mat src, double rotateAngle, Mat dst, int x, int y)
{
	Mat r = cv::getRotationMatrix2D(Point(x, y), rotateAngle, 1.0);
	warpAffine(src, dst, r, Size(x, y));
}

int main(int, char)
{
	GameContainer gameContainer;

	Answers answers;


	for (;;){
		Mat image = Mat::zeros(gameContainer.sizeY, gameContainer.sizeX, CV_8UC3);
		answers.circulate(100, 100);
		image = gameContainer.image + answers.image;
		imshow("Gaaame", image);
		if (waitKey(30) >= 0){
			break;
		}
	}
}