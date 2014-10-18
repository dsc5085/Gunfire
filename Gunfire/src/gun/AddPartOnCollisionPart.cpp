#include "AddPartOnCollisionPart.h"
#include "CollidedEventArgs.h"
#include "AddPartEventArgs.h"
#include "GameObject.h"
#include "Services.h"
#include "EventManager.h"

gun::AddPartOnCollisionPart::AddPartOnCollisionPart(
	Part* part, ObjectClass::Enum object_class)
	: part_(part), object_class_(object_class)
{
}

void gun::AddPartOnCollisionPart::Initialize()
{
	collided_bind_ = Services::Instance().event_manager()->Subscribe<CollidedEventArgs>(
		boost::bind(&gun::AddPartOnCollisionPart::Handle_Collided, this, _1));
}

void gun::AddPartOnCollisionPart::Cleanup()
{
	collided_bind_.Unsubscribe();
}

void gun::AddPartOnCollisionPart::Handle_Collided(CollidedEventArgs& args)
{
	GameObject* other = 0;

	if (game_object_ == args.game_object1)
	{
		other = args.game_object2;
	}
	else if (game_object_ == args.game_object2)
	{
		other = args.game_object1;
	}

	if (other != 0)
	{
		if (other->object_class() == object_class_)
		{
			Services::Instance().event_manager()->Publish(
				AddPartEventArgs(game_object_, other));
			other->Replace(part_);
			game_object_->Die();
		}
	}
}