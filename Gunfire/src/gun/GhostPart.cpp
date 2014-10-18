#include "GhostPart.h"
#include "GameObject.h"
#include "DieOnCollisionPart.h"
#include "Services.h"
#include "SoundCache.h"

gun::GhostPart::GhostPart(double ghost_time)
	: ghost_timer_(Timer(ghost_time, 0))
{
}

void gun::GhostPart::Initialize()
{
	old_coll_type_ = game_object_->coll_type();
	game_object_->set_coll_type(CollisionType::NONE);

	if (game_object_->HasPart<DieOnCollisionPart>())
	{
		DieOnCollisionPart* dieOnCollisionPart
			= game_object_->GetPart<DieOnCollisionPart>();
		dieOnCollisionPart->set_is_active(false);
	}
	
	game_object_->sprite().set_color(sf::Color(255, 255, 255, 64));
	Services::Instance().sound_cache()->PlaySound(SoundKey::MALE_YES);
}

void gun::GhostPart::Update(double dt)
{
	if(ghost_timer_.is_time())
	{
		game_object_->set_coll_type(old_coll_type_);
		game_object_->sprite().set_color(sf::Color(255, 255, 255, 255));

		if (game_object_->HasPart<DieOnCollisionPart>())
		{
			DieOnCollisionPart* dieOnCollisionPart
				= game_object_->GetPart<DieOnCollisionPart>();
			dieOnCollisionPart->set_is_active(true);
		}

		game_object_->Detach<GhostPart>();
	}

	ghost_timer_.Update(dt);
}