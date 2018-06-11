#include "stdafx.h"
#include "BeatsReader.h"
#include <string>
using namespace std;

BeatsReader::BeatsReader()
{
	vector = new std::vector<float>;
}


BeatsReader::~BeatsReader()
{
	delete vector;
}

std::vector<float>* BeatsReader::getBeats(const wchar_t* path)
{
	fstream in(path);
	string line;
	while (getline(in, line))
	{
		vector->push_back(atof(line.c_str()));
	}
	in.close();
	return vector;
}
