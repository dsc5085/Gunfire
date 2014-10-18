#ifndef GUN_DIE_AFTER_ANIMATION_PART_H
#define GUN_DIE_AFTER_ANIMATION_PART_H

#include "Part.h"

namespace gun
{
	class DieAfterAnimationPart : public Part
	{
	public:
		void Update(double dt);
	};
}

#endif