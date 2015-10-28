#include "opencv2/opencv.hpp"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

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

int main(int, char)
{
	GameContainer gameInitialized;
	gameInitialized.containerConstructor(0, 0);
	//Returns the sizeX and sizeY
	cout << "sizeX: " << gameInitialized.sizeX() << "\nsizeY: " << gameInitialized.sizeY() << endl;
	cout << "Before name has a value: " << gameInitialized.name << "\n";
	gameInitialized.name = 100;
	cout << "After name has a been given a value of 100: " << gameInitialized.name;
	waitKey(0);
	return(0);
}
