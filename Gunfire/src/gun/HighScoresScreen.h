#ifndef GUN_HIGH_SCORES_SCREEN_H
#define GUN_HIGH_SCORES_SCREEN_H

#include <SFML\Graphics.hpp>

#include "Screen.h"
#include "ScoreEntry.h"
#include "Text.h"
#include "Sprite.h"
#include "TextFactory.h"

namespace gun
{
	class HighScoresScreen : public Screen
	{
	public:
		HighScoresScreen();
		HighScoresScreen(const ScoreEntry& new_score);

		void Initialize();
		void HandleInput(const InputContext& input_context);
		void Draw(sf::RenderWindow& window);

	private:
		Sprite splash_;
		std::vector<ScoreEntry> new_scores_;
		TextFactory text_factory_;
		std::vector<Text> texts_;
	};
}

#endif