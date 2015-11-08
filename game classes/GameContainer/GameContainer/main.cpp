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
	Mat image1 = Mat::zeros(400,1000, CV_8UC3);
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
	Mat image = Mat::zeros(sizeY, sizeX, CV_8UC3);
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
	int tempR = 255;
	int tempG = 255;
	int tempB = 255;
	int tempFill = 1;
	int tempScore = 0;
	double tempboxSize = 648/7.2;
public:
	int r = tempR;
	int g = tempG;
	int b = tempB;
	int fill = tempFill;
	int score = tempScore;
	Mat image = Mat::zeros(sizeY, sizeX, CV_8UC3);
	double boxSize = tempboxSize;

	void ansBoxLocation(int, int);
	void checkAnswer(int, int);
	void addPoint(int, int);
	
};

void AnswerBox::ansBoxLocation(int x, int y){
	
	rectangle(image, Point(y, x), Point(y + boxSize, x + boxSize), Scalar(b, g, r), fill);
	checkAnswer(x, y);
	
}

void AnswerBox::checkAnswer(int x, int y){
	int objIDX;
	int objIDY;
	//if (objIDX > y && objIDY > x && objIDX < y && objIDY < x){
		//if (yourAnswer == realAnswer){
			//r = 0;
			//b = 0;
			//fill = -1;
			addPoint(x, y);
		//} else
			//g = 0;
			//b = 0;
			//fill = -1;
	//}
}

void AnswerBox::addPoint(int x, int y){
	//Initialzing the changing features of the text
	score = 1;
	y += 50;
	x += -100;
	if (score == 1){
		String text = to_string(score) + " Point";
		Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
		baseline += thickness;
		putText(image, text, Point(y - textSize.width / 2, x + textSize.height / 2), fontFace, fontScale, Scalar::all(255), 1, 8);
	}
	else{
		String text = to_string(score) + " Points";
		Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
		baseline += thickness;
		putText(image, text, Point(y - textSize.width / 2, x + textSize.height / 2), fontFace, fontScale, Scalar::all(255), 1, 8);
	}
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
	int realAnswer[6];

	int width = tempwidth;
	int height = tempheight;
	int equationSize = tempequationSize;
	String equations[6];

	String solveableEquation = tempsolveableEquation;
	bool visibility = tempVisibility;
	Mat image = Mat::zeros(sizeY, sizeX, CV_8UC3);
	//Functions
	void eqLocation(int, int, int, int, int, int, int);
	void pickEquation();
	void createEquation(int, int, int x, int y, int y2, Mat img);
};

