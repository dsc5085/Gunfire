#ifndef GUN_POLYGON_MATH_H
#define GUN_POLYGON_MATH_H
#define _USE_MATH_DEFINES

#include <math.h>
#include <SFML\Graphics.hpp>

namespace gun
{
	class PolygonMath
	{
	public:
		static sf::Vector2f Center(const sf::FloatRect& rectangle);
		static sf::Vector2f Center(float left, float top, float width, float height);

		// Increase the size of the rectangle outwards by the x and y values
		// of stretch_size.
		static sf::FloatRect Stretch(const sf::FloatRect& rectangle, 
			const sf::Vector2f stretch_size);
	};
}

#endif