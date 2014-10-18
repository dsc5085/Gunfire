#ifndef GUN_TIMED_DEATH_PART_H
#define GUN_TIMED_DEATH_PART_H

#include "Part.h"

namespace gun
{
	class TimedDeathPart : public Part
	{
	public:
		TimedDeathPart(double max_age);

		void Update(double dt);

	private:
		double max_age_;
	};
}

#endif