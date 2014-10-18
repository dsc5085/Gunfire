#include "DiedEventArgs.h"
#include "GameObject.h"

gun::DiedEventArgs::DiedEventArgs(GameObject* game_object)
	: game_object(game_object)
{
}

std::string gun::DiedEventArgs::Details()
{
	std::string details = "Died { object = " + game_object->Details() + " }";
	return details;
}