#ifndef GUN_SCREEN_MANAGER_H
#define GUN_SCREEN_MANAGER_H

#include <vector>
#include <boost\ptr_container\ptr_vector.hpp>
#include <SFML\Graphics.hpp>

#include "Screen.h"

namespace gun
{
	class ScreenManager
	{
		struct ScreenDrawOrderComparer : std::binary_function<Screen, Screen, bool>
		{
		   bool operator()(const Screen& screen1, const Screen& screen2) const
		   {
			 return screen1.draw_order() > screen2.draw_order();
		   }
		}; 

	public:
		bool is_running() { return is_running_; }

		ScreenManager();

		void Stop();
		void AddScreen(Screen *screen);
		void RemoveScreen(Screen *screen);
		void Update(double dt, const std::vector<sf::Event>& current_events);
		void Draw(sf::RenderWindow& window);

	private:
		bool is_running_;
		boost::ptr_vector<Screen> screens_;
		std::vector<Screen*> screens_to_add_;
		std::vector<Screen*> screens_to_remove_;
	};
}

#endif