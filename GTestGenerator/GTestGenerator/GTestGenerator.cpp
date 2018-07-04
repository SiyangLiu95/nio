// GTestGenerator.cpp : Generates GTests for variable comparison
// NIO Automotives
// Siyang Liu (6796)
// 2018-06-21

#include "stdafx.h"
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

void reportProgress(int& num) {
	//keep track of progress
	if (num % 500 == 0) {
		cout << "processed" << num << "lines" << endl;
	}
}

int main()
{
	vector<string> leftVar(0); //store variable names
	vector<string> rightVar(0);
	string left = "";
	string right = "";
	//open source file
	fstream srFile("in.csv"); //file reader
	string curLine = ""; //current line 
	int lineNum = 0; //line number
	while (getline(srFile, curLine)) {
		int idx = curLine.find(",");
		if (idx != -1) {
			lineNum++;
			left = curLine.substr(0, idx);
			leftVar.push_back(left);
			right = curLine.substr(idx + 1, curLine.size() - idx - 1);
			rightVar.push_back(right);
		}
		reportProgress(lineNum);
	}
	srFile.close();

	//create output files 
	ofstream gts;
	gts.open("gtests.txt", ios::out | ios::trunc);
	for (int i = 0; i < lineNum; i++) {
		gts << "TEST(varTest, Test" << i+1 << ")" << endl;
		gts << "{" << endl;
		gts << "EXPECT_EQ(" << leftVar[i] << ", " << rightVar[i] << ");" << endl;
		gts << "}" << endl;
		gts << endl;
		reportProgress(i);
	}
	gts.close();
}

