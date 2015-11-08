#include "opencv2/opencv.hpp"
#include <time.h>
#include <iostream>

using namespace cv;
using namespace std;



int main(int, char)
{
	clock_t init, final;
	init = clock();
	double printin = 0;
	//
	// do stuff
	//

	int fontFace = FONT_HERSHEY_SIMPLEX;
	int thickness = 3;
	int baseline = 0;
	double fontScale = 0.7;


	for (;;){
		Mat image = Mat::zeros(500, 500, CV_8UC3);
		String text = to_string(printin);
		putText(image, text, Point(250, 250), fontFace, fontScale, Scalar::all(255), 1);
		if (printin >= 10)
			putText(image, "wow", Point(250, 300), fontFace, fontScale, Scalar::all(255), 1);
		final = clock() - init;
		printin = (double)final / ((double)CLOCKS_PER_SEC);
		imshow("kek", image);
		if (waitKey(30) >= 0)
			break;
	}
	return 0;
}