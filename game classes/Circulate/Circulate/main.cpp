#include "opencv2/opencv.hpp"
#include <conio.h>
#define _USE_MATH_DEFINES
#include <math.h>


using namespace cv;

void rotate(cv::Mat& src, double rotateAngle, cv::Mat& dst)
{
	int len = max(src.cols, src.rows);
	cv::Point2f pt(len / 2., len / 2.);
	cv::Mat r = cv::getRotationMatrix2D(pt, rotateAngle, 1.0);
	cv::warpAffine(src, dst, r, Size(len, len));
}

int main(int, char)
{
	int x = 100;
	int y = 100;
	int rotateX, rotateY;
	int angle = 2 * M_PI / 1;
	int radius = 50;
	float speed = 0;
	float rotateSpeed = 0;

	//creating the text
	String text = "text";
	int fontFace = FONT_HERSHEY_SIMPLEX;
	double fontScale = 1;
	int thickness = 3;
	int baseline = 0;
	Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
	baseline += thickness;


	for (;;)
	{
		Mat image = Mat::zeros(500, 500, CV_8UC3);
		Mat textImg = Mat::zeros(image.rows, image.cols, image.type());
		circle(image, Point(x, y), 50, Scalar(255, 0, 0), 1, 1);
		putText(textImg, text, Point(x - textSize.width / 2, y + textSize.height / 2), fontFace, fontScale, Scalar::all(255), 1, 8);



		putText(textImg, text, Point(100, 100), fontFace, fontScale, Scalar::all(255), 1, 8);
		rotate(textImg, rotateSpeed, textImg);

		image = image + textImg;
		imshow("cool pic", image);
		x = radius*sin(angle * 1 + speed) + 500 / 2;
		y = radius*cos(angle * 1 + speed) + 500 / 2;
		speed += 0.05;
		rotateSpeed += 1;
		waitKey(0);
	}
	return 0;
}