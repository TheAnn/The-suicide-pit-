#include "opencv2/opencv.hpp"

using namespace cv;
//The GameContainer, just a bunch of variables
class GameContainer
{
	int tempcollide = 1;
	int tempSizeX = 800; // X-size of the gameboard
	int tempSizeY = 400; // Y-size of the gameboard
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


class AnswerBox : GameContainer{
	//Initiate all the variables and construcer in this class
public:
	Mat image = Mat::zeros(sizeY, sizeX, CV_8UC3);

	void ansBoxLocation(int, int);
	void checkAnswer(int, int);
	void addPoint(int, int);

};

void AnswerBox::ansBoxLocation(int x, int y){
	rectangle(image, Point(y, x), Point(y + 50, x + 50), Scalar(255, 255, 255), 1);

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


int main(int, char)
{
	GameContainer gameContainer;

	AnswerBox answerBoxP1;
	AnswerBox answerBoxP2;
	answerBoxP1.checkAnswer(gameContainer.sizeY / 2, 50);
	answerBoxP1.ansBoxLocation(gameContainer.sizeY / 2 - 25, 10);
	answerBoxP2.checkAnswer(gameContainer.sizeY / 2, gameContainer.sizeX - 50);
	answerBoxP2.ansBoxLocation(gameContainer.sizeY / 2 - 25, gameContainer.sizeX - 60);

	for (;;){
		Mat image = Mat::zeros(gameContainer.sizeY, gameContainer.sizeX, CV_8UC3);
		image = gameContainer.image + answerBoxP1.image + answerBoxP2.image;
		imshow("Gaaame", image);
		if (waitKey(30) >= 0){
			break;
		}
	}
}