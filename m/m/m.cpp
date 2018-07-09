// m.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <math.h>

void rotate(float& x, float& y, float angle) {
	float tmpX = cos(angle) * x + sin(angle) * y;
	float tmpY = - sin(angle) * x + cos(angle) * y;
	x = tmpX;
	y = tmpY;
}

int main()
{
	float x = 0.000;
	float y = 1.000;
	rotate(x, y, 0.78540); //rotate 45 degree to the left
	std::cout << x << std::endl;
	std::cout << y << std::endl;
    return 0;
}

