#ifndef GUN_LEVEL_SCREEN_H
#define GUN_LEVEL_SCREEN_H

#include <SFML\Graphics.hpp>

#include "Screen.h"
#include "EventBind.h"
#include "Level.h"
#include "ObjectManager.h"
#include "LevelController.h"

namespace gun
{
	class GameOverEventArgs;
	class EventManager;

	class LevelScreen : public Screen
	{
	public:
		LevelScreen(Level level);

		void Initialize();
		void Cleanup();
		void HandleInput(const InputContext& input_context);
		void Update(double dt);
		void Draw(sf::RenderWindow& window);

	private:
		Level level_;
		EventManager* event_manager_;
		EventBind game_over_bind_;
		ObjectManager<GameObject>* object_manager_;
		LevelController level_controller_;

		void Handle_GameOver(GameOverEventArgs& args);
	};
}

#endif