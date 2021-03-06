// opencvTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;

#define w 900 //define window size
#define unit 50 //define each step irl

struct myObj {
	int classification;
	float centerX;
	float centerY;
	float length;
	float width;
	float orientation;
	float relVelX;
	float relVelY;
	myObj() { // dummy obj
		classification	= 5;
		centerX = (float)9.41556;
		centerY = (float)3.76033;
		length = (float)4.15154;
		width = (float)1.08806;
		orientation = (float)-0.00803664;
		relVelX = (float)12.76;
		relVelY = (float)-0.08;
	}
	myObj(
		int cl,
		float cX,
		float cY,
		float lth,
		float wth,
		float otn,
		float rVX,
		float rVY
	) {
		this->classification = cl;
		this->centerX = cX;
		this->centerY = cY;
		this->length = lth;
		this->width = wth;
		this->orientation = otn;
		this->relVelX = rVX;
		this->relVelY = rVY;
	}
};

void myRotate(float& x, float& y, float angle) { //rotate 2D coordinate by angle
	float tmpX = cos(angle) * x + sin(angle) * y;
	float tmpY = -sin(angle) * x + cos(angle) * y;
	x = tmpX;
	y = tmpY;
}

Scalar myColor(int& c)
{
	if ((c == 5)
		|| (c == 6)) { //car & truck
		return Scalar(0, 255, 0); //green
	}
	else if (c == 3) { //ped
		return Scalar(0, 255, 255); // green + red = yellow
	}
	else if (c == 4) {
		return Scalar(0, 0, 255); // red
	}
	else if (c == 15) { //MBike
		return Scalar(255, 0, 255); // violet 
	}
	return Scalar(0, 122, 255); // orange
}

void addObj(Mat& img, myObj o) {
	// find the coordinates of obj box in ibeo coordinate
	myRotate(o.centerX, o.centerY, -o.orientation);
	float pt1x = o.centerX - o.length / (float)2.00000;
	float pt2x = o.centerX + o.length / (float)2.00000;
	float pt1y = o.centerY - o.width / (float)2.00000;
	float pt2y = o.centerY + o.width / (float)2.00000;
	float arrowx = o.centerX + +o.length / (float)2.00000 + sqrtf(o.relVelX * o.relVelX + o.relVelY * o.relVelY);
	float arrowy = o.centerY; 
	float cx = o.centerX;
	float cy = o.centerY;
	myRotate(o.centerX, o.centerY, o.orientation);
	myRotate(pt1x, pt1y, o.orientation);
	myRotate(pt2x, pt2y, o.orientation);
	myRotate(arrowx, arrowy, o.orientation);
	myRotate(cx, cy, o.orientation);
	

	std::cerr << "coordinate in ibeo system:" << std::endl;
	std::cerr << o.orientation << std::endl;
	std::cerr << pt1x << std::endl;
	std::cerr << pt1y << std::endl;
	std::cerr << pt2x << std::endl;
	std::cerr << pt2y << std::endl;
	std::cerr << arrowx << std::endl;
	std::cerr << arrowy << std::endl;
	std::cerr << cx << std::endl;
	std::cerr << cy << std::endl;
	std::cerr << std::endl;

	//convert ibeo coordinate to opencv mat val
	pt1x *= w / unit / 3;
	pt1y *= w / unit / 3;
	pt2x *= w / unit / 3;
	pt2y *= w / unit / 3; //900 pixels represents 150m irl.
	arrowx *= w / unit / 3; 
	arrowy *= w / unit / 3;
	cx *= w / unit / 3;
	cy *= w / unit / 3;
	std::cerr << "mat values:" << std::endl;
	std::cerr << pt1x << std::endl;
	std::cerr << pt1y << std::endl;
	std::cerr << pt2x << std::endl;
	std::cerr << pt2y << std::endl;
	std::cerr << arrowx << std::endl;
	std::cerr << arrowy << std::endl;
	std::cerr << cx << std::endl;
	std::cerr << cy << std::endl;
	std::cerr << std::endl;

	std::cerr << "mat locations:" << std::endl;
	std::cerr << "x1 = " << (float)w / 2.00000 - pt1y << std::endl;
	std::cerr << "y1 = " << (float)w - pt1x << std::endl;
	std::cerr << "x2 = " << (float)w / 2.00000 - pt2y << std::endl;
	std::cerr << "y2 = " << (float)w - pt2x << std::endl;
	std::cerr << "arrow x = " << (float)w / 2.00000 - arrowy << std::endl;
	std::cerr << "arrow y = " << (float)w - arrowx << std::endl;
	std::cerr << "center x = " << (float)w / 2.00000 - cy << std::endl;
	std::cerr << "center y = " << (float)w - cx << std::endl;
	std::cerr << std::endl;

	rectangle(img, 
		Point(w / 2 - (int)pt1y, w - (int)pt1x), 
		Point(w / 2 - (int)pt2y, w - (int)pt2x), 
		myColor(o.classification),
		2, LINE_8, 0
	);
	arrowedLine(img,
		Point(w / 2 - (int)cy, w - (int)cx), //box center location
		Point(w / 2 - (int)arrowy, w - (int)arrowx),
		myColor(o.classification),
		1, LINE_8, 0,
		0.1//tip length
	);
}

