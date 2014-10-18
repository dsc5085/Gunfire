#include "AddPartEventArgs.h"
#include "GameObject.h"

gun::AddPartEventArgs::AddPartEventArgs(
	GameObject* adder, GameObject* receiver)
	: adder(adder), receiver(receiver)
{
}

std::string gun::AddPartEventArgs::Details()
{
	std::string details = "AddPart { adder=" + adder->Details()
		+ " receiver = " + receiver->Details() + " }";
	return details;
}