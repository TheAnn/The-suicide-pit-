#define _USE_MATH_DEFINES
#include "opencv2/opencv.hpp"
#include <cmath>
#include <ctime>

using namespace cv;

bool new_eq[] = { true, true, true, true };
float answer_list[] = { 1, 2, 0, 0, 5, 6, 7, 8, 9, 10, 11, 12 };
String equation;



void vocabulary_trundle(Point pivot, String word, Scalar color)
{

	double shiftVar = 1.2;
	int fontFace = FONT_HERSHEY_SIMPLEX;
	int thickness = 2;
	int baseline = 0;
	double fontScale = 1;
	int value;

	Size textSize = getTextSize(word, fontFace, fontScale, thickness, &baseline);
	baseline += thickness;

	Mat yep = Mat::zeros(textSize.height*2, textSize.width, CV_8UC3);
	putText(yep, word, Point(0, textSize.height*shiftVar), fontFace, fontScale, color, thickness, 8);
	imshow("looolaa", yep);


	Mat r = cv::getRotationMatrix2D(Point(textSize.height / shiftVar, textSize.height / shiftVar), -90, 1.0);
	warpAffine(yep, yep, r, Size(textSize.height*2, textSize.width));

	Mat image = Mat::zeros(400, 640, CV_8UC3);

	std::cout << "\n" << pivot.x << "\n" << pivot.y;

	std::cout << "\n" << textSize.height << "\n" << textSize.width << "\n" << yep.rows << "\n" << yep.cols;

	for (int y = pivot.y; y < yep.rows + pivot.y; ++y){
		for (int x = pivot.x; x < textSize.height*5 + pivot.x; ++x){
			int pixel = yep.at<unsigned char>(y - pivot.y, x - pivot.x);
				image.at<unsigned char>(y, x) = pixel;
		}
	}

	
	imshow("loool2", yep);
	imshow("loool", image);
}




double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}


void Equation()
{

	int correct_answer,
		index;
	Point2f location,
		location_op;
	Scalar box_colour;

	index = 0;

	new_eq[index] = false;
	srand(time(NULL) + index);




	int first_number = 1 + rand() % 10;
	double first_number_deci = fRand(1, 10);
	int second_number = 1 + rand() % 10;
	double second_number_deci = fRand(1, 10);
	int operation = rand() % 3;
	int deci_decider = rand() % 4;

	first_number_deci = floor(first_number_deci * 100.0) / 100;
	second_number_deci = floor(second_number_deci * 100.0) / 100;

	switch (operation) {
	case 0:
		switch (deci_decider) {
		case 0:
			answer_list[index] = first_number + second_number;
			equation = std::to_string(first_number) + "+" + std::to_string(second_number) + "=";
			break;
		case 1:
			answer_list[index] = first_number_deci + second_number_deci;
			equation = std::to_string(first_number_deci) + "+" + std::to_string(second_number_deci) + "=";
			break;
		case 2:
			answer_list[index] = first_number + second_number_deci;
			equation = std::to_string(first_number) + "+" + std::to_string(second_number_deci) + "=";
			break;
		case 3:
			answer_list[index] = first_number_deci + second_number;
			equation = std::to_string(first_number_deci) + "+" + std::to_string(second_number) + "=";
			break;
		default:
			break;
		}
		break;
	case 1:
		switch (deci_decider) {
		case 0:
			answer_list[index] = first_number - second_number;
			equation = std::to_string(first_number) + "-" + std::to_string(second_number) + "=";
			break;
		case 1:
			answer_list[index] = first_number_deci - second_number_deci;
			equation = std::to_string(first_number_deci) + "-" + std::to_string(second_number_deci) + "=";
			break;
		case 2:
			answer_list[index] = first_number - second_number_deci;
			equation = std::to_string(first_number) + "-" + std::to_string(second_number_deci) + "=";
			break;
		case 3:
			answer_list[index] = first_number_deci - second_number;
			equation = std::to_string(first_number_deci) + "-" + std::to_string(second_number) + "=";
			break;
		default:
			break;
		}
		break;
	case 2:
		switch (deci_decider) {
		case 0:
			answer_list[index] = first_number * second_number;
			equation = std::to_string(first_number) + "*" + std::to_string(second_number) + "=";
			break;
		case 1:
			answer_list[index] = first_number_deci * second_number_deci;
			equation = std::to_string(first_number_deci) + "*" + std::to_string(second_number_deci) + "=";
			break;
		case 2:
			answer_list[index] = first_number * second_number_deci;
			equation = std::to_string(first_number) + "*" + std::to_string(second_number_deci) + "=";
			break;
		case 3:
			answer_list[index] = first_number_deci * second_number;
			equation = std::to_string(first_number_deci) + "*" + std::to_string(second_number) + "=";
			break;
		default:
			break;
		}
	default:
		break;
	}

	std::cout << "eq: " << equation << "\n";
	std::cout << "answer: " << answer_list[0];
}

int main(int, char)
{
	Equation();
	vocabulary_trundle(Point(100,100),"Look, i can turn!",Scalar(255,255,255));

	Mat display_area = Mat::zeros(400, 640, CV_8UC3);
	putText(display_area, equation, Point(100, 100), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 1, 1, false);
	imshow("lul", display_area);

	waitKey(0);
	return 0;
}