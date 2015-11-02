#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

class A{
	int tempA = 10;
public:
	int a = tempA;
};

class B : A{
	int tempB = 20;
public:
	int b = tempB;
	int ab = a;
};

class C : B{
	int tempC = 30;
public:
	int c = tempC;
	int bc = b;
};


int main(int, char)
{
	A testA;
	cout << testA.a << "\n";

	B testB;
	cout << testB.b << "\n";
	cout << testB.ab << "\n";

	C testC;
	cout << testC.c << "\n";
	//Test
	return 0;
}