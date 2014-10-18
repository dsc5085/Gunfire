#include "Timer.h"

gun::Timer::Timer()
	: is_running_(true), max_time_(0), current_time_(0)
{
}

gun::Timer::Timer(double max_time)
	: is_running_(true), max_time_(max_time), current_time_(max_time)
{
}

gun::Timer::Timer(double max_time, double current_time)
	: is_running_(true), max_time_(max_time), current_time_(current_time)
{
}

void gun::Timer::Start()
{
	is_running_ = true;
}

void gun::Timer::Stop()
{
	is_running_ = false;
}

bool gun::Timer::Check()
{
	bool is_time = this->is_time();

	if(is_time)
	{
		current_time_ = 0;
	}

	return is_time;
}

void gun::Timer::Update(double dt)
{
	if(is_running_ && current_time_ < max_time_)
	{
		current_time_ += dt;
	}
}