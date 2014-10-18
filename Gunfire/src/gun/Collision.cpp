#include "Collision.h"

bool gun::Collision::IsInBounds(
	const sf::FloatRect& coll_box, const sf::FloatRect& area)
{
	return coll_box.top >= area.top
		&& coll_box.top + coll_box.height <= area.top + area.height
		&& coll_box.left >= area.left
		&& coll_box.left + coll_box.width <= area.left + area.width;
}