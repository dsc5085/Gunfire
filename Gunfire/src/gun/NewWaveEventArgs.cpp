#include <boost\lexical_cast.hpp>

#include "NewWaveEventArgs.h"

gun::NewWaveEventArgs::NewWaveEventArgs(int wave_index)
	: wave_index(wave_index)
{
}

std::string gun::NewWaveEventArgs::Details()
{
	std::string details = "NewWave { wave = "
		+ boost::lexical_cast<std::string>(wave_index) + " }";
	return details;
}