#include "opencv2/opencv.hpp"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <ctime>
#define _USE_MATH_DEFINES
#include <math.h>


using namespace cv;
using namespace std;

class GameContainer
{
	int tempcollide = 1;
	int tempSizeX = 800; // X-size of the gameboard
	int tempSizeY = 400; // Y-size of the gameboard
	double tempPlaceX, tempPlaceY; //The placement of objects on the gameboard
	int tempName; //The id of objects
	int tempeqState = 1; //The placement of the equation.
	int temphandState= 1; //Determines if the hand is open or closed. 0 for closed, 1 for open
	int temphandPosX = 50; //The X pos of the hand on our game
	int temphandPosy = 50; ////The Y pos of the hand on our game
	int tempcircleRadius = 100; //The radius for the circles
	int tempplayerColor = 1; //The player color determines the players team. 0 for white team and 1 for pink team
public:
	int collide = tempcollide;
	int sizeX = tempSizeX;
	int sizeY = tempSizeY;
	Mat image = Mat::zeros(sizeY, sizeX, CV_8UC3);
	int name = tempName;
	double placeX = tempPlaceX;
	double placeY = tempPlaceY;	
	int eqState = tempeqState;
	int handState = temphandState;
	int handPosX = temphandPosX;
	int handPosY = temphandPosy;
	int circleRadius = tempcircleRadius;
	int playerColor = tempplayerColor;
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
public:
	Mat image = Mat::zeros(sizeY, sizeX, CV_8UC3);

	void ansBoxLocation(int, int);
	void checkAnswer(int, int);
	void addPoint(int, int);
	
};

void AnswerBox::ansBoxLocation(int x, int y){
	rectangle(image, Point(y, x), Point(y+50, x+50), Scalar(255, 255, 255), 1);
	
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
	//Initializing the unchanging features of the text
	int fontFace = FONT_HERSHEY_SIMPLEX;
	double fontScale = 0.7;
	int thickness = 3;
	int baseline = 0;
	//Initialzing the changing features of the text
	String text = "u win";
	Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
	baseline += thickness;
	putText(image, text, Point(y - textSize.width / 2, x + textSize.height / 2), fontFace, fontScale, Scalar::all(255), 1, 8);
}

class EquationBox : GameContainer{
	
	bool tempVisibility = true;
	int temprNumber1, temprNumber2, temprTempNumber1;
	int tempyourAnswer, temprealAnswer;
	int temprOperator;
	String tempsolveableEquation;
public:
	int rNumber1 = temprNumber1;
	int rNumber2 = temprNumber2;
	int rTempNumber1 = temprTempNumber1;
	int yourAnswer = tempyourAnswer;
	int realAnswer = temprealAnswer;
	int rOperator = temprOperator;
	String solveableEquation = tempsolveableEquation;
	bool visibility = tempVisibility;
	//Functions
	void eqLocation();
	void pickEquation();
	void createEquation();
};

void EquationBox::eqLocation()
{
	if (eqState == 0) { //Unpicked state
		//placeX = homeX //Changes the equations location on the X-axis, to your own equation box
		//placeY = homeY //Changes the equations location on the Y-axis, to your own equation box
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

void EquationBox::createEquation(){
	srand((double)time(NULL));
	rNumber1 = rand() % 11;
	rNumber2 = rand() % 11;
	rOperator = rand() % 2;

	if (rNumber1 <= rNumber2){
		rTempNumber1 = rNumber1;
		rNumber2 = rNumber1;
		rNumber1 = rTempNumber1;
	}

	if (rOperator == 1){ //in here goes an equation with subtraction
		/*cout << "what is " << rNumber1 << "-" << rNumber2 << "?\n";
		solveableEquation = rNumber1 + rNumber2;
		realAnswer = rNumber1 - rNumber2;
		cout << solveableEquation;
		cin >> yourAnswer;
		if (realAnswer == yourAnswer)
		cout << "Correct!";
		else
		cout << "u suck";*/
		cout << "Subtraction of numbers \n";
	}
	else{ //In here goes an equation with addition
		/*cout << "what is " << rNumber1 << "+" << rNumber2 << "?\n";
		cin >> yourAnswer;
		realAnswer = rNumber1 + rNumber2;

		if (realAnswer == yourAnswer)
		cout << "Correct!";
		else
		cout << "u suck";*/
		cout << "Addition of numbers \n";
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
	void circulate(int, int);
	void drop();
	void grab();
};

void Answers::circulate(int x, int y){
	{
		//Vari from other classes
		int radiusOuter = sizeY / 2 - circleRadius;
		int radiusInner = sizeY / 2 - circleRadius*4;
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

	EquationBox equations;
	equations.eqLocation();
	equations.pickEquation();
	equations.createEquation();

	Circles circles;
	circles.createCircles();

	AnswerBox answerBoxP1;
	AnswerBox answerBoxP2;
	answerBoxP1.checkAnswer(gameContainer.sizeY / 2, 50);
	answerBoxP1.ansBoxLocation(gameContainer.sizeY / 2 - 25, 10);
	answerBoxP2.checkAnswer(gameContainer.sizeY / 2, gameContainer.sizeX - 50);
	answerBoxP2.ansBoxLocation(gameContainer.sizeY / 2 - 25, gameContainer.sizeX - 60);

	Answers answers;

	for (;;){
		Mat image = Mat::zeros(gameContainer.sizeY, gameContainer.sizeX, CV_8UC3);
		answers.circulate(100, 100);
		image = gameContainer.image + circles.image + answerBoxP1.image + answerBoxP2.image + answers.image;
		imshow("Gaaame", image);
		if (waitKey(30) >= 0){
			break;
		}
	}
}
