#include "BoundingPart.h"
#include "Collision.h"
#include "GameObject.h"
#include "Services.h"

gun::BoundingPart::BoundingPart(const sf::FloatRect& bound)
{
	bounds_.push_back(bound);
}

gun::BoundingPart::BoundingPart(const std::vector<sf::FloatRect>& bounds)
	: bounds_(bounds)
{
}

void gun::BoundingPart::Update(double dt)
{
	sf::FloatRect coll_box = game_object_->coll_box();

	// Attempt to find a bounds area for the gameobject.
	while (bounds_.size() > 1 && Collision::IsInBounds(
		coll_box, bounds_[bounds_.size() - 2]))
	{
		bounds_.pop_back();
	}

	sf::FloatRect bound = bounds_.back();

	// Check bounds.
	if (coll_box.top < bound.top)
	{
		game_object_->position().y = bound.top;
	}
	if (coll_box.top + coll_box.height > bound.top + bound.height)
	{
		game_object_->position().y = bound.top + bound.height - coll_box.height;
	}
	if (coll_box.left < bound.left)
	{
		game_object_->position().x = bound.left;
	}
	if (coll_box.left + coll_box.width > bound.left + bound.width)
	{
		game_object_->position().x = bound.left + bound.width - coll_box.width;
	}
}