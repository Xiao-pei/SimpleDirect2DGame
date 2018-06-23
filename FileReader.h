#pragma once
#include<vector>
#include<fstream>

class FileReader
{
public:
	FileReader() = default;
	~FileReader() = default;
	std::vector<float>* getBeats(const wchar_t* path);
	std::vector<int>* getMap(const wchar_t* path);
};
