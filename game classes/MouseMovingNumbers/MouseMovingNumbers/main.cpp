#include "opencv2/opencv.hpp"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <ctime>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
using namespace cv;

void CallBackFunc(int event, int mouseX, int mouseY, int flags, void* userdata)
{
	Mat img = imread("C:/images/mathers.png");

	int sizeX = img.rows;
	int sizeY = img.cols;

	int circleRadius = 10;
	double x = 0;
	double y = 0;
	double angle = 0;
	double speedRight = 0;
	int answersSize = 12;

	//Vari from other classes
	double radiusOuter = 100;
	int answers[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

	//Declaring the array size, since c++ is stoopid
	//Also spacing numbers and delcaring start position
	answersSize = sizeof(answers) / sizeof(*answers);
	angle = 2 * M_PI / answersSize;

	//Initializing the unchanging features of the text
	int fontFace = FONT_HERSHEY_SIMPLEX;
	double fontScale = 0.7;
	int thickness = 3;
	int baseline = 0;
	bool pls = false;


	for (int i = 0; i < answersSize; i++)
	{
		//Initialzing the changing features inside the circle, such as text and position
		String text = to_string(answers[i]);
		Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
		baseline += thickness;

		//Creating matrixes for each of the different answers, to make them "rotateable". Currently not in use
		//Mat textImg = Mat::zeros(image.rows, image.cols, image.type());

		//Declaring the position of the answer
		x = radiusOuter*sin(angle * i + speedRight) + sizeX / 2;
		y = radiusOuter*cos(angle * i + speedRight) + sizeY / 2;
		Point answerPos(x, y);

		if (x + circleRadius > mouseX && y + circleRadius > mouseY && x - circleRadius < mouseX && y - circleRadius < mouseY){
			cout << "now!";
			x = mouseX;
			y = mouseY;
			circleRadius = 100;
		}

		//Creating the numbers to be shown
		circle(img, answerPos, circleRadius, Scalar(0, 0, 255), 1, 1);
		putText(img, text, Point(x - textSize.width / 2, y + textSize.height / 2), fontFace, fontScale, Scalar::all(255), 1, 8);
		//rotate(textImg, rotateSpeed, textImg, x, y);
		//Adds the new text image to the source image
		//image = image + textImg;
	}


	if (event == EVENT_LBUTTONDOWN)
	{
		cout << "Left button of the mouse is clicked - position (" << mouseX << ", " << mouseY << ")" << endl;
	}
	else if (event == EVENT_MOUSEMOVE)
	{
		cout << "Mouse move over the window - position (" << mouseX << ", " << mouseY << ")" << endl;

	}

	circle(img, Point(x, y), 10, Scalar(0, 0, 255), 1, 1);
	imshow("My Window", img);
}

int main(int argc, char** argv)
{


	//Create a window
	namedWindow("My Window", 1);

	//set the callback function for any mouse event
	setMouseCallback("My Window", CallBackFunc, NULL);
	waitKey(30);

	// Wait until user press some key
	waitKey(0);

	return 0;

}

