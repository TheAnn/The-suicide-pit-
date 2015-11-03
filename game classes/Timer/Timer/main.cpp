// Timer class
#include "opencv2/opencv.hpp"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <ctime>
#include <Windows.h>

using namespace cv;
using namespace std;

//start the variables
class MathTimer{
	int tempsec = 0;
public:
	int sec = tempsec;
	void startTimer(){
		for (int k = 0; k<11; k++)
		{
			Sleep(1000);
			Mat image = Mat::zeros(200, 400, CV_8UC3);
			cv::putText(image, "lala", cv::Point(50, 50), CV_FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 1, 8, false);
			imshow("Timer", image);
			cout << "Timer: " << sec << endl;
			sec++;
			system("Cls");
			if (sec == 10){
				cout << "Stop" << endl;
			}
		}
	};
};

int main()
{
	MathTimer mathTimer;
	mathTimer.startTimer();
	waitKey(0);
	return 0;
}