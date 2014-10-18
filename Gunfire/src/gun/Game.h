#ifndef GUN_GAME_H
#define GUN_GAME_H

#include <SFML\Graphics.hpp>

#include "ScreenManager.h"

namespace gun
{
	class ViewManager;

	class Game
	{
	public:
		Game();
		void Run();

	private:
		sf::Clock clock_;
		ScreenManager screen_manager_;
		ViewManager* view_manager_;

		void Setup();
		void LoadSettings();
		void LoadHighScores();
	};
}

#endif