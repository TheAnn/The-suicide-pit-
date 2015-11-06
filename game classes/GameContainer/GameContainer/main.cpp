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
	int temphandState= 1; //Determines if the hand is open or closed. 0 for closed, 1 for open
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

class Circles : GameContainer{
	//Initiate all the variables and construcer in this class
public:
	Mat image = Mat::zeros(sizeY, sizeX, CV_8UC3);
	int radiusIn =  sizeY / 3;
	int radiusMed = sizeY / 2.35;
	int radiusOut = sizeY / 2;
	void createCircles(){
		circle(image, Point(sizeX / 2, sizeY / 2), radiusIn, Scalar(255, 255, 255), 1, 8);
		circle(image, Point(sizeX / 2, sizeY / 2), radiusMed, Scalar(255, 255, 255), 1, 8);
		circle(image, Point(sizeX / 2, sizeY / 2), radiusOut, Scalar(255, 255, 255), 1, 8);	
	};
};

class AnswerBox : GameContainer{
	//Initiate all the variables and construcer in this class
	double tempboxSize = 648/7.2;
public:
	Mat image = Mat::zeros(sizeY, sizeX, CV_8UC3);
	double boxSize = tempboxSize;

	void ansBoxLocation(int, int, int, int);
	void checkAnswer(int, int);
	void addPoint(int, int);
	
};

void AnswerBox::ansBoxLocation(int x, int y, int x1, int y1){
	rectangle(image, Point(y, x), Point(y1, x1), Scalar(255, 255, 255), 1);
	
}

void AnswerBox::checkAnswer(int x, int y){
	int objIDX;
	int objIDY;
	//if (objIDX > y && objIDY > x && objIDX < y && objIDY < x){
		//if (yourAnswer == realAnswer){
			//display checkmark
			addPoint(x, y);
		//} else
			//display cross
	//}
}

void AnswerBox::addPoint(int x, int y){
	//Initialzing the changing features of the text
	String text = "u win";
	Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
	baseline += thickness;
	putText(image, text, Point(y - textSize.width / 2, x + textSize.height / 2), fontFace, fontScale, Scalar::all(255), 1, 8);
}

class EquationBox : GameContainer{
	
	bool tempVisibility = true;
	int temprNumber1, temprNumber2, temprTempNumber1;
	int tempyourAnswer;
	
	int temprOperator;
	String tempsolveableEquation;

	int tempwidth;
	int tempheight;
	int tempequationSize;
	int temprealAnswer;

	int y2temp = 100;

public:
	int rNumber1 = temprNumber1;
	int rNumber2 = temprNumber2;
	int rTempNumber1 = temprTempNumber1;
	int yourAnswer = tempyourAnswer;
	int y2 = y2temp;

	int rOperator = temprOperator;
	int realAnswer[3];

	int width = tempwidth;
	int height = tempheight;
	int equationSize = tempequationSize;
	int equations[3];

	String solveableEquation = tempsolveableEquation;
	bool visibility = tempVisibility;
	Mat image = Mat::zeros(sizeY, sizeX, CV_8UC3);
	//Functions
	void eqLocation(int, int, int, int, int, int);
	void pickEquation();
	void createEquation(int equationSize, int equations[], int fontFace, double fontScale, int thickness, int &baseline, int x, int y, int y2, int width, int height, Mat img);
};

void EquationBox::eqLocation(int placeY, int placeX, int homeY, int homeX, int enemyY, int enemyX)
{
	if (eqState == 0) { //Unpicked state
		createEquation(equationSize, equations, fontFace, fontScale, thickness, baseline, placeX, placeY, width, height, y2, image);
		//placeX = homeX; //Changes the equations location on the X-axis, to your own equation box
		//placeY = homeY;//Changes the equations location on the Y-axis, to your own equation box
		visibility = true; //Determines if the box is visible on the board
		cout << "State 0 achived. gz \n";
	}
	else if (eqState == 1){ //Picked state
		//placeX = enemyX //Changes the equations location on the X-axis, to your enemies "solving box"
		//placeY = enemyY //Changes the equations location on the Y-axis, to your enemies "solving box"
		visibility = true; //Determines if the box is visible on the board
		cout << "State 1 achived. gz \n";
	}
	else if (eqState == 2){ //Queued state
		//placeX = enemyX //Changes the equations location on the X-axis, to your enemies "solving box"
		//placeY = enemyY //Changes the equations location on the Y-axis, to your enemies "solving box"
		visibility = false; //Determines if the box is visible on the board
		cout << "State 2 achived. gz \n";
	}
}

