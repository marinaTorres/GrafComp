#pragma once
#include <string>

class inputFile {
public:
	bool read(std::string fileName);
	std::string  getContents();
private:
	std::string _contents;
};