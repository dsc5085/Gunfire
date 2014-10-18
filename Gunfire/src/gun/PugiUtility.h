#ifndef GUN_PUGI_UTILITY_H
#define GUN_PUGI_UTILITY_H

#include "pugi\pugixml.hpp"

namespace gun
{
	class PugiUtility
	{
	public:
		static pugi::xml_node LoadRoot(const char* file_name, const char* root_name);
	};
}

#endif