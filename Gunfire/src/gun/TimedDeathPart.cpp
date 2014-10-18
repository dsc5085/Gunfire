#include "TimedDeathPart.h"
#include "GameObject.h"

gun::TimedDeathPart::TimedDeathPart(double max_age)
	: max_age_(max_age)
{
}

void gun::TimedDeathPart::Update(double dt)
{
	if (game_object_->age() >= max_age_)
	{
		game_object_->Die();
	}
}