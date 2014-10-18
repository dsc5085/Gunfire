#ifndef GUN_MAIN_MENU_SCREEN_H
#define GUN_MAIN_MENU_SCREEN_H

#include <SFML\Graphics.hpp>

#include "Screen.h"
#include "Sprite.h"
#include "Text.h"
#include "TextFactory.h"

namespace gun
{
	class SoundCache;
	class ViewManager;

	class MainMenuScreen : public Screen
	{
	public:
		MainMenuScreen();

		void Initialize();
		void HandleInput(const InputContext& input_context);
		void Update(double dt);
		void Draw(sf::RenderWindow& window);

	private:
		Sprite splash_;
		SoundCache* sound_cache_;
		ViewManager* view_manager_;
		TextFactory text_factory_;
		std::vector<Text> menu_texts_;
		int menu_index_;

		void SelectMenuItem(const std::string& menu_item);
	};
}

#endif