#include <boost\lexical_cast.hpp>

#include "CollidedEventArgs.h"
#include "GameObject.h"

gun::CollidedEventArgs::CollidedEventArgs(
	GameObject* game_object1, GameObject* game_object2)
	: game_object1(game_object1), game_object2(game_object2)
{
}

std::string gun::CollidedEventArgs::Details()
{
	std::string details = "Collided { object1=" + game_object1->Details()
		+ ", object2 = " + game_object2->Details() + " }";
	return details;
}