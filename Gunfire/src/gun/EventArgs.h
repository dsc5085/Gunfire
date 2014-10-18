#ifndef GUN_EVENT_ARGS_H
#define GUN_EVENT_ARGS_H

#include <string>

namespace gun
{
	class EventArgs
	{
	public:
		virtual ~EventArgs() { }

		virtual std::string Details() { return ""; }
	};
}

#endif