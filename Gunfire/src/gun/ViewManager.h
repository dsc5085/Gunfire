#ifndef GUN_VIEW_MANAGER_H
#define GUN_VIEW_MANAGER_H

#include <SFML\Graphics.hpp>

namespace gun
{
	class ViewManager
	{
	public:
		float unit_pixels() { return unit_pixels_; }
		sf::RenderWindow& window() { return window_; }
		sf::View& world_view() { return world_view_; }
		
		ViewManager();

		void SetWindowDisplay(bool is_fullscreen, int screen_width, int screen_height);

	private:
		float unit_pixels_;
		sf::RenderWindow window_;
		sf::View world_view_;
	};
}

#endif