#ifndef GUN_COLLIDED_EVENT_ARGS_H
#define GUN_COLLIDED_EVENT_ARGS_H

#include "EventArgs.h"

namespace gun
{
	class GameObject;

	class CollidedEventArgs : public EventArgs
	{
	public:
		GameObject* game_object1;
		GameObject* game_object2;

		CollidedEventArgs(GameObject* game_object1, GameObject* game_object2);

		std::string Details();
	};
}

#endif