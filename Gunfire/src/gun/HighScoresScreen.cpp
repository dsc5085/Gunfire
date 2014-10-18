#include <boost\lexical_cast.hpp>

#include "HighScoresScreen.h"
#include "ScoreEntry.h"
#include "InputContext.h"
#include "MainMenuScreen.h"
#include "Services.h"
#include "Session.h"
#include "SpriteCache.h"
#include "ScreenManager.h"
#include "ViewManager.h"

gun::HighScoresScreen::HighScoresScreen()
{
	splash_ = Services::Instance().sprite_cache()->GetSprite(SpriteKey::SPLASH);
}

gun::HighScoresScreen::HighScoresScreen(const ScoreEntry& new_score)
{
	splash_ = Services::Instance().sprite_cache()->GetSprite(SpriteKey::SPLASH);
	new_scores_.push_back(new_score);
}

void gun::HighScoresScreen::Initialize()
{
	text_factory_.Initialize();
	int margin = 10;
	sf::View view = Services::Instance().view_manager()->world_view();
	std::vector<ScoreEntry> high_scores = Services::Instance().session().high_scores;
	Text header_text = text_factory_.CreateText(24, "HIGH SCORES");
	header_text.set_center(sf::Vector2f(view.getCenter().x, (float)header_text.char_size() / 2));
	texts_.push_back(header_text);
	int text_y = (int)(header_text.position().y + header_text.char_size() * 2);

	for (unsigned int i = 0; i < high_scores.size(); i++)
	{
		Text name_text = text_factory_.CreateText(16, 
			boost::lexical_cast<std::string>(i + 1) + ". " + high_scores[i].name);
		Text score_text = text_factory_.CreateText(16, 
			boost::lexical_cast<std::string>(high_scores[i].score));
		name_text.set_position(sf::Vector2f(
			(float)(margin * name_text.char_size()), (float)text_y));
		score_text.set_position(sf::Vector2f(view.getSize().x - score_text.bounds().width
			- margin * name_text.char_size(), (float)text_y));
		text_y += name_text.char_size() * 2;

		for (unsigned int j = 0; j < new_scores_.size(); j++)
		{
			if (high_scores[i].name == new_scores_[j].name
				&& high_scores[i].score == new_scores_[j].score)
			{
				name_text.sf_text().setColor(sf::Color::Yellow);
				score_text.sf_text().setColor(sf::Color::Yellow);
				new_scores_.erase(new_scores_.begin() + j);
				break;
			}
		}

		texts_.push_back(name_text);
		texts_.push_back(score_text);
	}

	Text continue_text = text_factory_.CreateText(24, "PRESS ENTER TO CONTINUE");
	continue_text.set_position(sf::Vector2f(view.getCenter().x
		- continue_text.bounds().width / 2, (float)text_y));
	texts_.push_back(continue_text);
}

void gun::HighScoresScreen::HandleInput(const InputContext& input_context)
{
	if (input_context.IsKeyReleased(sf::Keyboard::Return))
	{
		screen_mgr_->RemoveScreen(this);
		screen_mgr_->AddScreen(new MainMenuScreen());
	}
}

void gun::HighScoresScreen::Draw(sf::RenderWindow& window)
{
	window.draw(splash_);

	for (unsigned int i = 0; i < texts_.size(); i++)
	{
		texts_[i].Draw(window);
	}
}