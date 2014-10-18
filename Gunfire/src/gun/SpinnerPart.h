#ifndef GUN_SPINNER_PART_H
#define GUN_SPINNER_PART_H

#include "Part.h"

namespace gun
{
	class SpinnerPart : public Part
	{
	public:
		SpinnerPart(float spin_speed);

		void Update(double dt);

	private:
		float spin_speed_;
	};
}

#endif