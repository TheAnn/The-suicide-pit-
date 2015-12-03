/*
Author: Atanas Nikolov, MTA15345
Email Adress: aniko14@student.aau.dk
Description: Math game test realm.
Update 1.0: Detect a hand and extract information such as size, gesture, and colour.
Update 1.1: Created moving answer boxes in the center of the field.
Update 1.2: Created a hand object to check for the user actions.
Update 1.3: Created a box to check if the selected answer is correct.
Update 1.4: Created an object to generate random equations and answers.
Update 1.5: Answer objects can now be grabed and draged.
Update 1.6: Answer objects can now be grabed and draged only when the hand is closed on top of the object.
*/

#define _USE_MATH_DEFINES
#include "opencv2/opencv.hpp"
#include <cmath>
#include <ctime>

using namespace cv;

// General variables, exchange data between IP and game
	Point2f center[10],
		point_list[11],
		center_mass;
	Mat background,
		frame,
		display_area;
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
	int blob_state[10];
	float speed = 0,
		answer_list[] = { 1, 2, 0, 0, 5, 6, 7, 8, 9, 10, 11, 12 };
	bool new_eq[] = { true, true, true, true };
	int colour_value = 11;
class Answer
{

public:
	void set(Point2f , float );
	void move(Point2f );
	void draw();
	Point2f get_center();
private:
	Point2f answer_center;
	float answer_value;
	Scalar answer_colour;
};

class Rotator
{
public:
	Rotator(Mat , Point2f ,int );
	void circulate();
private:
	int angle,
		radius;
	Mat size_frame;
	
};

class Hand
{
public:
	Hand(int );
	void set(int );
	void grab();
	bool get_hold();
	int get_holded();
private:
	Point2f hand_center;
	int hand_state,
		colour_bellow,
		hand_colour,
		holded;
	bool open = true,
		 hold = false;
};

class DropBox
{
public:
	DropBox(int , Point2f , Scalar);
	void check();
	void draw();
private:
	int index,
		correct_answer;
	Point2f location,
		location_op;
	Scalar box_colour;
};

class Equation
{
public:
	Equation(Point2f , Scalar ,int );
	void generate();
	void draw();
	int get_answer();
private:
	std::string equation;
	int correct_answer,
		index;
	Point2f location,
		location_op;
	Scalar box_colour;
};

class Score
{
public:
	Score(int , Point2f, Scalar);
	void gain();
	void draw();
private:
	int index,
		score;
	Point2f location;
	Scalar box_colour;
};


class ImageProcessing																			//Image processing class, contains the functions to find objects in the image.
{

public:
	void thresholding();																		//Remove the background and threshold the image.

	void contour();																				//Find the external contours.

	void eliminteContours();																	//Eliminate too short or too long contours and extract data from the rest
																								//Add more conditions to the if/else statement to remove noise.

	void blobArea();																			//Caculate area of the blob.

	void circularity();																			//Calculate the circularity of the blob.

	void blobColour();																			//Find the colour of the blob 1-blue, 2-green, 3-red.

	void blobState();																			//Get the state of the blob.

	void draw();																				//Draw contours.

	void whiteBalance(Point2f );																//Colour balance, adjusts all colours to be equal at white.

	int getColour(Point2f , int);																//Get the colour from the 9 central pixels.

private:
	Mat thresholded,
		gray_frame,
		subtracted,
		contour_frame;
	std::vector<std::vector<cv::Point>> contours;
	int min_contour = 100,																		//Minimum size of the contour to be counted as objet of interest.
		max_contour = 650,																		//Maximum size of the contour to be counted as objet of interest.
		min_area = 1200,
		max_area = 7400,
		blob_area,
		blob_colour,
		vec;
	float radius;
	double rec_y,
		rec_x,
		rec_height,
		rec_width,
		blob_perimeter,
		blob_sqrt_area,
		blob_circularity,
		blob_circularity_precision = 1.5;														//Circularity threshold, determine state/gesture.



};

