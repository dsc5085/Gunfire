#ifndef GUN_ADD_PART_ON_COLLISION_PART_H
#define GUN_ADD_PART_ON_COLLISION_PART_H

#include "Part.h"
#include "ObjectClass.h"
#include "EventBind.h"

namespace gun
{
	class CollidedEventArgs;

	class AddPartOnCollisionPart : public Part
	{
	public:
		AddPartOnCollisionPart(Part* part, ObjectClass::Enum object_class);

		void Initialize();
		void Cleanup();

	private:
		EventBind collided_bind_;
		Part* part_;
		ObjectClass::Enum object_class_;

		void Handle_Collided(CollidedEventArgs& args);
	};
}

#endif