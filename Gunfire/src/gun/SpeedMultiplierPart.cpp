#include "SpeedMultiplierPart.h"
#include "GameObject.h"
#include "Services.h"
#include "SoundCache.h"

gun::SpeedMultiplierPart::SpeedMultiplierPart(double effect_time, float multiplier)
	: effect_timer_(Timer(effect_time, 0)), multiplier_(multiplier)
{
}

void gun::SpeedMultiplierPart::Initialize()
{
	old_max_speed_ = game_object_->max_speed();
	game_object_->max_speed() *= multiplier_;
	Services::Instance().sound_cache()->PlaySound(SoundKey::MALE_YES);
}

void gun::SpeedMultiplierPart::Cleanup()
{
	game_object_->max_speed() = old_max_speed_;
}

void gun::SpeedMultiplierPart::Update(double dt)
{
	if(effect_timer_.is_time())
	{
		game_object_->Detach<SpeedMultiplierPart>();
	}

	effect_timer_.Update(dt);
}