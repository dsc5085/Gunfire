#ifndef GUN_ANIMATION_H
#define GUN_ANIMATION_H

#include <SFML\Graphics.hpp>

namespace gun
{
	class Animation
	{
	public:
		int num_frames() const { return source_rects_.size(); }

		Animation();
		Animation(const std::vector<sf::IntRect>& source_rects);

		sf::IntRect GetSourceRect(int frame) const;

	private:
		std::vector<sf::IntRect> source_rects_;
	};
}

#endif