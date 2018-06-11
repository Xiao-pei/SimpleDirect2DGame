#pragma once
#include<vector>
#include<fstream>
class BeatsReader
{
private:
	std::vector<float> *vector;
public:
	BeatsReader();
	~BeatsReader();
	std::vector<float> * getBeats(const wchar_t* path);
};

