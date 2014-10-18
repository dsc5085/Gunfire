#ifndef GUN_WAVE_COMPLETE_EVENT_ARGS_H
#define GUN_WAVE_COMPLETE_EVENT_ARGS_H

#include "EventArgs.h"

namespace gun
{
	class WaveCompleteEventArgs : public EventArgs
	{
	public:
		int wave_index;
		int time_bonus;

		WaveCompleteEventArgs(int wave_index, int time_bonus);

		std::string Details();
	};
}

#endif