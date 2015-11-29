#define _USE_MATH_DEFINES
#include "opencv2/opencv.hpp"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <ctime>
#include <math.h>
#include <ctime>
#include <Windows.h>

using namespace cv;
using namespace std;

class GameContainer
{
	Mat image1 = Mat::zeros(400, 640, CV_8UC3);
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
	int sizeX = tempSizeX;
	int sizeY = tempSizeY;
	int name = tempName;
	Mat image = Mat::zeros(sizeY, sizeX, CV_8UC3);
	double placeX = tempPlaceX;
	double placeY = tempPlaceY;
	int placeXArray[10];
	int placeYArray[10];
	int eqState = tempeqState;
	int handState = temphandState;
	int handPosX = temphandPosX;
	int handPosY = temphandPosy;
	int circleRadius = tempcircleRadius;
	int playerColor = tempplayerColor;

	//Initializing the unchanging features of the text
	int fontFace = FONT_HERSHEY_SIMPLEX;
	int thickness = 2;
	int baseline = 0;
	double fontScale = sizeY / 625.0;

};

class Circles : GameContainer{
	//Initiate all the variables and construcer in this class
public:
	Mat image = Mat::zeros(sizeY, sizeX, CV_8UC3);
	int radiusIn = sizeY / 5.7;
	int radiusMed = sizeY / 3.8;
	int radiusOut = sizeY / 2.8;
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
	double tempboxSize = sizeX / 7.2;
public:
	int r = tempR;
	int g = tempG;
	int b = tempB;
	int fill = tempFill;
	int score = tempScore;
	Mat image = Mat::zeros(sizeY, sizeX, CV_8UC3);
	double boxSize = tempboxSize;
	bool insideBox[];

	void ansBoxLocation(int, int, double objX[], double objY[], bool pos[], int yourAnswer[], int realAnswer[], int);
	void checkAnswer(int, int, double objX[], double objY[], bool pos[], int yourAnswer[], int realAnswer[], int);
	void addPoint(int, int);

};

void AnswerBox::ansBoxLocation(int x, int y, double objX[], double objY[], bool pos[], int yourAnswer[], int realAnswer[], int player){
	rectangle(image, Point(y, x), Point(y + boxSize, x + boxSize), Scalar(b, g, r), fill);
	checkAnswer(x, y, objX, objY, pos, yourAnswer, realAnswer, player);
}

void AnswerBox::checkAnswer(int y, int x, double objX[], double objY[], bool pos[], int yourAnswer[], int realAnswer[], int player){
	for (int i = 0; i < 10; i++)
	{
		insideBox[i] = false;
		if (pos[i])
		{

			if (objX[i] > x && objY[i] > y && objX[i] < x + boxSize && objY[i] < y + boxSize)
			{

				if (yourAnswer[i] == realAnswer[player]){
					r = 0;
					b = 0;
					fill = -1;
					addPoint(x, y);
				}

				if (yourAnswer[i] != realAnswer[player]){
					g = 0;
					b = 0;
					fill = -1;
				}
				insideBox[i] = true;
				cout << "check";
			}

		}
	}
}

