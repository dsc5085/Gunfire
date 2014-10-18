#ifndef GUN_FIRE_RATE_MULTIPLIER_PART_H
#define GUN_FIRE_RATE_MULTIPLIER_PART_H

#include "Part.h"
#include "Timer.h"

namespace gun
{
	class FireRateMultiplierPart : public Part
	{
	public:
		FireRateMultiplierPart(double effect_time, float multiplier);

		void Initialize();
		void Cleanup();
		void Update(double dt);

	private:
		Timer effect_timer_;
		float multiplier_;
		double old_reload_time_;
	};
}

#endif