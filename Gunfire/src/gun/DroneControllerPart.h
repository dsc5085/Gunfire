#ifndef GUN_DRONE_CONTROLLER_PART_H
#define GUN_DRONE_CONTROLLER_PART_H

#include "Part.h"
#include "Timer.h"

namespace gun
{
	class DroneControllerPart : public Part
	{
	public:
		DroneControllerPart();

		void Update(double dt);

	private:
		float bullet_speed_;
		double max_reload_time_;
		Timer move_timer_;
		Timer reload_timer_;

		void Reload();
	};
}

#endif