#ifndef GUN_BOUNCING_PART_H
#define GUN_BOUNCING_PART_H

#include "Part.h"

namespace gun
{
	class BouncingPart : public Part
	{
	public:
		void Update(double dt);
	};
}

#endif