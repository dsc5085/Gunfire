#ifndef GUN_OPTIONS_SCREEN_H
#define GUN_OPTIONS_SCREEN_H

#include <SFML\Graphics.hpp>

#include "Screen.h"
#include "InputAction.h"
#include "Text.h"
#include "Sprite.h"
#include "TextFactory.h"

namespace gun
{
	class SoundCache;

	class OptionsScreen : public Screen
	{
	public:
		OptionsScreen();

		void Initialize();
		void HandleInput(const InputContext& input_context);
		void Update(double dt);
		void Draw(sf::RenderWindow& window);

	private:
		enum InputState
		{
			MENU, 
			CONTROL_BIND
		};

		static std::map<std::string, InputAction::Enum> INPUT_ACTIONS_MAP;
		std::map<InputAction::Enum, sf::Keyboard::Key> input_map_;

		Sprite splash_;
		SoundCache* sound_cache_;
		TextFactory text_factory_;
		InputState input_state_;
		Text select_text_;
		Text change_text_;
		std::vector<Text> label_texts_;
		std::vector<Text> value_texts_;
		int menu_index_;

		void SelectMenuItem(const std::string& menu_item);
		void ToggleMenuItem(const std::string& menu_item, int offset);
		void SaveSettings();
		std::string GetKeyString(InputAction::Enum action);
	};
}

#endif