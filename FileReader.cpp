#include "stdafx.h"
#include "FileReader.h"
#include <string>
using namespace std;


std::vector<float>* FileReader::getBeats(const wchar_t* path)
{
	std::vector<float> *vector = new std::vector<float>;
	fstream in(path);
	string line;
	while (getline(in, line))
	{
		vector->push_back(atof(line.c_str()));
	}
	in.close();
	return vector;
}

std::vector<int>* FileReader::getMap(char const* path)
{
	std::vector<int> *vector = new std::vector<int>;
	FILE *f = fopen(path, "r");
	std::string str;
	str.resize(3);
	while (fscanf(f, "%s", &str[0]) != EOF) {
		vector->push_back(atoi(str.c_str()));
	}
	return vector;
}
