#include "DieOnCollisionPart.h"
#include "CollidedEventArgs.h"
#include "GameObject.h"
#include "Services.h"
#include "EventManager.h"

gun::DieOnCollisionPart::DieOnCollisionPart(CollisionType::Enum coll_type)
	: coll_type_(coll_type)
{
}

void gun::DieOnCollisionPart::Initialize()
{
	collided_bind_ = Services::Instance().event_manager()->Subscribe<CollidedEventArgs>(
		boost::bind(&gun::DieOnCollisionPart::Handle_Collided, this, _1));
}

void gun::DieOnCollisionPart::Cleanup()
{
	collided_bind_.Unsubscribe();
}

void gun::DieOnCollisionPart::Handle_Collided(CollidedEventArgs& args)
{
	if (is_active_)
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
			if (other->coll_type() == coll_type_)
			{
				game_object_->Die();
			}
		}
	}
}