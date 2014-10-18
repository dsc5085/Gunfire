#ifndef GUN_SPEED_MULTIPLIER_PART_H
#define GUN_SPEED_MULTIPLIER_PART_H

#include "Part.h"
#include "Timer.h"

namespace gun
{
	class SpeedMultiplierPart : public Part
	{
	public:
		SpeedMultiplierPart(double effect_time, float multiplier);

		void Initialize();
		void Cleanup();
		void Update(double dt);

	private:
		Timer effect_timer_;
		float multiplier_;
		float old_max_speed_;
	};
}

#endif