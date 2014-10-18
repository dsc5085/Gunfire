#ifndef GUN_LEVEL_H
#define GUN_LEVEL_H

#include <SFML\Graphics.hpp>

#include "Wave.h"

namespace gun
{
	class GameObject;

	class Level
	{
	public:
		sf::FloatRect area;
		std::vector<Wave> waves;
	};
}

#endif