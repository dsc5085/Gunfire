#include "DamageOnCollisionPart.h"
#include "CollidedEventArgs.h"
#include "GameObject.h"
#include "Services.h"
#include "EventManager.h"

gun::DamageOnCollisionPart::DamageOnCollisionPart(
	CollisionType::Enum coll_type, float damage)
	: coll_type_(coll_type), damage_(damage)
{
}

void gun::DamageOnCollisionPart::Initialize()
{
	collided_bind_ = Services::Instance().event_manager()->Subscribe<CollidedEventArgs>(
		boost::bind(&gun::DamageOnCollisionPart::Handle_Collided, this, _1));
}

void gun::DamageOnCollisionPart::Cleanup()
{
	collided_bind_.Unsubscribe();
}

void gun::DamageOnCollisionPart::Handle_Collided(CollidedEventArgs& args)
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
		if(other->coll_type() == coll_type_)
			other->health() -= damage_;
	}
}