int main(int, char)
{

	ImageProcessing IPGod;
	
	namedWindow("Game", CV_WINDOW_AUTOSIZE);
	namedWindow("IP", CV_WINDOW_AUTOSIZE);

	VideoCapture cap(2);
	if (!cap.isOpened())
		return -1;
	for (;;)
	{
		Mat a;
		cap >> a;
		imshow("SODA", a);
		if (waitKey(30)>=0)
			break;
	}
	cap >> background;
	display_area = Mat::zeros(background.size(), background.type());
	cvtColor(background, background, CV_RGB2GRAY);
	Point2f image_center(2*background.rows/3,2*background.cols/3);

	Answer answer[12];
	Rotator Rot(background,image_center,background.rows/2.2);
	DropBox BoxP1(2, Point2f(0, 2 * display_area.rows / 5), Scalar(0, 100, 0));
	DropBox BoxP2(3, Point2f(11 * display_area.cols / 12, 2 * display_area.rows / 5), Scalar(0, 0, 255));
	Equation Eq1(Point2f(50, 50), Scalar(0, 255, 0),2);
	Equation Eq2(Point2f(11 * display_area.cols / 12-50, 4 * display_area.rows / 5-50), Scalar(0, 0, 255),3);
	Score Sc1(2, Point2f(50, 4 * display_area.rows / 5 - 50), Scalar(0, 255, 0));
	Score Sc2(3, Point2f(11 * display_area.cols / 12 - 50, 50), Scalar(0, 0, 255));
	Hand P1(2);
	Hand P2(3);

	for (;;)
	{
		//preparation
		cap >> frame;
		Mat hsv_frame;
		for (int i = 0; i < 10; i++)
			center[i] = center[i] * 0;
		
		//use of image processing
		IPGod.thresholding();
		IPGod.contour();
		IPGod.eliminteContours();
		
		//use of game code
		if (new_eq[2]){
			Eq1.generate();
			Sc1.gain();
		}
		if (new_eq[3]){
			Eq2.generate();
			Sc2.gain();
		}
		Rot.circulate();
		P1.set(2);
		P1.grab();
		P2.set(3);
		P2.grab();
		for (int i = 0; i < 12; i++)
		{
			if (P1.get_hold() && P1.get_holded() == answer_list[i]+colour_value)
			{
				float distance1 = sqrt((center[2].x - answer[i].get_center().x)*(center[2].x - answer[i].get_center().x) + (center[2].y - answer[i].get_center().y)*(center[2].y - answer[i].get_center().y));
				if (distance1 < 40)
					answer[i].set(center[2], answer_list[i]);
				else
					answer[i].set(point_list[i], answer_list[i]);
			}
			else if (P2.get_hold() && P2.get_holded() == answer_list[i] + colour_value)
			{
				float distance2 = sqrt((center[3].x - answer[i].get_center().x)*(center[3].x - answer[i].get_center().x) + (center[3].y - answer[i].get_center().y)*(center[3].y - answer[i].get_center().y));
				if (distance2 < 40)
					answer[i].set(center[3], answer_list[i]);
				else
					answer[i].set(point_list[i], answer_list[i]);
			}else 
				answer[i].set(point_list[i], answer_list[i]);
		}

		//draw stuff
		display_area = Mat::zeros(frame.size(), frame.type());
		IPGod.draw();
		for (int i = 0; i < 12; i++)
		{
			answer[i].draw();
		}
		
		BoxP1.draw();
		BoxP2.draw();
		Eq1.draw();
		Eq2.draw();
		Sc1.draw();
		Sc2.draw();
		imshow("Game", display_area);
		BoxP1.check();
		BoxP2.check();
		//brake option
		if (waitKey(1) >= 0){
			break;
		}
	}
	return 0;
}
//Answer
void Answer::set(Point2f center, float value)
{
	answer_center = center;
	answer_value = value;
	answer_colour = Scalar(answer_value + colour_value, 0, 0);

}
Point2f Answer::get_center()
{
	return answer_center;
}
void Answer::move(Point2f center)
{
	answer_center = center;
}
void Answer::draw()
{
	circle(display_area, answer_center, 25, answer_colour, CV_FILLED);
	std::string ansV = std::to_string(answer_value);//change to answer_value.
	ansV.erase(ansV.find_last_not_of('0'), std::string::npos);
	putText(display_area, ansV, answer_center - Point2f(20, -10), FONT_HERSHEY_SIMPLEX, 1, CV_RGB(answer_colour.val[0], 255, 255), 1, 1, false);
}

