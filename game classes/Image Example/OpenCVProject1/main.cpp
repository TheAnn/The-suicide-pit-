#include "opencv2/opencv.hpp"

using namespace cv;

int main(int, char)
{
	Mat image = imread("C:/images/mathers.png", 1);
	Mat image2 = Mat::zeros(image.rows, image.cols, CV_8UC3);

	circle(image2, Point(image.rows/2, image.cols/2), 100, Scalar(255, 255, 255), 1, 8);
	imshow("image1", image);
	imshow("image2", image2);
	Mat image3 = image + image2;
	imshow("image3", image3);
	Mat image4 = image2 + image;
	imshow("image4", image4);
	waitKey(0);
	return 0;
}