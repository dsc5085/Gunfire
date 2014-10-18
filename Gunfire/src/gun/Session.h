#ifndef GUN_SESSION_H
#define GUN_SESSION_H

#include <vector>
#include <SFML\Graphics.hpp>

#include "InputAction.h"
#include "ScoreEntry.h"
#include "Level.h"

namespace gun
{
	struct Session
	{
	public:
		// Constants
		static const int MAX_HIGH_SCORES;

		// Game Setting Variables
		bool is_fullscreen;
		int screen_width;
		int screen_height;
		std::map<InputAction::Enum, sf::Keyboard::Key> input_map;

		// Game State Variables
		std::vector<ScoreEntry> high_scores;
		bool is_paused;
		int score;
		int lives;
		Level level;
	};
}

#endif