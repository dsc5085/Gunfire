#include <boost\lexical_cast.hpp>

#include "GameOverScreen.h"
#include "InputContext.h"
#include "MainMenuScreen.h"
#include "Services.h"
#include "Session.h"
#include "ScreenManager.h"
#include "ViewManager.h"

void gun::GameOverScreen::Initialize()
{
	text_factory_.Initialize();
	std::string score = boost::lexical_cast<std::string>(
		Services::Instance().session().score);
	sf::Vector2f screen_center = Services::Instance()
		.view_manager()->world_view().getCenter();
	info_text_ = text_factory_.CreateText(24, "GAME OVER!\nFINAL SCORE "
		+ score + ".\n\nPRESS ENTER TO CONTINUE");
	info_text_.set_center(screen_center);
}

void gun::GameOverScreen::HandleInput(const InputContext& input_context)
{
	if (input_context.IsKeyReleased(sf::Keyboard::Return))
	{
		screen_mgr_->RemoveScreen(this);
		screen_mgr_->AddScreen(new MainMenuScreen());
	}
}

void gun::GameOverScreen::Draw(sf::RenderWindow& window)
{
	info_text_.Draw(window);
}