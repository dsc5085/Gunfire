#include "AnimationFactory.h"

gun::Animation gun::AnimationFactory::CreateAnimation(int sheet_width, 
	int sprite_width, int sprite_height, int frames)
{
	std::vector<sf::IntRect> source_rects = std::vector<sf::IntRect>();

	for(int i = 0; i < frames; i++)
	{
		int sheet_x = i % sheet_width;
		int sheet_y = i / sheet_width;

		source_rects.push_back(sf::IntRect(sheet_x * sprite_width, sheet_y * sprite_height, 
			sprite_width, sprite_height));
	}

	return Animation(source_rects);
}