#include <fstream>

#include "FileIO.h"

std::vector<std::string> gun::FileIO::LoadLines(const std::string& file_name)
{
	std::ifstream file(file_name);
	std::vector<std::string> layout = std::vector<std::string>();
	std::string line;

	while(std::getline(file, line))
	{
		layout.push_back(line);
	}

	return layout;
}