//HEEEEJ! 
void AnswerBox::addPoint(int x, int y){
	//Initialzing the changing features of the text
	score = 1;
	y += 50;
	x += -100;
	if (score == 1){
		String text = to_string(score) + " Point";
		Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
		baseline += thickness;
		putText(image, text, Point(y - textSize.width / 2, x + textSize.height / 2), fontFace, fontScale, Scalar::all(255), thickness, 8);
	}
	else{
		String text = to_string(score) + " Points";
		Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
		baseline += thickness;
		putText(image, text, Point(y - textSize.width / 2, x + textSize.height / 2), fontFace, fontScale, Scalar::all(255), thickness, 8);
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

	bool tempeqRun = false;

public:
	int rNumber1 = temprNumber1;
	int rNumber2 = temprNumber2;
	int rTempNumber1 = temprTempNumber1;
	int yourAnswer = tempyourAnswer;

	int rOperator = temprOperator;
	int realAnswer[100];
	String equations[100];

	int width = tempwidth;
	int height = tempheight;
	int equationSize = tempequationSize;
	int nextIndex = 0;

	Size textSize;


	bool eqRun = tempeqRun;
	String text;


	String solveableEquation = tempsolveableEquation;
	bool visibility = tempVisibility;
	Mat image = Mat::zeros(sizeY, sizeX, CV_8UC3);
	//Functions
	void eqLocation(int, int, int, int, int, int, int, Point, int, String[], bool[]);
	void pickEquation();
	void createEquation(int, int, int x[], int y[], Mat img, Point, int);
};

void EquationBox::eqLocation(int eqStart, int intY, int intX, int homeY, int homeX, int enemyY, int enemyX, Point hCenter, int check, String eq[], bool insideBox[])
{
	int x[2];
	int y[2];
	for (int i = 0; i < 2; i++){
		x[i] = intX;
		y[i] = intY;
		}
	if (nextIndex != nextIndex || eqRun == false){
		createEquation(eqStart, equationSize / 2, x, y, image, hCenter, check);
		text = "lol";
		putText(image, text, Point(x[1], y[1]), fontFace, fontScale, Scalar::all(255), thickness, 8);
		eqRun = true;
	}
		for (int i = 0; i < 10; i++)
	{
		if (insideBox[i] == true){
			nextIndex++;
			cout << text;
			cout << nextIndex;
			rectangle(image, Point(x[i] - 5, y[i] + 5), Point(x[i] + textSize.width + 5, y[i] - textSize.height - 5), Scalar(255, 0 ,0), -1);
			
			}
		}
	
}



void EquationBox::pickEquation(){
	if (eqState == 1){
		cout << "You did it!\n";
	}
}

void EquationBox::createEquation(int i, int equationSizes, int x[], int y[], Mat img, Point hCenter, int check){

	int eqStart = 0;
	eqStart = i;

	
	
	equationSize = sizeof(equations) / sizeof(*equations);
	srand(time(NULL) + i);

	for (i; i < 1 + eqStart; i++){
		rNumber1 = rand() % 10;
		rNumber2 = rand() % 10;
		rOperator = rand() % 2;

		if (rNumber1 <= rNumber2){
			rTempNumber1 = rNumber1;
			rNumber2 = rNumber1;
			rNumber1 = rTempNumber1;
		}

		if (rOperator == 0){ //in here goes an equation with subtraction	
			equations[i + nextIndex] = to_string(rNumber1) + "-" + to_string(rNumber2);
			text = equations[i + nextIndex];
			textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
			baseline += thickness;
			realAnswer[i + nextIndex] = rNumber1 - rNumber2;

		}
		else if (rOperator == 1){ //In here goes an equation with addition
			equations[i + nextIndex] = to_string(rNumber1) + "+" + to_string(rNumber2);
			text = equations[i + nextIndex];
			textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
			baseline += thickness;
			realAnswer[i + nextIndex] = rNumber1 + rNumber2;
		}
	}
}



class Answers : GameContainer{
	double tempangle;
	double tempspeedRight = 0;
	double tempspeedLeft = 0;
	double temprotateSpeed = 0;
	int tempanswersSize;
	double circleRadius = sizeY / 31.25;
	int temprNumber;
	int tempequationSize;
public:
	Mat image = Mat::zeros(sizeY, sizeX, CV_8UC3);
	double x[10];
	double y[10];
	double angle = tempangle;
	double speedRight = tempspeedRight;
	double speedLeft = tempspeedLeft;
	double rotateSpeed = temprotateSpeed;
	int answersSize = tempanswersSize;
	int equationSize = tempequationSize;
	int rNumber = temprNumber;
	int answers[10];
	int tempArray[10];
	bool holding[10];
	bool firstHold = true;
	bool myInsideBox = true;
	bool notInsideBox[10];

	int eqStart = 0;


	//void spinningCircles(int, int answers[], int, double, int, int &baseline, double, double, int, double, double, Mat);
	void singleCircle(int, int answers[], int radius, double speed, Point hCenter, bool[], int handState);
	void rotate(Mat src, double rotateAngle, Mat dst, int x, int y);
	void numberGenerator(int equationsP1[], int equationsP2[]);
	void circulate(int, int, Point, bool[], int handState);
	void drop();
	void grab();

};

void Answers::numberGenerator(int equationsP1[], int equationsP2[]){

	equationSize = 2;

	answersSize = sizeof(answers) / sizeof(*answers);
	for (int i = 0; i < equationSize / 2; i++)
	{
		answers[i] = equationsP1[i];
		answers[i + equationSize / 2] = equationsP2[i + equationSize / 2];
	}

	for (int i = equationSize; i < answersSize; i++)
	{
		rNumber = rand() % 19;
		answers[i] = rNumber;
	}

	for (int i = 0; i < answersSize; i++){
		rNumber = rand() % 10;
		tempArray[i] = answers[i];
		answers[i] = answers[rNumber];
		answers[rNumber] = tempArray[i];
	}
}

void Answers::circulate(int x, int y, Point hCenter, bool insideBox[], int handState){
	{
		//Vari from other classes
		double radiusOuter = sizeY / 2 - circleRadius * 6;
		double radiusInner = sizeY / 2 - circleRadius * 9;

		answersSize = sizeof(answers) / sizeof(*answers);


		Mat newImage = Mat::zeros(sizeY, sizeX, CV_8UC3);
		image = newImage;

		speedRight += 0.02;
		speedLeft -= 0.02;
		rotateSpeed += 2.8;

		//The inner circle
		singleCircle(0, answers, radiusInner, speedRight, hCenter, insideBox, handState);

		//The outer circle
		singleCircle(5, answers, radiusOuter, speedLeft, hCenter, insideBox, handState);

	}
}

void Answers::singleCircle(int i, int ans[], int radius, double speed, Point hCenter, bool insideBox[], int handState){
	angle = 2 * M_PI / (answersSize / 2);
	eqStart = i;

	for (i + eqStart; i < answersSize / 2 + eqStart; i++)
	{
		//Initialzing the changing features inside the circle, such as text and position
		String text = to_string(ans[i]);
		Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
		baseline += thickness;

		//Creating matrixes for each of the different answers, to make them "rotateable". Currently not in use
		//Mat textImg = Mat::zeros(image.rows, image.cols, image.type());

		//Declaring the position of the answer
		x[i] = radius*sin(angle * i + speed) + sizeX / 2;
		y[i] = radius*cos(angle * i + speed) + sizeY / 2;

		if (handState == 1){
			if (firstHold == true) {
				if (x[i] + circleRadius > hCenter.x && y[i] + circleRadius > hCenter.y && x[i] - circleRadius < hCenter.x && y[i] - circleRadius < hCenter.y){
					holding[i] = true;
					firstHold = false;
				}
			}
		}
		if (holding[i]){
			x[i] = hCenter.x;
			y[i] = hCenter.y;
			if (insideBox[i]){
				holding[i] = false;
				firstHold = true;

			}

		}
		Point answerPos(x[i], y[i]);
		//Creating the numbers to be shown
		circle(image, answerPos, circleRadius, Scalar(0, 0, 255), 1, 1);
		putText(image, text, Point(x[i] - textSize.width / 2, y[i] + textSize.height / 2), fontFace, fontScale, Scalar::all(255), thickness, 8);
		//rotate(textImg, rotateSpeed, textImg, x, y);
		//Adds the new text image to the source image
		//image = image + textImg;
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
		String text = to_string(printin);
		putText(newImage, text, Point(y, x), fontFace, fontScale, Scalar::all(255), thickness);
		if (printin >= 10)
			putText(newImage, "wow", Point(250, 300), fontFace, fontScale, Scalar::all(255), thickness);
		final = clock() - init;
		printin = final / (CLOCKS_PER_SEC);
	}
};

class ImageProcessing : GameContainer
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
				if (blob_area < min_area || blob_area>max_area)
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

		//std::cout << t << "\n";
		//std::cout << blob_area << "\n";
		//std::cout << blob_circularity << "\n";
		//std::cout << "\n";
		//std::cout << "\n";
		//t++;
	}
	void draw()																				//Draw contours
	{
		Mat newImage = Mat::zeros(sizeY, sizeX, CV_8UC3);
		image = newImage;
		
		if (blob_state == 1)
			rectangle(newImage, center, Point(center.x + 1, center.y + 1), CV_RGB(255, 0, 0), 10);
		else
			rectangle(newImage, center, Point(center.x + 1, center.y + 1), CV_RGB(0, 0, 255), 10);

		//drawContours(result, contours,
		//	-1,
		//	cv::Scalar(0),
		//	1);

	}
	Mat image = Mat::zeros(sizeY, sizeX, CV_8UC3);
	Mat frame,
		background,
		thresholded,
		gray_frame,
		subtracted,
		contour_frame;
	Point2f center;
	std::vector<std::vector<cv::Point>> contours;
	int min_contour = 100,																	//Minimum size of the contour to be counted as objet of interest
		max_contour = 600,																	//Maximum size of the contour to be counted as objet of interest
		min_area = 2200,																		//Minimum area of the blob to be counted as objet of interest
		max_area = 6000,																		//Maximum area of the blob to be counted as objet of interest
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
		blob_circularity_precision = 1.0;													//Circularity threshold, determine state/gesture
};

