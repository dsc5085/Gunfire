#include "Animation.h"

gun::Animation::Animation()
{
}

gun::Animation::Animation(const std::vector<sf::IntRect>& source_rects)
	: source_rects_(source_rects)
{
}

sf::IntRect gun::Animation::GetSourceRect(int frame) const
{
	return source_rects_[frame];
}