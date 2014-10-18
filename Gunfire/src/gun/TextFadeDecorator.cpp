#include <algorithm>
#include <SFML\Graphics.hpp>

#include "TextFadeDecorator.h"
#include "Text.h"

gun::TextFadeDecorator::TextFadeDecorator(double max_age)
	: is_looping_(false), fade_state_(FADE), age_(0), max_age_(max_age)
{
}

gun::TextFadeDecorator::TextFadeDecorator(double max_age, bool is_looping)
	: is_looping_(is_looping), fade_state_(FADE), age_(0), max_age_(max_age)
{
}

void gun::TextFadeDecorator::Update(Text& text, double dt)
{
	age_ += dt;
	double age_ratio;

	switch (fade_state_)
	{
		case FADE:
		{
			age_ratio = 1 - std::min(age_ / max_age_, 1.0);
			break;
		}
		case DEFADE:
		{
			age_ratio = std::max(age_ / max_age_, 0.0);
			break;
		}
	}

	sf::Color color = text.sf_text().getColor();
	color.a = 255;
	color.a = (sf::Uint8) (color.a * age_ratio);
	text.sf_text().setColor(color);

	if (is_looping_ && age_ >= max_age_)
	{
		age_ = 0;

		switch (fade_state_)
		{
			case FADE:
			{
				fade_state_ = DEFADE;
				break;
			}
			case DEFADE:
			{
				fade_state_ = FADE;
				break;
			}
		}
	}
}