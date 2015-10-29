#include "opencv2/opencv.hpp"

using namespace cv;

int main(int, char){

//Initializes all the variables
int cY = 500; //center
int cX = 800; //center
int radiusIn = cY / 3;
int radiusMed = cY / 2.35;
int radiusOut = cY / 2;
Point circleCenter(cX / 2, cY / 2);

// Create black empty images 
Mat image = Mat::zeros(cY, cX, CV_8UC3);
// Draw a circle -> void circle(Mat& img, Point center, int radius, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
circle(image, circleCenter, radiusIn, Scalar(255, 255, 255), 1, 8); //The values for center and radius needs to changed to fit our program
circle(image, circleCenter, radiusMed, Scalar(255, 255, 255), 1, 8); //The values for center and radius needs to changed to fit our program
circle(image, circleCenter, radiusOut, Scalar(255, 255, 255), 1, 8); //The values for center and radius needs to changed to fit our program
imshow("Image", image);

waitKey(0);
return(0);
}