int main(int, char)
{
	ImageProcessing IPGod;
	VideoCapture cap(0);
	if (!cap.isOpened()){

		std::cout << "Not found";
	}

	GameContainer gameContainer;

	MathTimer mathTimerP1;
	MathTimer mathTimerP2;
	mathTimerP1.setTimer();

	AnswerBox answerBoxP1;
	AnswerBox answerBoxP2;

	EquationBox equationsP1;
	EquationBox equationsP2;
	equationsP2.eqLocation(1, 300, 700, 0, 0, 0, 0, IPGod.center, mathTimerP2.printin, equationsP2.equations, answerBoxP2.insideBox);
	equationsP1.pickEquation();


	Circles circles;
	circles.createCircles();

	Answers answers;
	answers.numberGenerator(equationsP1.realAnswer, equationsP2.realAnswer);

	cap >> IPGod.background;
	cvtColor(IPGod.background, IPGod.background, CV_RGB2GRAY);
	for (;;){
		cap >> IPGod.frame;
		IPGod.thresholding();
		IPGod.contour();
		IPGod.eliminteContours();

		equationsP1.eqLocation(0, 300, 50, 0, 0, 0, 0, IPGod.center, mathTimerP1.printin, equationsP1.equations, answerBoxP1.insideBox);


		answerBoxP1.ansBoxLocation(gameContainer.sizeY / 2 - answerBoxP1.boxSize / 2, gameContainer.sizeX / 32.4, answers.x, answers.y, answers.holding, answers.answers, equationsP1.realAnswer, 0);
		answerBoxP2.ansBoxLocation(gameContainer.sizeY / 2 - answerBoxP1.boxSize / 2, gameContainer.sizeX - gameContainer.sizeX / 32.4 - answerBoxP1.boxSize, answers.x, answers.y, answers.holding, answers.answers, equationsP2.realAnswer, 1);

		Mat image = Mat::zeros(gameContainer.sizeY, gameContainer.sizeX, CV_8UC3);
		mathTimerP1.startTimer(120, 385);
		answers.circulate(100, 100, IPGod.center, answerBoxP1.insideBox, IPGod.blob_state);
		//mathTimerP1.startTimer();
		//mathTimerP2.startTimer(gameContainer.sizeX - gameContainer.sizeX / 4, gameContainer.sizeY - gameContainer.sizeY / 4);
		image = gameContainer.image + answerBoxP1.image + answerBoxP2.image + answers.image + mathTimerP1.image + mathTimerP2.image + equationsP1.image + equationsP2.image + circles.image + IPGod.image;
		namedWindow("Gaaame", CV_WINDOW_AUTOSIZE);
		imshow("Gaaame", image);
		imshow("thresh", IPGod.thresholded);
		if (waitKey(30) >= 0)
			break;
	}
}
