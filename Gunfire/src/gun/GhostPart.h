#ifndef GUN_GHOST_PART_H
#define GUN_GHOST_PART_H

#include "Part.h"
#include "Timer.h"
#include "CollisionType.h"

namespace gun
{
	class GhostPart : public Part
	{
	public:
		GhostPart(double ghost_time);

		void Initialize();
		void Update(double dt);

	private:
		CollisionType::Enum old_coll_type_;
		Timer ghost_timer_;
	};
}

#endif