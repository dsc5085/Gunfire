#include "FireRateMultiplierPart.h"
#include "GameObject.h"
#include "PlayerControllerPart.h"
#include "Services.h"
#include "SoundCache.h"

gun::FireRateMultiplierPart::FireRateMultiplierPart(
	double effect_time, float multiplier)
	: effect_timer_(Timer(effect_time, 0)), multiplier_(multiplier)
{
}

void gun::FireRateMultiplierPart::Initialize()
{
	PlayerControllerPart* player_controller
		= game_object_->GetPart<PlayerControllerPart>();
	old_reload_time_ = player_controller->reload_time();
	player_controller->set_reload_time(old_reload_time_ * multiplier_);
	Services::Instance().sound_cache()->PlaySound(SoundKey::MALE_YES);
}

void gun::FireRateMultiplierPart::Cleanup()
{
	PlayerControllerPart* player_controller
		= game_object_->GetPart<PlayerControllerPart>();
	player_controller->set_reload_time(old_reload_time_);
}

void gun::FireRateMultiplierPart::Update(double dt)
{
	if(effect_timer_.is_time())
	{
		game_object_->Detach<FireRateMultiplierPart>();
	}

	effect_timer_.Update(dt);
}