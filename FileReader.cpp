#include "stdafx.h"
#include "FileReader.h"
#include <string>
using namespace std;


std::vector<float>* FileReader::getBeats(const wchar_t* path)
{
	std::vector<float>* vector = new std::vector<float>;
	fstream in(path);
	string line;
	while (getline(in, line))
	{
		vector->push_back(atof(line.c_str()));
	}
	in.close();
	return vector;
}

std::vector<int>* FileReader::getMap(const wchar_t* path)
{
	std::vector<int>* vector = new std::vector<int>;
	fstream in(path);
	std::string str;
	str.resize(2);
	while (in.peek() != EOF)
	{
		in >> str;
		vector->push_back(atoi(str.c_str()));
	}
	in.close();
	return vector;
}
