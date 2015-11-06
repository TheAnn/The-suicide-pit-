#include "opencv2/opencv.hpp"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <ctime>
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctime>
#include <Windows.h>


using namespace cv;
using namespace std;

class GameContainer
{
	Mat image1 = imread("C:/images/mathers.png", 1);
	int tempcollide = 1;
	int tempSizeX = image1.cols; // X-size of the gameboard
	int tempSizeY = image1.rows; // Y-size of the gameboard
	double tempPlaceX, tempPlaceY; //The placement of objects on the gameboard
	int tempName; //The id of objects
	int tempeqState = 0; //The placement of the equation.
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
	Mat image = imread("C:/images/mathers.png", 1);
	//Mat image = Mat::zeros(sizeY, sizeX, CV_8UC3);
	double placeX = tempPlaceX;
	double placeY = tempPlaceY;
	int eqState = tempeqState;
	int handState = temphandState;
	int handPosX = temphandPosX;
	int handPosY = temphandPosy;
	int circleRadius = tempcircleRadius;
	int playerColor = tempplayerColor;


	//Initializing the unchanging features of the text
	int fontFace = FONT_HERSHEY_SIMPLEX;
	int thickness = 3;
	int baseline = 0;
	double fontScale = sizeY / 625.0;

};

class MathTimer : GameContainer{
public:
	Mat image = Mat::zeros(sizeY, sizeX, CV_8UC3);
	void startTimer(int y, int x){
		for (int k = 0; k<11; k++) {
			String text = to_string(k);
			Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
			baseline += thickness;
			Mat newImage = Mat::zeros(sizeY, sizeX, CV_8UC3);
			image = newImage;;
			putText(image, text, Point(y - textSize.width / 2, x + textSize.height / 2), fontFace, fontScale, Scalar::all(255), 1, 8);
			cout << k;
		}
	};
};
int main(int, char)
{
	MathTimer mathTimerP1;
	mathTimerP1.startTimer(100,100);
	imshow("Gaaame", mathTimerP1.image);
	waitKey(0);
	return(0);
}

	