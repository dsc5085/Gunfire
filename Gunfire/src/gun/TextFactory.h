#ifndef GUN_TEXT_FACTORY_H
#define GUN_TEXT_FACTORY_H

#include <SFML\Graphics.hpp>

#include "Text.h"

namespace gun
{
	class TextFactory
	{
	public:
		void Initialize();
		Text CreateText(unsigned int size);
		Text CreateText(unsigned int size, const std::string& string);
		Text CreateText(unsigned int size, sf::Vector2f position);
		Text CreateText(unsigned int size, sf::Vector2f position, const std::string& string);
		Text AddFade(double max_age);

	private:
		sf::Font font_;
	};
}

#endif