#ifndef GUN_EXPLODER_CONTROLLER_PART_H
#define GUN_EXPLODER_CONTROLLER_PART_H

#include "Part.h"
#include "Timer.h"

namespace gun
{
	class ExploderControllerPart : public Part
	{
	public:
		ExploderControllerPart(double min_explode_time, double max_explode_time);

		void Update(double dt);

	private:
		Timer explode_timer_;
	};
}

#endif