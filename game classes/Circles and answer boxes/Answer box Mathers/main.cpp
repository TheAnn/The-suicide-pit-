#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

class GameContainer
{
	float tempPlaceX, tempPlaceY;
	int tempSizeX, tempSizeY;
	int tempName;
public:
	void containerConstructor(int, int);
	int sizeX() { return 100; }	//This is the number of the Horisontal size of the game board
	int sizeY() { return 200; }	//This is the number of the Vertical size of the game board
	int name = tempName; //Initialzed the ID in the constructer
	float placeX = tempPlaceX;	//Initialzed the placeX in the constructer
	float placeY = tempPlaceY;	//Initialzed the placeT in the constructer
};

void GameContainer::containerConstructor(int x, int y) {
	tempSizeX = x;
	tempSizeY = y;
}

//class for AnswerBox
class AnswerBox {
	//initiate all variables and constructors in this class:
public:
	void ansBoxLocation(float, float);
	void checkAnswer();
	void changeColor();
	int addPoint();
	//these are private because we are not suposed to be able to change them in other classes
private:
};

int main(int, char)
{
	GameContainer gameInitialized;
	gameInitialized.containerConstructor(0, 0);
	//Returns the sizeX and sizeY
	cout << "sizeX: " << gameInitialized.sizeX() << "\nsizeY: " << gameInitialized.sizeY() << endl;
	cout << "Before name has a value: " << gameInitialized.name << "\n";
	gameInitialized.name = 100;
	cout << "After name has a been given a value of 100: " << gameInitialized.name;

	
	//AnswerBox
	
	// Create black empty images
	float width = 500;
	float height = 800;
	Mat image = Mat::zeros(width, height, CV_8UC3);
	
	// Draw a rectangle -> void rectangle(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=8)
	float pt1 = (4.5*height / 5); 
	float pt2 = (3*width / 5);
	float pt3 = (height / 4);
	float pt4 = (0.3*width / 5);
	
	// The points are made to have the correct position for the answerboxes but we have to change them a bit when we have the correct size of the table. 
	rectangle(image, Point(pt1, pt2), Point (pt1 + 50, pt3) , Scalar(255, 255, 255), -2); //The values for the rectangle are the points defined above. We added 50 to set the size of the box. 
	rectangle(image, Point(pt4, pt2), Point (pt4 + 50, pt3) , Scalar(255, 255, 255), -2); 

	int cY = width; //Variable - center of circle
	int cX = height; //Variable - center of circle

	// Draw a circle (the circles with the answers) -> void circle(Mat& img, Point center, int radius, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
	circle(image, Point(cX / 2, cY / 2), cY / 2, Scalar(255, 255, 255), 1, 8); //The values for center and radius needs to changed to fit our program
	circle(image, Point(cX / 2, cY / 2), cY / 2.35, Scalar(255, 255, 255), 1, 8); //The values for center and radius needs to changed to fit our program
	circle(image, Point(cX / 2, cY / 2), cY / 3, Scalar(255, 255, 255), 1, 8); //The values for center and radius needs to changed to fit our program
	imshow("Mathers", image);


	
	/*AnswerBox ansBox1;
	ansBox1.ansBoxLocation(0, 0);

	AnswerBox ansBox2;
	ansBox2.ansBoxLocation(0, 0);

	if ()*/

	waitKey(0);

	return(0);


}

