#ifndef GUN_DIED_EVENT_ARGS_H
#define GUN_DIED_EVENT_ARGS_H

#include "EventArgs.h"

namespace gun
{
	class GameObject;

	class DiedEventArgs : public EventArgs
	{
	public:
		GameObject* game_object;

		DiedEventArgs(GameObject* game_object);

		std::string Details();
	};
}

#endif