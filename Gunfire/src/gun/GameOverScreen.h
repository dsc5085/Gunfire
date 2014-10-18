#ifndef GUN_GAME_OVER_SCREEN_H
#define GUN_GAME_OVER_SCREEN_H

#include <SFML\Graphics.hpp>

#include "Screen.h"
#include "Text.h"
#include "TextFactory.h"

namespace gun
{
	class GameOverScreen : public Screen
	{
	public:
		void Initialize();
		void HandleInput(const InputContext& input_context);
		void Draw(sf::RenderWindow& window);

	private:
		TextFactory text_factory_;
		Text info_text_;
	};
}

#endif