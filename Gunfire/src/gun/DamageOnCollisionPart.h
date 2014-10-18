#ifndef GUN_DAMAGE_ON_COLLISION_PART_H
#define GUN_DAMAGE_ON_COLLISION_PART_H

#include "Part.h"
#include "EventBind.h"
#include "CollisionType.h"

namespace gun
{
	class CollidedEventArgs;

	class DamageOnCollisionPart : public Part
	{
	public:
		DamageOnCollisionPart(CollisionType::Enum coll_type, float damage);
		void Initialize();
		void Cleanup();
		
	private:
		EventBind collided_bind_;
		CollisionType::Enum coll_type_;
		float damage_;

		void Handle_Collided(CollidedEventArgs& args);
	};
}

#endif