#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign.hpp>

#include "OptionsScreen.h"
#include "Math.h"
#include "Paths.h"
#include "KeyNames.h"
#include "TextFadeDecorator.h"
#include "InputContext.h"
#include "MainMenuScreen.h"
#include "Services.h"
#include "SpriteCache.h"
#include "SoundCache.h"
#include "ScreenManager.h"

std::map<std::string, gun::InputAction::Enum> gun::OptionsScreen::INPUT_ACTIONS_MAP
	= boost::assign::map_list_of 
	("UP KEY", InputAction::MOVE_UP)
	("DOWN KEY", InputAction::MOVE_DOWN)
	("LEFT KEY", InputAction::MOVE_LEFT)
	("RIGHT KEY", InputAction::MOVE_RIGHT)
	("FIRE UP KEY", InputAction::FIRE_UP)
	("FIRE DOWN KEY", InputAction::FIRE_DOWN)
	("FIRE LEFT KEY", InputAction::FIRE_LEFT)
	("FIRE RIGHT KEY", InputAction::FIRE_RIGHT);

gun::OptionsScreen::OptionsScreen()
	: input_state_(MENU), menu_index_(0)
{
	splash_ = Services::Instance().sprite_cache()->GetSprite(SpriteKey::SPLASH);
	sound_cache_ = Services::Instance().sound_cache();
	input_map_ = Services::Instance().session().input_map;
}

void gun::OptionsScreen::Initialize()
{
	// Create the option label texts.
	text_factory_.Initialize();
	int ch_size = 24;
	sf::Vector2f label_position = sf::Vector2f(0, 0);
	select_text_ = text_factory_.CreateText(ch_size, label_position, "ARROW KEYS - NAVIGATE");
	label_position.y += ch_size;
	change_text_ = text_factory_.CreateText(ch_size, label_position, "ENTER KEY - SELECT");
	label_position.y += ch_size * 2;
	Text up_text = text_factory_.CreateText(ch_size, label_position, "UP KEY");
	label_position.y += ch_size;
	Text down_text = text_factory_.CreateText(ch_size, label_position, "DOWN KEY");
	label_position.y += ch_size;
	Text left_text = text_factory_.CreateText(ch_size, label_position, "LEFT KEY");
	label_position.y += ch_size;
	Text right_text = text_factory_.CreateText(ch_size, label_position, "RIGHT KEY");
	label_position.y += ch_size;
	Text fire_up_text = text_factory_.CreateText(ch_size, label_position, "FIRE UP KEY");
	label_position.y += ch_size;
	Text fire_down_text = text_factory_.CreateText(ch_size, label_position, "FIRE DOWN KEY");
	label_position.y += ch_size;
	Text fire_left_text = text_factory_.CreateText(ch_size, label_position, "FIRE LEFT KEY");
	label_position.y += ch_size;
	Text fire_right_text = text_factory_.CreateText(ch_size, label_position, "FIRE RIGHT KEY");
	label_position.y += ch_size * 2;
	Text save_text = text_factory_.CreateText(ch_size, label_position, "SAVE CHANGES");
	label_position.y += ch_size * 2;
	Text back_text = text_factory_.CreateText(ch_size, label_position, "BACK");

	// Add the texts to the label texts vector
	label_texts_.push_back(up_text);
	label_texts_.push_back(down_text);
	label_texts_.push_back(left_text);
	label_texts_.push_back(right_text);
	label_texts_.push_back(fire_up_text);
	label_texts_.push_back(fire_down_text);
	label_texts_.push_back(fire_left_text);
	label_texts_.push_back(fire_right_text);
	label_texts_.push_back(save_text);
	label_texts_.push_back(back_text);

	// Find the maximum value of the label texts x bound.
	float value_x = 0;
	for (unsigned int i = 0; i < label_texts_.size(); i++)
	{
		float x = label_texts_[i].bounds().left + label_texts_[i].bounds().width;
		if (x > value_x)
		{
			value_x = x;
		}
	}
	value_x += 96;
	
	// Create the value texts based on the label texts position.
	for (unsigned int i = 0; i < label_texts_.size(); i++)
	{
		sf::Vector2f value_position = label_texts_[i].position();
		value_position.x = value_x;
		value_texts_.push_back(text_factory_.CreateText(24, value_position));
	}

	value_texts_[0].set_string(GetKeyString(InputAction::MOVE_UP));
	value_texts_[1].set_string(GetKeyString(InputAction::MOVE_DOWN));
	value_texts_[2].set_string(GetKeyString(InputAction::MOVE_LEFT));
	value_texts_[3].set_string(GetKeyString(InputAction::MOVE_RIGHT));
	value_texts_[4].set_string(GetKeyString(InputAction::FIRE_UP));
	value_texts_[5].set_string(GetKeyString(InputAction::FIRE_DOWN));
	value_texts_[6].set_string(GetKeyString(InputAction::FIRE_LEFT));
	value_texts_[7].set_string(GetKeyString(InputAction::FIRE_RIGHT));

	label_texts_[menu_index_].sf_text().setColor(sf::Color::Yellow);
	value_texts_[menu_index_].sf_text().setColor(sf::Color::Yellow);
}

