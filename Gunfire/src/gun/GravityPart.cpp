#include "GravityPart.h"
#include "GameObject.h"

const float gun::GravityPart::GRAVITY = 40;

void gun::GravityPart::Update(double dt)
{
	game_object_->velocity().y += (float)(GRAVITY * dt);
}