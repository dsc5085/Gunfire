#ifndef GUN_ANIMATION_LOADER_H
#define GUN_ANIMATION_LOADER_H

#include "pugi\pugixml.hpp"
#include "Animation.h"

namespace gun
{
	class AnimationLoader
	{
	public:
		static std::map<int, gun::Animation> Load(const std::string& file_name);

	private:
		static gun::Animation GetFramesByBlockFormat(
			std::vector<pugi::string_t> data_values);
		static gun::Animation GetFramesByLineFormat(
			std::vector<pugi::string_t> data_values); 
	};
}

#endif