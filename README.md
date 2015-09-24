# The-suicide-pit-
Our 3rd. semester favorite repository
Excercise> make 2 thresholds after loading an image
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	Mat image;
	image = imread("C:/morten.jpg", 1);
	imshow("Original image", image);
	if (image.data && !image.empty()){
		int countR = 0, countG = 0, countB = 0;
		for (size_t y = 0; y < image.rows; ++y){
			for (size_t x = 0; x < image.cols; ++x){
				countB = image.at<Vec3b>(y, x)[0];
				countG = image.at<Vec3b>(y, x)[1];
				countR = image.at<Vec3b>(y, x)[2];
				if (countB >= 90 && countG >= 90 && countR >= 90 && countB <= 150 && countG <= 150 && countR <= 150){
					image.at<Vec3b>(y, x)[0] = 255;
					image.at<Vec3b>(y, x)[1] = 255;
					image.at<Vec3b>(y, x)[2] = 255;
				}
				else{
					image.at<Vec3b>(y, x)[0] = 0;
					image.at<Vec3b>(y, x)[1] = 0;
					image.at<Vec3b>(y, x)[2] = 0;
				}
			}
		}
		imshow("Thresoldedimage", image);
		waitKey(0);

	}
	return 0;
}