void EquationBox::pickEquation(){
	if (collide % 2 == 0){
		//if (hand.pColor == eq.pColor) //Checks if the color on the hand picking and the equation adds up
		eqState = 2;
	}
}

void EquationBox::createEquation(int equationSize, int equations[], int fontFace, double fontScale, int thickness, int &baseline, int x, int y, int y2, int width, int height, Mat img){
	equationSize = sizeof(equations) / sizeof(*equations);
	srand(time(NULL));
	
	for (int i = 0; i <= equationSize; i++)
	{
		rNumber1 = rand() % 11;
		rNumber2 = rand() % 11;
		rOperator = rand() % 2;
		
		y2 = y;
		y = y + 50 * i;
		
		if (rNumber1 <= rNumber2){
			rTempNumber1 = rNumber1;
			rNumber2 = rNumber1;
			rNumber1 = rTempNumber1;
		}

		if (rOperator == 0){ //in here goes an equation with subtraction
			String text = to_string(rNumber1) + "-" + to_string(rNumber2);
			putText(image, text, Point(x, y), fontFace, fontScale, Scalar::all(255), 1, 8);
			
			realAnswer[i] = rNumber1 - rNumber2;
			cout << "Subtraction of numbers \n";
		}
		else if (rOperator == 1){ //In here goes an equation with addition
			String text = to_string(rNumber1) + "+" + to_string(rNumber2);
			putText(image, text, Point(x, y), fontFace, fontScale, Scalar::all(255), 1, 8);

			realAnswer[i] = rNumber1 + rNumber2;
			cout << "Addition of numbers \n";
		}
		y = y2;
	}
}


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
	void circulate(int, int, int, int, int);
	void drop();
	void grab();
};

void Answers::circulate(int x, int y, int ans1, int ans2, int ans3){
	{
		//Vari from other classes
		double radiusOuter = sizeY / 2 - circleRadius*6;
		double radiusInner = sizeY / 2 - circleRadius*9;
		int answers[5] = { ans1, ans2, ans3, 4, 5};

		//Declaring the array size, since c++ is stoopid
		//Also spacing numbers and delcaring start position
		answersSize = sizeof(answers) / sizeof(*answers);
		angle = 2 * M_PI / answersSize;
		
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
	//if (collide != objectID){ //Checks if the collide function stopped returning an object ID
		//checkAnswer(); // Runs the checkAnswer function to see if the object is within the answer box.
		holding = false;
	//}
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
	GameContainer gameContainer;

	MathTimer mathTimerP1;
	MathTimer mathTimerP2;
	

	EquationBox equations;
	equations.eqLocation(100,50,0,0,0,0);
	equations.pickEquation();

	AnswerBox answerBoxP1;
	AnswerBox answerBoxP2;
	answerBoxP1.ansBoxLocation(gameContainer.sizeY / 2 - answerBoxP1.boxSize / 2, gameContainer.sizeX / 32.4, gameContainer.sizeY / 2 + answerBoxP1.boxSize / 2, answerBoxP1.boxSize + gameContainer.sizeX / 32.4);
	
	answerBoxP2.ansBoxLocation(gameContainer.sizeY / 2 - answerBoxP1.boxSize / 2, gameContainer.sizeX - gameContainer.sizeX / 32.4 - answerBoxP1.boxSize, gameContainer.sizeY / 2 + answerBoxP1.boxSize / 2, gameContainer.sizeX - gameContainer.sizeX / 32.4);

	Answers answers;

	for (;;){
		Mat image = Mat::zeros(gameContainer.sizeY, gameContainer.sizeX, CV_8UC3);
		answers.circulate(100, 100, equations.realAnswer[0], equations.realAnswer[1], equations.realAnswer[2]);
		//mathTimerP1.startTimer(gameContainer.sizeX / 4, gameContainer.sizeY / 4);
		//mathTimerP2.startTimer(gameContainer.sizeX - gameContainer.sizeX / 4, gameContainer.sizeY - gameContainer.sizeY / 4);
		image = gameContainer.image + answerBoxP1.image + answerBoxP2.image + answers.image + mathTimerP1.image + mathTimerP2.image + equations.image;
		imshow("Gaaame", image);
		if (waitKey(30) >= 0){
			break;
		}
	}
}
