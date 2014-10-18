#ifndef GUN_HUD_SCREEN_H
#define GUN_HUD_SCREEN_H

#include <vector>
#include <SFML\Graphics.hpp>

#include "Screen.h"
#include "EventBind.h"
#include "Text.h"
#include "TextFactory.h"

namespace gun
{
	class DiedEventArgs;
	class NewWaveEventArgs;
	class WaveCompleteEventArgs;
	class AddPartEventArgs;
	class GameOverEventArgs;

	class HUDScreen : public Screen
	{
	public:
		HUDScreen();

		void Initialize();
		void Cleanup();
		void Update(double dt);
		void Draw(sf::RenderWindow& window);

	private:
		static const int SCORE_SCROLL_SPEED;

		TextFactory text_factory_;
		sf::Vector2f screen_center_;
		sf::Font font_;
		int score_;
		Text paused_text_;
		Text lives_text_;
		Text score_text_;
		std::vector<Text> popups_;
		EventBind died_bind_;
		EventBind new_wave_bind_;
		EventBind wave_complete_bind_;
		EventBind add_part_bind_;
		EventBind game_over_bind_;
		
		void Handle_Died(DiedEventArgs& args);
		void Handle_NewWave(NewWaveEventArgs& args);
		void Handle_WaveComplete(WaveCompleteEventArgs& args);
		void Handle_AddPart(AddPartEventArgs& args);
		void Handle_GameOver(GameOverEventArgs& args);

		void CreatePopup(const sf::Vector2f& center);
	};
}

#endif