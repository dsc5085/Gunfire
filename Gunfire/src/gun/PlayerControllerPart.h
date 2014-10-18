#ifndef GUN_PLAYER_CONTROLLER_PART_H
#define GUN_PLAYER_CONTROLLER_PART_H

#include <SFML\Graphics.hpp>

#include "Part.h"
#include "InputAction.h"
#include "Timer.h"

namespace gun
{
	class PlayerControllerPart : public Part
	{
	public:
		double reload_time() { return reload_timer_.max_time(); }
		void set_reload_time(double reload_time) { reload_timer_.set_max_time(reload_time); }

		PlayerControllerPart();
		
		void Initialize();
		void Update(double dt);

	private:
		std::map<InputAction::Enum, sf::Keyboard::Key> input_map_;
		float bullet_speed_;
		Timer reload_timer_;
	};
}

#endif