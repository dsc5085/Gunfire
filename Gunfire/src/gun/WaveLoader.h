#ifndef GUN_WAVE_LOADER_H
#define GUN_WAVE_LOADER_H

#include <vector>

#include "Wave.h"

namespace gun
{
	class WaveLoader
	{
	public:
		static std::vector<Wave> LoadWaves(const std::string& file_name);

	private:
		static Wave LoadWave(const std::string& file_name);
	};
}

#endif