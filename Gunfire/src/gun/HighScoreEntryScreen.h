#ifndef GUN_HIGH_SCORE_ENTRY_SCREEN_H
#define GUN_HIGH_SCORE_ENTRY_SCREEN_H

#include <SFML\Graphics.hpp>

#include "Screen.h"
#include "TextFactory.h"

namespace gun
{
	class InputContext;

	class HighScoreEntryScreen : public Screen
	{
	public:
		void Initialize();
		void HandleInput(const InputContext& input_context);
		void Draw(sf::RenderWindow& window);

	private:
		TextFactory text_factory_;
		Text info_text_;
		Text name_text_;
		
		void EnterHighScores();
		void SaveHighScores();
	};
}

#endif