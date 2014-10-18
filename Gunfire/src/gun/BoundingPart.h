#ifndef GUN_BOUNDING_PART_H
#define GUN_BOUNDING_PART_H

#include <SFML\Graphics.hpp>

#include "Part.h"

namespace gun
{
	class BoundingPart : public Part
	{
	public:
		BoundingPart(const sf::FloatRect& bounds_area);
		BoundingPart(const std::vector<sf::FloatRect>& bounds_area);

		void Update(double dt);

	private:
		std::vector<sf::FloatRect> bounds_;
	};
}

#endif