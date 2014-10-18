#ifndef GUN_DIE_ON_COLLISION_PART_H
#define GUN_DIE_ON_COLLISION_PART_H

#include "Part.h"
#include "EventBind.h"
#include "CollisionType.h"

namespace gun
{
	class CollidedEventArgs;

	class DieOnCollisionPart : public Part
	{
	public:
		DieOnCollisionPart(CollisionType::Enum coll_type);

		void Initialize();
		void Cleanup();
		
	private:
		EventBind collided_bind_;
		CollisionType::Enum coll_type_;

		void Handle_Collided(CollidedEventArgs& args);
		void Activate();
		void Deactivate();
	};
}

#endif