#include <math.h>

#include "Text.h"
#include "PolygonMath.h"

bool gun::Text::is_expired() const
{
	bool is_expired = true;

	for (unsigned int i = 0; i < decorators_.size(); i++)
	{
		if (!decorators_[i].is_expired())
		{
			is_expired = false;
			break;
		}
	}

	return is_expired;
}

void gun::Text::set_center(const sf::Vector2f position)
{
	sf_text_.setPosition(position - PolygonMath::Center(sf_text_.getGlobalBounds()));
}

gun::Text::Text()
{
}

gun::Text::Text(sf::Text sf_text)
	: sf_text_(sf_text)
{
}

void gun::Text::AddDecorator(TextDecorator* decorator)
{
	decorators_.push_back(decorator);
}

void gun::Text::Update(double dt)
{
	for (unsigned int i = 0; i < decorators_.size(); i++)
	{
		decorators_[i].Update(*this, dt);
	}
}

void gun::Text::Draw(sf::RenderWindow& window)
{
	window.draw(sf_text_);
}