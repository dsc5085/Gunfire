#ifndef GUN_FILE_IO_H
#define GUN_FILE_IO_H

#include <string>
#include <vector>

namespace gun
{
	class FileIO
	{
	public:
		static std::vector<std::string> LoadLines(const std::string& file_name);
	};
}

#endif