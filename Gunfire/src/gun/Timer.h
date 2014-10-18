#ifndef GUN_TIMER_H
#define GUN_TIMER_H

namespace gun
{
	class Timer
	{
	public:
		bool is_running() const { return is_running_; }
		bool is_time() const { return current_time_ >= max_time_; }
		double max_time() { return max_time_; }
		double current_time() { return current_time_; }
		void set_max_time(double max_time) { max_time_ = max_time; }

		Timer();
		Timer(double max_time);
		Timer(double max_time, double current_time);
		
		void Start();
		void Stop();
		bool Check();
		void Update(double dt);

	private:
		bool is_running_;
		double max_time_;
		double current_time_;
	};
}

#endif