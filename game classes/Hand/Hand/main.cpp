#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

class Hand{
	int tempX = 1; //This will be equal to the object ID given by IP god
	int tempY = 1; //This will be equal to the object ID given by IP god
	int tempState = 1; //This will be equal to the hand state given by IP god
public:
	int state = tempState;
	int x = tempX;
	int y = tempY;
	void collide() {
		if (state == 1){ //this is finished
			if (x == 1 && y == 1){ //the == 1 needs to be changed to == ipGod::objectID
				cout << "you will find the object ID here :)";
			}
		}
	}
};


int main(int, char){
	Hand myHand;
	myHand.collide();
	return(0);
}