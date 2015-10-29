#include "opencv2/opencv.hpp"
#include<iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

class GameContainer
{
public:
	float placeX, placeY;
	int tempSizeX, tempSizeY;
	int tempName;
public:
	void containerConstructor(int, int);
	int sizeX() { return 100; }	//This is the number of the Horisontal size of the game board
	int sizeY() { return 200; }	//This is the number of the Vertical size of the game board
	int name = tempName; //Initialized the ID in the constructer
};

void GameContainer::containerConstructor(int x, int y) {
	tempSizeX = x;
	tempSizeY = y;
}

//class for EquationBox
class EquationBox{
	//initiate all variables and constructors in this class
public:
	void EqBoxLocation(float, float);
	void PickEquation();
	void SendAnswer();
	void CreateEquation();
	//these are private because we are not suposed to be able to change them in other classes
private:
	int state;
	String equation;
	float answer;
	bool visibility;
	int homeX = -50;
	int homeY = -50;
	int enemyX = 50;
	int enemyY = 50;

};

//main function where we call other functions and classes
int main(int, char)
{
	GameContainer gameInitialized;
	gameInitialized.containerConstructor(0, 0);
	EquationBox EqBox1;
	EqBox1.EqBoxLocation(0, 0);

	return(0);
	waitKey(0);
}


//specifying attributes and values for the function called EqBoxLocation
//this function changes the location of the equations
void EquationBox::EqBoxLocation(float placeX, float placeY)
{
	if (state == 0){
	gameInitialized:placeX = homeX;
	gameInitialized:placeY = homeY;
		visibility = true;
	}
	else if (state == 1){
		placeX = enemyX;
		placeY = enemyY;
		visibility = true;
	}
	else if (state == 2){
		placeX = enemyX;
		placeY = enemyY;
		visibility = false;
	}
	cout << "PlaceX = " << placeX
		<< " PlaceY = " << placeY << endl;
}



/*void EquationBox::PickEquation()
{
if (collide() == containerConstructor.name){


}
}

void SendAnswer(){

}

void CreateEquation(){

}

//EquationBox inherits from GameContainer
class EqBoxLocation : public GameContainer {
public :
float placeX, placeY;
int name;

};*/
