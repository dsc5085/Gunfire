#ifndef GUN_GAME_OVER_EVENT_ARGS_H
#define GUN_GAME_OVER_EVENT_ARGS_H

#include "EventArgs.h"

namespace gun
{
	class GameOverEventArgs : public EventArgs
	{
		std::string Details();
	};
}

#endif