// opencvTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;

#define w 900 //define window size

struct obj {
	int classification;
	float centerX;
	float centerY;
	float length;
	float width;
	float orientation;
	float relVelX;
	float relVelY;
	obj() {

		classification	= 5;
		centerX = (float)76.1921;
		centerY = (float)4.28925;
		length = (float)4.17203;
		width = (float)1.73374;
		orientation = (float)0.0730224;
		relVelX = (float)4.44;
		relVelY = (float)0.33;
	}
};

void myRotate(float& x, float& y, float angle) { //rotate 2D coordinate by angle
	float tmpX = cos(angle) * x + sin(angle) * y;
	float tmpY = -sin(angle) * x + cos(angle) * y;
	x = tmpX;
	y = tmpY;
}

Scalar randomColor()
{
	RNG rng(0xFFFFFFFF);
	int icolor = (unsigned)rng;
	return Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
}

void addObj(Mat img, obj o) {
	// find the coordinates of two edge points of obj box in ibeo coordinate
	myRotate(o.centerX, o.centerY, -o.orientation);
	float pt1x = o.centerX - o.length / (float)2.00000;
	float pt2x = o.centerX + o.length / (float)2.00000;
	float pt1y = o.centerY - o.width / (float)2.00000;
	float pt2y = o.centerY + o.width / (float)2.00000;
	myRotate(pt1x, pt1y, o.orientation);
	myRotate(pt2x, pt2y, o.orientation);
	//std::cerr << o.orientation << std::endl;
	std::cerr << pt1x << std::endl;
	std::cerr << pt1y << std::endl;
	std::cerr << pt2x << std::endl;
	std::cerr << pt2y << std::endl;
	std::cerr << std::endl;

	//convert ibeo coordinate to opencv mat val
	pt1x *= 6;
	pt1y *= 6;
	pt2x *= 6;
	pt2y *= 6; //900 pixels represents 150m irl.
	std::cerr << pt1x << std::endl;
	std::cerr << pt1y << std::endl;
	std::cerr << pt2x << std::endl;
	std::cerr << pt2y << std::endl;
	std::cerr << std::endl;

	std::cerr << "x1 = " << (float)w / 2.00000 - pt1y << std::endl;
	std::cerr << "y1 = " << (float)w - pt1x << std::endl;
	std::cerr << "x2 = " << (float)w / 2.00000 - pt2y << std::endl;
	std::cerr << "y2 = " << (float)w - pt2x << std::endl;
	std::cerr << std::endl;

	rectangle(img, 
		Point(w / 2 - (int)pt1y, w - (int)pt1x), 
		Point(w / 2 - (int)pt2y, w - (int)pt2x), 
		randomColor(), 2, LINE_8, 0);

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
	std::cerr << "fullFOV = " << fullFOV << std::endl;
	addLine(img, Point(w / 2, w), fullFOV / 2, 800, Scalar(128, 138, 125), 1);
	addLine(img, Point(w / 2, w), -fullFOV / 2, 800, Scalar(128, 138, 125), 1);
}

int main(const int argc, const char** argv) {
	char fovTitle[] = "ECU IDC File Replay";
	Mat fov = Mat::zeros(w + 20, w, CV_8UC3); // leave space at bottom
	setBackground(fov);// draw coordinates and background

	//draw object box
	obj dummyObj;
	addObj(fov, dummyObj);


	imshow(fovTitle, fov);
	moveWindow(fovTitle, w, 0);

	waitKey(0);
	return(0);
}