void addCircle(Mat img, Point center)
{
	circle(img,
		center,
		w / 32,
		Scalar(0, 0, 255),
		FILLED,
		LINE_8);
}

void addLine(Mat img, Point start, float angle, int length, Scalar color, int thickness)//angle in rad, left +, right -, center forward 0
{
	int dx = (int)(-sin(angle) * (float)length);
	int dy = (int)(-cos(angle) * (float)length);
	//std::cerr << dx << std::endl;
	//std::cerr << dy << std::endl;
	line(img, start,
		Point(start.x + dx, start.y + dy),
		color, thickness, LINE_8);
}

void setBackground(Mat img) {
	//parse fov into 3*3 grid, each block represents 50m*50m irl.
	line(img, Point(0, w / 3), Point(w, w / 3), Scalar(128, 138, 125), 1, LINE_8);
	line(img, Point(0, w * 2 / 3), Point(w, w * 2 / 3), Scalar(128, 138, 125), 1, LINE_8);
	line(img, Point(w / 3, 0), Point(w / 3, w + 20), Scalar(128, 138, 125), 1, LINE_8);
	line(img, Point(w * 2 / 3, 0), Point(w * 2 / 3, w + 20), Scalar(128, 138, 125), 1, LINE_8);
	//origin
	line(img, Point(w / 2, w), Point(w / 2, w * 5 / 6), Scalar(0, 0, 255), 2, LINE_8);
	line(img, Point(w / 2, w), Point(w / 3, w), Scalar(0, 255, 0), 2, LINE_8);
	//FOV limits
	float fullFOV = (float)145.000 / (float)180.000 * (float)3.14159;
	//std::cerr << "fullFOV = " << fullFOV << std::endl;
	addLine(img, Point(w / 2, w), fullFOV / 2, 800, Scalar(128, 138, 125), 1);
	addLine(img, Point(w / 2, w), -fullFOV / 2, 800, Scalar(128, 138, 125), 1);
}

int main(const int argc, const char** argv) {
	char fovTitle[] = "ECU IDC File Replay";
	Mat fov = Mat::zeros(w + 20, w, CV_8UC3); // leave space at bottom
	setBackground(fov);// draw coordinates and background
	imshow(fovTitle, fov);
	// moveWindow(fovTitle, w, 0);

	//draw object box
	myObj dummyObj;
	myObj obj1 = myObj(3, 72.9318, 4.93623, 4.15154, 2.6134, 0.0854873, 4.6, -0.3);
	Mat frame = fov.clone();
	std::cerr << "ready" << std::endl;
	int flag = 1;
	std::cerr << "go" << std::endl;
	while (true) {
		if (flag == 1) {
			flag = 0;
			std::cerr << "1" << std::endl;
			frame = fov.clone();
			addObj(frame, dummyObj);
			imshow(fovTitle, frame);
			waitKey(0);
		}
		else {
			flag = 1;
			std::cerr << "2" << std::endl;
			frame = fov.clone();
			addObj(frame, obj1);
			imshow(fovTitle, frame);
			waitKey(0);
		}
	}
	
	waitKey(0);
	return(0);
}