//Rotator
Rotator::Rotator(Mat frame, Point2f start, int r)
{
	size_frame = frame;
	point_list[0] = start;
	radius = r;
}
void Rotator::circulate()
{
	angle = (2 * M_PI) / 6;
	
	for (int i = 0; i < 6; i++)
	{	
		point_list[i].x = radius * sin(angle * i + speed) + size_frame.cols / 2;
		point_list[i].y = radius * cos(angle * i + speed) + size_frame.rows / 2;
	}
	for (int i = 6; i < 12; i++)
	{
		point_list[i].x = radius / 2 * sin(angle * i - speed) + size_frame.cols / 2;
		point_list[i].y = radius / 2 * cos(angle * i - speed) + size_frame.rows / 2;		
	}
	speed = speed + 0.01;
}

//Hand
Hand::Hand(int index)
{
	hand_center = center[index];
	hand_state = blob_state[index];
	hand_colour = index;
}
bool Hand::get_hold()
{
	return hold;
}
int Hand::get_holded()
{
	return holded;
}
void Hand::set(int index)
{
	hand_center = center[index];
	hand_state = blob_state[index];
	hand_colour = index;
}
void Hand::grab()
{

	if (hand_state==1&&open)//remove open if not working
	{
		open = false;
		colour_bellow = display_area.at<Vec3b>(hand_center)[0];
		if (true)
		{
			hold = true;
			holded = colour_bellow;
			
		}
	}
	if (hand_state==2||new_eq[hand_colour]){
		hold = false;
		open = true;
	}
}

//DropBox
DropBox::DropBox(int in, Point2f loc, Scalar colour)
{
	correct_answer = answer_list[in];
	index = in;
	location = loc;
	location_op=location+Point2f(display_area.cols / 12, display_area.rows / 5);
	box_colour = colour;
	
}
void DropBox::check()
{
	
	for (int y = location.y; y < location_op.y; y++)
	{
		for (int x = location.x; x < location_op.x; x++)
		{
			if (display_area.at<Vec3b>(y, x)[0] == answer_list[index] + colour_value)
			{
				new_eq[index] = true;
				break;
				break;
			}
		}
	}
}
void DropBox::draw()
{
	rectangle(display_area, location, location_op, box_colour, 2);
}

//Equation
Equation::Equation(Point2f loc, Scalar colour,int in)
{
	index = in;
	location = loc;
	box_colour = colour;
}
void Equation::generate()
{
	new_eq[index] = false;
	srand(time(NULL) + index);
	int first_number;
	int second_number;
	int operation;
	bool valid = false;
	do{
		first_number = 1 + rand() % 10;
		second_number = 1 + rand() % 10;
		operation = rand() % 3;
		if (operation == 2 && first_number*second_number > 55)
			valid = true;
		else
			valid = false;
	} while (valid);

	switch (operation) {
	case 0:
		answer_list[index] = first_number + second_number;
		answer_list[index+8] = first_number + second_number;
		equation = std::to_string(first_number) + "+" + std::to_string(second_number) + "=";
		break;
	case 1:
		answer_list[index] = first_number - second_number;
		answer_list[index+8] = first_number - second_number;
		equation = std::to_string(first_number) + "-" + std::to_string(second_number) + "=";
		break;
	case 2:
		answer_list[index] = first_number * second_number;
		answer_list[index+8] = first_number * second_number;
		equation = std::to_string(first_number) + "*" + std::to_string(second_number) + "=";
		break;
	default:

		break;
	}
}
void Equation::draw()
{
	putText(display_area, equation, location , FONT_HERSHEY_SIMPLEX, 1, box_colour, 1, 1, false);
}

//Score
Score::Score(int in, Point2f loc, Scalar colour)
{
	index = in;
	location = loc;
	box_colour = colour;
	score = -1;
}
void Score::gain()
{
	score++;
}
void Score::draw()
{
	std::string string_score = std::to_string(score);
	putText(display_area, string_score, location, FONT_HERSHEY_SIMPLEX, 1, box_colour, 1, 1, false);
}
//ImageProcessing

