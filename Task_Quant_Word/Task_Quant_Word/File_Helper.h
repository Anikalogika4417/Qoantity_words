#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class File_Helper
{
public:
	File_Helper();

	int Get_Status();
	vector<string> Get_Data();
private:
	void Enter_Path();
	int Checking_Path();

	int status;
	ifstream inputFile;
	string path{};
	vector<string> data{};
};

