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
	string left = "";
	string right = "";

	//open source file
	fstream srFile("in.txt"); //file reader

	//create output files 
	ofstream gts;
	gts.open("gtests.txt", ios::out | ios::trunc);

	string curLine = ""; //current line 
	int lineNum = 0; //line number
	while (getline(srFile, curLine)) {
		lineNum++;
		int idx = curLine.find(",");
		if (idx != -1) { //found ","
			left = curLine.substr(0, idx);
			right = curLine.substr(idx + 1, curLine.size() - idx - 1);

			//gts << "TEST(testCases, Test" << lineNum << ")" << endl;
			//gts << "{" << endl;
			//gts << "	for (int i = 0; i < 100; i++){" << endl;
			//gts << "		" << right << " = i;" << endl;
			//gts << "		SIN_Arbiter_();" << endl;
			//gts << "		EXPECT_EQ(i, " << left << ");" << endl;
			//gts << "	}" << endl;
			//gts << "}" << endl;
			//gts << endl;
		}
		else { //following line tests a bool
			getline(srFile, curLine);
			idx = curLine.find(",");
			left = curLine.substr(0, idx);
			right = curLine.substr(idx + 1, curLine.size() - idx - 1);
			if (right.size() < 60) {
				//gts << "//Bool test" << endl;
				//gts << "TEST(testCases, Test" << lineNum << "True)" << endl;
				//gts << "{" << endl;
				//gts << "	for (int i = 1; i < 100; i++){" << endl;
				//gts << "		" << right << " = i;" << endl;
				//gts << "		SIN_Arbiter_();" << endl;
				//gts << "		EXPECT_TRUE(" << left << ");" << endl;
				//gts << "	}" << endl;
				//gts << "}" << endl;
				//gts << endl;
				//gts << "TEST(testCases, Test" << lineNum << "False)" << endl;
				//gts << "{" << endl;
				//gts << "	" << right << " = 0;" << endl;
				//gts << "	SIN_Arbiter_();" << endl;
				//gts << "	EXPECT_TRUE(!" << left << ");" << endl;
				//gts << "}" << endl;
				//gts << endl;
			}
			else { // Two variables on right side
				if (right.find(" ") == 0) {
					right = right.substr(1, right.size() - 1);
				}
				int idxBlank = right.find(" ");
				gts << "//Bool test" << endl;
				gts << "TEST(testCases, Test" << lineNum << "TrueFirstHalf)" << endl;
				gts << "{" << endl;
				gts << "	for (int i = 1; i < 100; i++){" << endl;
				gts << "		" << right.substr(0,idxBlank) << " = i;" << endl;
				gts << "		SIN_Arbiter_();" << endl;
				gts << "		EXPECT_TRUE(" << left << ");" << endl;
				gts << "	}" << endl;
				gts << "}" << endl;
				gts << endl;
				gts << "TEST(testCases, Test" << lineNum << "FalseFirstHalf)" << endl;
				gts << "{" << endl;
				gts << "	" << right.substr(0, idxBlank) << " = 0;" << endl;
				gts << "	SIN_Arbiter_();" << endl;
				gts << "	EXPECT_TRUE(!" << left << ");" << endl;
				gts << "}" << endl;
				gts << endl;
				gts << "TEST(testCases, Test" << lineNum << "TrueLastHalf)" << endl;
				gts << "{" << endl;
				gts << "	for (int i = 1; i < 100; i++){" << endl;
				gts << "		" << right.substr(idxBlank, right.size() - idxBlank - 1) << " = i;" << endl;
				gts << "		SIN_Arbiter_();" << endl;
				gts << "		EXPECT_TRUE(" << left << ");" << endl;
				gts << "	}" << endl;
				gts << "}" << endl;
				gts << endl;
				gts << "TEST(testCases, Test" << lineNum << "FalseLastHalf)" << endl;
				gts << "{" << endl;
				gts << "	" << right.substr(idxBlank, right.size() - idxBlank - 1) << " = 0;" << endl;
				gts << "	SIN_Arbiter_();" << endl;
				gts << "	EXPECT_TRUE(!" << left << ");" << endl;
				gts << "}" << endl;
				gts << endl;

			}
			
		}
		reportProgress(lineNum);
	}
	srFile.close();
	gts.close();
}