void gun::OptionsScreen::HandleInput(const InputContext& input_context)
{
	std::string menu_item = label_texts_[menu_index_].sf_text().getString();

	switch (input_state_)
	{
		case MENU:
		{
			int old_menu_index = menu_index_;

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
			if (input_context.IsKeyReleased(sf::Keyboard::Left))
			{
				sound_cache_->PlaySound(SoundKey::MENU_SELECT);
				ToggleMenuItem(menu_item, -1);
			}
			if (input_context.IsKeyReleased(sf::Keyboard::Right))
			{
				sound_cache_->PlaySound(SoundKey::MENU_SELECT);
				ToggleMenuItem(menu_item, 1);
			}
			if (input_context.IsKeyReleased(sf::Keyboard::Return))
			{
				sound_cache_->PlaySound(SoundKey::MENU_SELECT);
				SelectMenuItem(menu_item);
			}

			menu_index_ = Math::Wrap(menu_index_, 0, value_texts_.size() - 1);

			if (menu_index_ != old_menu_index)
			{
				label_texts_[old_menu_index].sf_text().setColor(sf::Color::White);
				value_texts_[old_menu_index].sf_text().setColor(sf::Color::White);
				label_texts_[menu_index_].sf_text().setColor(sf::Color::Yellow);
				value_texts_[menu_index_].sf_text().setColor(sf::Color::Yellow);
			}

			break;
		}
		case CONTROL_BIND:
		{
			if (input_context.IsKeyReleased(sf::Keyboard::Escape))
			{
				input_state_ = MENU;
			}
			else if (input_context.CheckForEvent(sf::Event::KeyReleased))
			{
				if (INPUT_ACTIONS_MAP.find(menu_item) != INPUT_ACTIONS_MAP.end())
				{
					InputAction::Enum input_action = INPUT_ACTIONS_MAP[menu_item];
					sf::Keyboard::Key released_key = input_context.GetEvent(
						sf::Event::KeyReleased).key.code;

					if (KeyNames::MAP.find(released_key) != KeyNames::MAP.end())
					{
						input_map_[input_action] = released_key;
						std::string key_name = boost::to_upper_copy(KeyNames::MAP[released_key]);
						value_texts_[menu_index_].set_string(key_name);
					}
				}
				else
				{
					std::string message = "Could not bind to " + menu_item
						+ " because it is not a valid input action.";
					throw std::invalid_argument(message);
				}
				input_state_ = MENU;
			}

			if (input_state_ == MENU)
			{
				label_texts_[menu_index_].RemoveDecorators<TextFadeDecorator>();
				value_texts_[menu_index_].RemoveDecorators<TextFadeDecorator>();
				label_texts_[menu_index_].sf_text().setColor(sf::Color::Yellow);
				value_texts_[menu_index_].sf_text().setColor(sf::Color::Yellow);
			}

			break;
		}
	}
}

void gun::OptionsScreen::Update(double dt)
{
	for (unsigned int i = 0; i < label_texts_.size(); i++)
	{
		label_texts_[i].Update(dt);
	}

	for (unsigned int i = 0; i < value_texts_.size(); i++)
	{
		value_texts_[i].Update(dt);
	}
}

void gun::OptionsScreen::Draw(sf::RenderWindow& window)
{
	window.draw(splash_);
	select_text_.Draw(window);
	change_text_.Draw(window);

	for (unsigned int i = 0; i < label_texts_.size(); i++)
	{
		label_texts_[i].Draw(window);
	}

	for (unsigned int i = 0; i < value_texts_.size(); i++)
	{
		value_texts_[i].Draw(window);
	}
}

void gun::OptionsScreen::SelectMenuItem(const std::string& menu_item)
{
	if (boost::algorithm::ends_with(menu_item, "KEY"))
	{
		input_state_ = CONTROL_BIND;
		label_texts_[menu_index_].AddDecorator(new TextFadeDecorator(0.2, true));
		value_texts_[menu_index_].AddDecorator(new TextFadeDecorator(0.2, true));
	}
	else if (menu_item == "SAVE CHANGES")
	{
		Services::Instance().session().input_map = input_map_;
		SaveSettings();
	}
	else if (menu_item == "BACK")
	{
		screen_mgr_->RemoveScreen(this);
		screen_mgr_->AddScreen(new MainMenuScreen());
	}
}

void gun::OptionsScreen::ToggleMenuItem(const std::string& menu_item, int offset)
{
}

void gun::OptionsScreen::SaveSettings()
{
	std::ofstream file = std::ofstream();
	file.open(Paths::SETTINGS_FILE);
	int is_fullscreen = Services::Instance().session().is_fullscreen ? 1 : 0;
	file << is_fullscreen << std::endl;
	file << Services::Instance().session().screen_width << std::endl;
	file << Services::Instance().session().screen_height << std::endl;
	file << input_map_[InputAction::MOVE_UP] << std::endl;
	file << input_map_[InputAction::MOVE_DOWN] << std::endl;
	file << input_map_[InputAction::MOVE_LEFT] << std::endl;
	file << input_map_[InputAction::MOVE_RIGHT] << std::endl;
	file << input_map_[InputAction::FIRE_UP] << std::endl;
	file << input_map_[InputAction::FIRE_DOWN] << std::endl;
	file << input_map_[InputAction::FIRE_LEFT] << std::endl;
	file << input_map_[InputAction::FIRE_RIGHT] << std::endl;
	file.close();
}

std::string gun::OptionsScreen::GetKeyString(InputAction::Enum action)
{
	sf::Keyboard::Key key = input_map_[action];
	return boost::to_upper_copy(KeyNames::MAP[key]);
}