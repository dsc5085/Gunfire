#include <math.h>

#include "VelocityRandomizerPart.h"
#include "Math.h"
#include "VectorMath.h"
#include "GameObject.h"

void gun::VelocityRandomizerPart::Initialize()
{
	double angle = Math::Random(0, 2 * M_PI);
	game_object_->velocity() = VectorMath::Velocity(
		(float)angle, game_object_->max_speed());
}