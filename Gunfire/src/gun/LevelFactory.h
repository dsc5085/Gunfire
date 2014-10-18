#ifndef GUN_LEVEL_FACTORY_H
#define GUN_LEVEL_FACTORY_H

#include <vector>

#include "Level.h"

namespace gun
{
	class GameObject;

	class LevelFactory
	{
	public:
		static Level CreateLevel();
	};
}

#endif