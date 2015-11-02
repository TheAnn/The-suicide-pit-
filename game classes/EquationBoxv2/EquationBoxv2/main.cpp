#include "opencv2/opencv.hpp"
#include <ctime>
#include <iostream>

using namespace cv;
using namespace std;

class EquationBox{
	int tempState = 1;
	bool tempVisibility = true;
	int collide = 1; //The collide should come from the Hand class
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
	int state = tempState;
	void eqLocation();
	void pickEquation();
	void createEquation();
};

void EquationBox::eqLocation()
{
	if (state == 0) { //Unpicked state
		//placeX = homeX //Changes the equations location on the X-axis, to your own equation box
		//placeY = homeY //Changes the equations location on the Y-axis, to your own equation box
		visibility = true; //Determines if the box is visible on the board
		cout << "State 0 achived. gz \n";
	}
	else if (state == 1){ //Picked state
		//placeX = enemyX //Changes the equations location on the X-axis, to your enemies "solving box"
		//placeY = enemyY //Changes the equations location on the Y-axis, to your enemies "solving box"
		visibility = true; //Determines if the box is visible on the board
		cout << "State 1 achived. gz \n";
	}
	else if (state == 2){ //Queued state
		//placeX = enemyX //Changes the equations location on the X-axis, to your enemies "solving box"
		//placeY = enemyY //Changes the equations location on the Y-axis, to your enemies "solving box"
		visibility = false; //Determines if the box is visible on the board
		cout << "State 2 achived. gz \n";
	}
}

void EquationBox::pickEquation(){
	if (collide % 2 == 0){
		//if (hand.pColor == eq.pColor) //Checks if the color on the hand picking and the equation adds up
		state = 2;
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

int main(int, char)
{
	EquationBox equations;
	equations.eqLocation();
	equations.pickEquation();
	equations.createEquation();
	return 0;
}