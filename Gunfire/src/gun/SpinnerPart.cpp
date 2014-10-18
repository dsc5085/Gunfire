#include "SpinnerPart.h"
#include "GameObject.h"

gun::SpinnerPart::SpinnerPart(float spin_speed)
	: spin_speed_(spin_speed)
{
}

void gun::SpinnerPart::Update(double dt)
{
	game_object_->sprite().set_rotation(
		game_object_->sprite().rotation() + (float)(spin_speed_ * dt));
}