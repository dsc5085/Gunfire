#ifndef GUN_GRAVITY_PART_H
#define GUN_GRAVITY_PART_H

#include "Part.h"

namespace gun
{
	class GravityPart : public Part
	{
	public:
		void Update(double dt);

	private:
		static const float GRAVITY;
	};
}

#endif