void ImageProcessing::eliminteContours()
{
	std::vector<std::vector<cv::Point>>::
		const_iterator itc(contours.begin());
	vec = 0;
	while (itc != contours.end())
	{
		if (itc->size() < min_contour || itc->size() > max_contour)
			itc = contours.erase(itc);
		else
		{

			Rect r0(boundingRect(cv::Mat(contours[vec])));

			rec_x = r0.x;
			rec_y = r0.y;
			rec_height = r0.height;
			rec_width = r0.width;

			blob_perimeter = itc->size();
			blobArea();
			
			if (blob_area < min_area || blob_area>max_area)
				itc = contours.erase(itc);
			else
			{
				blobColour();
				if (blob_colour==1)
				{
					itc = contours.erase(itc);
				}
				else{
					minEnclosingCircle(Mat(contours[vec]), center[0], radius);
					circularity();

					center[blob_colour] = center_mass;
					blobState();
					++vec;
					++itc;
				}
			}
		}
	}
}
void ImageProcessing::thresholding()
{
	cvtColor(frame, gray_frame, CV_RGB2GRAY);
	
	subtract(gray_frame, background, subtracted, noArray(), -1);
	medianBlur(subtracted, subtracted, 5);
	threshold(subtracted, subtracted, 10, 255, CV_THRESH_BINARY);
	dilate(subtracted, thresholded, element);
	erode(thresholded, thresholded, element);

}
void ImageProcessing::contour()
{
	contour_frame = thresholded.clone();
	findContours(contour_frame,
		contours,
		CV_RETR_EXTERNAL,
		CV_CHAIN_APPROX_NONE);

}
void ImageProcessing::blobArea()
{
	double yMax = rec_y + rec_height - 1;
	double xMax = rec_x + rec_width - 1;
	blob_area = 1;
	int center_mass_x = 0,
		center_mass_y = 0;
	center_mass = center_mass*0;
	for (int y = rec_y; y < yMax; y++)
	{
		for (int x = rec_x; x < xMax; x++)
		{
			if (thresholded.at<unsigned char>(y, x)>0)
			{
				blob_area++;
				center_mass_x =center_mass_x+x,
				center_mass_y =center_mass_y+y;
			}
		}
	}
	center_mass.x = center_mass_x / blob_area;
	center_mass.y = center_mass_y / blob_area;
}
int ImageProcessing::getColour(Point2f center, int ch)
{
	int color = 0;
	for (int i = -1; i < 2; i++)
	{
		if (!center.x + i<0 || !center.x + i>640 || !center.y + i<0 || !center.y + i>480)
			color = +frame.at<Vec3b>(center.y - 1, center.x + i)[ch] +
			frame.at<Vec3b>(center.y, center.x + i)[ch] +
			frame.at<Vec3b>(center.y + 1, center.x + i)[ch];
	}

	return color;
}
void ImageProcessing::blobColour()
{
	int blue = getColour(center_mass, 0)-30;
	int green = getColour(center_mass, 1);
	int red = getColour(center_mass, 2)+20;
	 
	std::cout << blue << " " << green << " " << red << "\n";
	if (blue > green)
		if (blue > red)
			blob_colour = 1;
		else
			blob_colour = 3;
	else if (green > red)
		blob_colour = 2;
	else
		blob_colour = 3;

}
void ImageProcessing::blobState()
{
	if (blob_circularity < blob_circularity_precision)
		blob_state[blob_colour] = 1;
	else
		blob_state[blob_colour] = 2;
}
void ImageProcessing::circularity()
{
	blob_sqrt_area = 2 * sqrt(3.14*blob_area);
	blob_circularity = blob_perimeter / blob_sqrt_area;
}
void ImageProcessing::draw()
{


	Mat result(frame.size(), CV_8UC3, cv::Scalar(0, 0, 0));
	for (int i = 1; i < 4; i++)
	{
		std::string vecS = std::to_string(i);
		putText(result, vecS, center[i], FONT_HERSHEY_SIMPLEX, 1, CV_RGB(255, 255, 255), 3, 8, false);
		if (blob_state[i] == 2)
		{
			circle(display_area, center[i], 5, CV_RGB(0, 255, 0), CV_FILLED);
			circle(result, center[i], 5, CV_RGB(0, 255, 0), CV_FILLED);
		}
		else
		{
			circle(display_area, center[i], 5, CV_RGB(0, 0, 255), CV_FILLED);
			circle(display_area, center[i], 5, CV_RGB(0, 0, 255), CV_FILLED);
		}
	}


	drawContours(result, contours,
		-1,
		cv::Scalar(255, 255, 255),
		1);
	imshow("IP", result);
	imshow("SB", subtracted);
	imshow("TH", thresholded);
}


