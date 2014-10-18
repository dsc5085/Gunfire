#include <string>
#include <boost\lexical_cast.hpp>

#include "WaveCompleteEventArgs.h"

gun::WaveCompleteEventArgs::WaveCompleteEventArgs(int wave_index, int time_bonus)
	: wave_index(wave_index), time_bonus(time_bonus)
{
}

std::string gun::WaveCompleteEventArgs::Details()
{
	std::string details = "WaveComplete { wave = "
		+ boost::lexical_cast<std::string>(wave_index) + " timebonus="
		+ boost::lexical_cast<std::string>(time_bonus) + " }";
	return details;
}