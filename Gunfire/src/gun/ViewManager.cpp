#include "ViewManager.h"
#include "Services.h"

gun::ViewManager::ViewManager()
	: unit_pixels_(32)
{
}

void gun::ViewManager::SetWindowDisplay(
	bool is_fullscreen, int screen_width, int screen_height)
{
	int style = (is_fullscreen) ? sf::Style::Fullscreen : sf::Style::Default;
	window_.create(sf::VideoMode(screen_width, screen_height), "Gunfire", style);
}