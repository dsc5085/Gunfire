#include "MainMenuScreen.h"
#include "Math.h"
#include "Log.h"
#include "InputContext.h"
#include "LevelScreen.h"
#include "HUDScreen.h"
#include "HighScoresScreen.h"
#include "OptionsScreen.h"
#include "Services.h"
#include "ScreenManager.h"
#include "SpriteCache.h"
#include "SoundCache.h"
#include "ViewManager.h"
#include "LevelFactory.h"

gun::MainMenuScreen::MainMenuScreen()
	: menu_index_(0)
{
	splash_ = Services::Instance().sprite_cache()->GetSprite(SpriteKey::SPLASH);
	sound_cache_ = Services::Instance().sound_cache();
	view_manager_ = Services::Instance().view_manager();
}

void gun::MainMenuScreen::Initialize()
{
	sf::Vector2f position = sf::Vector2f(0, 0);
	text_factory_.Initialize();
	Text new_game_text = text_factory_.CreateText(24, position, "NEW GAME");
	position.y += new_game_text.char_size() * 2;
	Text high_scores_text = text_factory_.CreateText(24, position, "HIGH SCORES");
	position.y += new_game_text.char_size() * 2;
	Text options_text = text_factory_.CreateText(24, position, "OPTIONS");
	position.y += new_game_text.char_size() * 2;
	Text quit_text = text_factory_.CreateText(24, position, "QUIT");

	menu_texts_.push_back(new_game_text);
	menu_texts_.push_back(high_scores_text);
	menu_texts_.push_back(options_text);
	menu_texts_.push_back(quit_text);
}

void gun::MainMenuScreen::HandleInput(const InputContext& input_context)
{
	if (input_context.IsKeyReleased(sf::Keyboard::Up))
	{
		sound_cache_->PlaySound(SoundKey::MENU_SELECT);
		menu_index_--;
	}
	if (input_context.IsKeyReleased(sf::Keyboard::Down))
	{
		sound_cache_->PlaySound(SoundKey::MENU_SELECT);
		menu_index_++;
	}
	menu_index_ = Math::Wrap(menu_index_, 0, menu_texts_.size() - 1);
	if (input_context.IsKeyReleased(sf::Keyboard::Return))
	{
		sound_cache_->PlaySound(SoundKey::MENU_SELECT);
		std::string menu_item = menu_texts_[menu_index_].sf_text().getString();
		SelectMenuItem(menu_item);
	}
}

void gun::MainMenuScreen::Update(double dt)
{
	for (unsigned int i = 0; i < menu_texts_.size(); i++)
	{
		if (i == menu_index_)
		{
			menu_texts_[i].sf_text().setColor(sf::Color::Yellow);
		}
		else
		{
			menu_texts_[i].sf_text().setColor(sf::Color::White);
		}
	}
}

void gun::MainMenuScreen::Draw(sf::RenderWindow& window)
{
	window.draw(splash_);

	for (unsigned int i = 0; i < menu_texts_.size(); i++)
	{
		menu_texts_[i].Draw(window);
	}
}

void gun::MainMenuScreen::SelectMenuItem(const std::string& menu_item)
{
	screen_mgr_->RemoveScreen(this);

	if (menu_item == "NEW GAME")
	{
		BOOST_LOG_TRIVIAL(info) << "NEW GAME";
		Level level = LevelFactory::CreateLevel();
		Services::Instance().session().level = level;
		sf::Vector2f screen_size = view_manager_->world_view().getSize();
		sf::FloatRect viewPort(level.area.left, level.area.top, 
			(float)screen_size.x / (level.area.width * view_manager_->unit_pixels()), 
			(float)screen_size.y / (level.area.height * view_manager_->unit_pixels()));
		view_manager_->world_view().setViewport(viewPort);
		screen_mgr_->AddScreen(new LevelScreen(level));
		screen_mgr_->AddScreen(new HUDScreen());
	}
	else if (menu_item == "HIGH SCORES")
	{
		screen_mgr_->AddScreen(new HighScoresScreen());
	}
	else if (menu_item == "OPTIONS")
	{
		screen_mgr_->AddScreen(new OptionsScreen());
	}
	else if (menu_item == "QUIT")
	{
		screen_mgr_->Stop();
	}
}