#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

class A{
	int tempA = 10;
public:
	Mat image = Mat::zeros(200, 200, CV_8UC3);
	int a = tempA;
	void imageImp(){
		circle(image, Point(50, 50), 20, Scalar(255, 255, 255), 1, 8);
	};

};

class B : A{
	int tempB = 20;
public:
	int b = tempB;
	int ab = a;
	void imageShow(){
		imshow("work pls", image);
	};
	void hello(){
		cout << "hello";
	}
	void superhello(){
		hello();
	}
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
	testA.imageImp();

	B testB;
	cout << testB.b << "\n";
	cout << testB.ab << "\n";
	testB.imageShow();
	testB.superhello();

	C testC;
	cout << testC.c << "\n";
	//Test
	imshow("work plas", testA.image);
	waitKey(0);
	return 0;
}