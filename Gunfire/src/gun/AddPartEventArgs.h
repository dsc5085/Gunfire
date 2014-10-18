#ifndef GUN_ADD_PART_EVENT_ARGS_H
#define GUN_ADD_PART_EVENT_ARGS_H

#include "EventArgs.h"

namespace gun
{
	class GameObject;

	class AddPartEventArgs : public EventArgs
	{
	public:
		GameObject* adder;
		GameObject* receiver;

		AddPartEventArgs(GameObject* adder, GameObject* receiver);

		std::string Details();
	};
}

#endif