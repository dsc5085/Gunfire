#ifndef GUN_NEW_WAVE_EVENT_ARGS_H
#define GUN_NEW_WAVE_EVENT_ARGS_H

#include "EventArgs.h"

namespace gun
{
	class NewWaveEventArgs : public EventArgs
	{
	public:
		int wave_index;

		NewWaveEventArgs(int wave_index);

		std::string Details();
	};
}

#endif