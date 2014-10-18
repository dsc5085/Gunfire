#ifndef GUN_PATHS_H
#define GUN_PATHS_H

#include <string>

namespace gun
{
	struct Paths
	{
	public:
		// File Constants
		static const std::string SETTINGS_FILE;
		static const std::string HIGH_SCORES_FILE;
		static const std::string WAVES_FILE;

		// Directory Constants
		static const std::string LOGS_DIR;
		static const std::string WAVES_DIR;
		static const std::string TEXTURES_DIR;
		static const std::string ANIMATIONS_DIR;
		static const std::string FONTS_DIR;
		static const std::string SOUNDS_DIR;
	};
}

#endif