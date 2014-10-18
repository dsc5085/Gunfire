#include <boost\lexical_cast.hpp>

#include "HUDScreen.h"
#include "PolygonMath.h"
#include "ScreenDrawOrder.h"
#include "DiedEventArgs.h"
#include "NewWaveEventArgs.h"
#include "WaveCompleteEventArgs.h"
#include "AddPartEventArgs.h"
#include "GameOverEventArgs.h"
#include "GameObject.h"
#include "TextFadeDecorator.h"
#include "Services.h"
#include "EventManager.h"
#include "ScreenManager.h"
#include "ViewManager.h"

const int gun::HUDScreen::SCORE_SCROLL_SPEED = 300;

gun::HUDScreen::HUDScreen()
	: Screen(ScreenDrawOrder::HUD), score_(0)
{
	screen_center_ = Services::Instance().view_manager()->world_view().getCenter();
}

void gun::HUDScreen::Initialize()
{
	text_factory_.Initialize();
	Handle_NewWave(NewWaveEventArgs(0));
	
	died_bind_ = Services::Instance().event_manager()->Subscribe<DiedEventArgs>(
		boost::bind(&gun::HUDScreen::Handle_Died, this, _1));
	new_wave_bind_ = Services::Instance().event_manager()->Subscribe<NewWaveEventArgs>(
		boost::bind(&gun::HUDScreen::Handle_NewWave, this, _1));
	wave_complete_bind_ = Services::Instance().event_manager()->Subscribe<WaveCompleteEventArgs>(
		boost::bind(&gun::HUDScreen::Handle_WaveComplete, this, _1));
	add_part_bind_ = Services::Instance().event_manager()->Subscribe<AddPartEventArgs>(
		boost::bind(&gun::HUDScreen::Handle_AddPart, this, _1));
	game_over_bind_ = Services::Instance().event_manager()->Subscribe<GameOverEventArgs>(
		boost::bind(&gun::HUDScreen::Handle_GameOver, this, _1));

	paused_text_ = text_factory_.CreateText(24, "PAUSED");
	paused_text_.set_center(screen_center_);
	score_text_ = text_factory_.CreateText(16, sf::Vector2f(0, 0));
	lives_text_ = text_factory_.CreateText(16, sf::Vector2f(0, 16));
}

void gun::HUDScreen::Cleanup()
{
	died_bind_.Unsubscribe();
	new_wave_bind_.Unsubscribe();
	wave_complete_bind_.Unsubscribe();
	add_part_bind_.Unsubscribe();
	game_over_bind_.Unsubscribe();
}

void gun::HUDScreen::Update(double dt)
{
	score_text_.set_string("SCORE " + boost::lexical_cast<std::string>(score_));
	lives_text_.set_string("LIVES " + boost::lexical_cast<std::string>(
		Services::Instance().session().lives));

	for (unsigned int i = 0; i < popups_.size(); i++)
	{
		popups_[i].Update(dt);

		if (popups_[i].is_expired())
		{
			popups_.erase(popups_.begin() + i);
			i--;
		}
	}

	int new_score = score_ + (int) (SCORE_SCROLL_SPEED * dt);
	score_ = std::min(new_score, Services::Instance().session().score);
}

void gun::HUDScreen::Draw(sf::RenderWindow& window)
{
	score_text_.Draw(window);
	lives_text_.Draw(window);

	if (Services::Instance().session().is_paused)
	{
		paused_text_.Draw(window);
	}

	for (unsigned int i = 0; i < popups_.size(); i++)
	{
		popups_[i].Draw(window);
	}
}

void gun::HUDScreen::Handle_Died(DiedEventArgs& args)
{
	if (args.game_object->points() > 0)
	{
		sf::Vector2f position = args.game_object->center()
			* Services::Instance().view_manager()->unit_pixels();
		Text popup = text_factory_.CreateText(12, 
			boost::lexical_cast<std::string>(args.game_object->points()));
		popup.AddDecorator(new TextFadeDecorator(3));
		popup.set_center(position);
		popups_.push_back(popup);
	}
}

void gun::HUDScreen::Handle_NewWave(NewWaveEventArgs& args)
{
	int wave_num = Services::Instance().session().level.waves.size();
	std::string display_string; 

	if (args.wave_index < wave_num - 1)
	{
		display_string = std::string("WAVE ") + boost::lexical_cast<std::string>(
			args.wave_index + 1) + " STARTED!";
	}
	else
	{
		display_string = "FINAL WAVE STARTED!";
	}

	Text popup = text_factory_.CreateText(24, display_string);
	popup.AddDecorator(new TextFadeDecorator(3));
	popup.set_center(screen_center_);
	popups_.push_back(popup);
}

void gun::HUDScreen::Handle_WaveComplete(WaveCompleteEventArgs& args)
{
	std::string string = std::string("WAVE ")
		+ boost::lexical_cast<std::string>(args.wave_index + 1) + " COMPLETED!\nTIME BONUS: "
		+ boost::lexical_cast<std::string>(args.time_bonus);
	Text popup = text_factory_.CreateText(24, string);
	popup.AddDecorator(new TextFadeDecorator(3));
	popup.set_center(screen_center_);
	popups_.push_back(popup);
}

void gun::HUDScreen::Handle_AddPart(AddPartEventArgs& args)
{
	ObjectClass::Enum object_class = args.adder->object_class();
	std::string string;
	
	if (object_class == ObjectClass::SPEED_POWER_UP)
	{
		string = "SPEED UP!";
	}
	else if (object_class == ObjectClass::FIRE_RATE_POWER_UP)
	{
		string = "RAPID FIRE!";
	}
	else if (object_class == ObjectClass::GHOSTING_POWER_UP)
	{
		string = "GHOST MODE!";
	}
	else
	{
		std::string message = object_class + " isn't a valid powerup object class.";
		throw std::invalid_argument(message);
	}
	
	sf::Vector2f position = args.receiver->center()
		* Services::Instance().view_manager()->unit_pixels();
	Text popup = text_factory_.CreateText(12, string);
	popup.AddDecorator(new TextFadeDecorator(3));
	popup.set_center(position);
	popups_.push_back(popup);
}

void gun::HUDScreen::Handle_GameOver(GameOverEventArgs& args)
{
	screen_mgr_->RemoveScreen(this);
}