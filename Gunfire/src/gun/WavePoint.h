#ifndef GUN_WAVE_POINT_H
#define GUN_WAVE_POINT_H

#include <map>

namespace gun
{
	class WavePoint
	{
	public:
		int duration;
		std::map<std::string, int> objects;
	};
}

#endif