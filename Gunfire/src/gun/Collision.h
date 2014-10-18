#ifndef GUN_COLLISION_H
#define GUN_COLLISION_H

#include <SFML\Graphics.hpp>

namespace gun
{
	class Collision
	{
	public:
		static bool IsInBounds(const sf::FloatRect& coll_box, const sf::FloatRect& area);
	};
}

#endif