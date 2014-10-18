#include "DieAfterAnimationPart.h"
#include "GameObject.h"

void gun::DieAfterAnimationPart::Update(double dt)
{
	if(!game_object_->sprite().is_playing())
	{
		game_object_->Die();
	}
}