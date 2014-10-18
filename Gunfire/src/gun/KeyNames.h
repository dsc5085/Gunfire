#ifndef GUN_KEY_NAMES_H
#define GUN_KEY_NAMES_H

#include <string>
#include <map>
#include <SFML\Graphics.hpp>

namespace gun
{
	class KeyNames
	{
	public:
		static std::map<sf::Keyboard::Key, std::string> MAP;
	};
}

#endif