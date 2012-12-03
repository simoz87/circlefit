#include "Point2Dvector.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

Point2Dvector::Point2Dvector(const std::string &filename)
{
	ifstream inputfile;
	string line;
	inputfile.open(filename);
	if (inputfile.is_open()){
		while (inputfile.good()){
			float x, y;
			getline (inputfile, line);
			istringstream sline(line);
			sline>>x>>y;
			push_back (Point2D(x,y));

		}
		inputfile.close();
	}
	else{
		string msg="File ";
		msg.append(filename).append(" not found!");
		throw runtime_error(msg);
	}
}


Point2Dvector::~Point2Dvector(void)
{
}
