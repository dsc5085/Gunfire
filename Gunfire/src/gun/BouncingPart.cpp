#include "BouncingPart.h"
#include "GameObject.h"
#include "Services.h"

void gun::BouncingPart::Update(double dt)
{
	sf::FloatRect bounds = Services::Instance().level().area;
	sf::FloatRect coll_box = game_object_->coll_box();

	if (coll_box.top < bounds.top)
	{
		// top bounds
		if (game_object_->velocity().y < 0)
		{
			game_object_->velocity().y *= -1;
		}
	}
	if (coll_box.top + coll_box.height > bounds.top + bounds.height)
	{
		// bottom bounds
		if (game_object_->velocity().y > 0)
		{
			game_object_->velocity().y *= -1;
		}
	}
	if (coll_box.left < bounds.left)
	{
		// left bounds
		if (game_object_->velocity().x < 0)
		{
			game_object_->velocity().x *= -1;
		}
	}
	if (coll_box.left + coll_box.width > bounds.left + bounds.width)
	{
		// right bounds
		if (game_object_->velocity().x > 0)
		{
			game_object_->velocity().x *= -1;
		}
	}
}