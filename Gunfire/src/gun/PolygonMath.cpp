#include "PolygonMath.h"

sf::Vector2f gun::PolygonMath::Center(const sf::FloatRect& rectangle)
{
	return Center(rectangle.left, rectangle.top, rectangle.width, rectangle.height);
}

sf::Vector2f gun::PolygonMath::Center(float left, float top, float width, float height)
{
	sf::Vector2f center = sf::Vector2f(left, top) + sf::Vector2f(
		width / 2.0f, height / 2.0f);
	return center;
}

sf::FloatRect gun::PolygonMath::Stretch(
	const sf::FloatRect& rectangle, const sf::Vector2f stretch_size)
{
	sf::FloatRect stretched_rect = sf::FloatRect();
	stretched_rect.left = rectangle.left - stretch_size.x;
	stretched_rect.top = rectangle.top - stretch_size.y;
	stretched_rect.width = rectangle.width + stretch_size.x * 2;
	stretched_rect.height = rectangle.height + stretch_size.y * 2;
	return stretched_rect;
}