void EquationBox::eqLocation(int eqStart, int placeY, int placeX, int homeY, int homeX, int enemyY, int enemyX)
{
	
	createEquation(eqStart, equationSize / 2, placeX, placeY, y2, image);
	
	for (int i = 0; i < equationSize; i++)
	{
		cout << equations[i] << "\n";
	}
	if (eqState == 0) { //Unpicked state
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

void EquationBox::createEquation(int i,  int equationSizes, int x, int y, int y2, Mat img){
	
	equationSize = sizeof(equations) / sizeof(*equations);
	srand(time(NULL)+i);
	
	int eqStart = 0;
	eqStart = i;
	

	for (i; i < equationSize/2 + eqStart; i++)
	{
		rNumber1 = rand() % 10;
		rNumber2 = rand() % 10;
		rOperator = rand() % 2;
		
		y2 = y;
		y = y + 50 * (i - eqStart);
		

		if (rNumber1 <= rNumber2){
			rTempNumber1 = rNumber1;
			rNumber2 = rNumber1;
			rNumber1 = rTempNumber1;
		}

		if (rOperator == 0){ //in here goes an equation with subtraction	
			equations[i] = to_string(rNumber1) + "-" + to_string(rNumber2);
			String text = equations[i];
			Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
			baseline += thickness;
			putText(image, text, Point(x, y), fontFace, fontScale, Scalar::all(255), 1, 8);
			rectangle(image, Point(x - 5, y + 5), Point(x + textSize.width + 5, y - textSize.height - 5), Scalar::all(255), 1);
			realAnswer[i] = rNumber1 - rNumber2;
		}
		else if (rOperator == 1){ //In here goes an equation with addition
			equations[i] = to_string(rNumber1) + "+" + to_string(rNumber2);
			String text = equations[i];
			Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
			baseline += thickness;
			putText(image, text, Point(x, y), fontFace, fontScale, Scalar::all(255), 1, 8);
			rectangle(image, Point(x - 5, y + 5), Point(x + textSize.width + 5, y - textSize.height - 5), Scalar::all(255), 1);
			putText(image, text, Point(x, y), fontFace, fontScale, Scalar::all(255), 1, 8);

			realAnswer[i] = rNumber1 + rNumber2;
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
	int temprNumber;
	bool tempholding; //This bool should be taken from the grab() function
	int tempequationSize;
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
	int equationSize = tempequationSize;
	int rNumber = temprNumber;
	int answers[10];
	int tempArray[10];


	
	//void spinningCircles(int, int answers[], int, double, int, int &baseline, double, double, int, double, double, Mat);
	void singleCircle(int answersSize, int answers[], int fontFace, double fontScale, int thickness, int &baseline, double x, double y, int radius, double angle, double speed, Mat img);
	void rotate(Mat src, double rotateAngle, Mat dst, int x, int y);
	void numberGenerator(int equationsP1[], int equationsP2[]);
	void circulate(int, int);
	void drop();
	void grab();

};

void Answers::numberGenerator(int equationsP1[], int equationsP2[]){
	
	equationSize = 6;

	answersSize = sizeof(answers) / sizeof(*answers);
	for (int i = 0; i < equationSize / 2; i++)
	{
		answers[i] = equationsP1[i];
		answers[i + equationSize / 2] = equationsP2[i + equationSize / 2];
	}
	
	for (int i = equationSize; i < answersSize; i++)
	{
		rNumber = rand() % 21;
		answers[i] = 101;
	}

	for (int i = 0; i < answersSize; i++){
		rNumber = rand() % 10;
		cout << rNumber;
		tempArray[i] = answers[i];
		answers[i] = answers[rNumber];
		answers[rNumber] = tempArray[i];
	}
}

void Answers::circulate(int x, int y){
	{
		//Vari from other classes
		double radiusOuter = sizeY / 2 - circleRadius*6;
		double radiusInner = sizeY / 2 - circleRadius*9;
		
		answersSize = sizeof(answers) / sizeof(*answers);

		int answersInner[5];
		int answersOuter[5];
		//Declaring the array size, since c++ is stoopid
		//Also spacing numbers and delcaring start position
		

		for (int i = 0; i < answersSize / 2; i++)
		{
			answersInner[i] = answers[i];
			answersOuter[i] = answers[i + answersSize / 2];
		}
		
		Mat newImage = Mat::zeros(sizeY, sizeX, CV_8UC3);
		image = newImage;

		speedRight += 0.02;
		speedLeft -= 0.02;
		rotateSpeed += 2.8;

		//The inner circle
		singleCircle(answersSize/2, answersInner, fontFace, fontScale, thickness, baseline, x, y, radiusInner, angle, speedRight, image);

		//The outer circle
		singleCircle(answersSize/2, answersOuter, fontFace, fontScale, thickness, baseline, x, y, radiusOuter, angle, speedLeft, image);
		
	}
}

void Answers::singleCircle(int answersSize, int answers[], int fontFace, double fontScale, int thickness, int &baseline, double x, double y, int radius, double angle, double speed, Mat img){
	for (int i = 0; i < answersSize; i++)
	{
		angle = 2 * M_PI / answersSize;
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
	clock_t init, final;
	int printin = 0;
	

	Mat image = Mat::zeros(sizeY, sizeX, CV_8UC3);
	void setTimer(){ init = clock(); }

	void startTimer(int y, int x){
		Mat newImage = Mat::zeros(sizeY, sizeX, CV_8UC3);
		image = newImage;
		cout << printin;
		String text = to_string(printin);
		putText(newImage, text, Point(y, x), fontFace, fontScale, Scalar::all(255), 1);
		if (printin >= 10)
			putText(newImage, "wow", Point(250, 300), fontFace, fontScale, Scalar::all(255), 1);
		final = clock() - init;
		printin = final / (CLOCKS_PER_SEC);
	}
};



int main(int, char)
{
	GameContainer gameContainer;

	MathTimer mathTimerP1;
	MathTimer mathTimerP2;
	mathTimerP1.setTimer();
	
	

	EquationBox equationsP1;
	EquationBox equationsP2;
	equationsP1.eqLocation(0, gameContainer.sizeY / 1.4, gameContainer.sizeX / 20, 0, 0, 0, 0);
	equationsP2.eqLocation(3, gameContainer.sizeY / 1.4, gameContainer.sizeX / 1.1, 0, 0, 0, 0);
	equationsP1.pickEquation();

	AnswerBox answerBoxP1;
	AnswerBox answerBoxP2;

	
	Answers answers;
	answers.numberGenerator(equationsP1.realAnswer, equationsP2.realAnswer);

	for (;;){
		answerBoxP1.ansBoxLocation(gameContainer.sizeY / 2 - answerBoxP1.boxSize / 2, gameContainer.sizeX / 32.4);
		answerBoxP2.ansBoxLocation(gameContainer.sizeY / 2 - answerBoxP1.boxSize / 2, gameContainer.sizeX - gameContainer.sizeX / 32.4 - answerBoxP1.boxSize);

		Mat image = Mat::zeros(gameContainer.sizeY, gameContainer.sizeX, CV_8UC3);
		mathTimerP1.startTimer(120,385);
		answers.circulate(100, 100);
		//mathTimerP1.startTimer();
		//mathTimerP2.startTimer(gameContainer.sizeX - gameContainer.sizeX / 4, gameContainer.sizeY - gameContainer.sizeY / 4);
		image = gameContainer.image + answerBoxP1.image + answerBoxP2.image + answers.image + mathTimerP1.image + mathTimerP2.image + equationsP1.image + equationsP2.image;
		imshow("Gaaame", image);
		if (waitKey(30) >= 0)
			break;

	}
}
