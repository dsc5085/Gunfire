#ifndef GUN_EVENT_H
#define GUN_EVENT_H

#include <boost\signals2.hpp>
#include <boost\concept_check.hpp>

#include "EventBase.h"
#include "EventArgs.h"
#include "EventBind.h"

namespace gun
{
	template<class T>
	class Event : public EventBase
	{
	public:
		BOOST_CONCEPT_ASSERT((boost::Convertible<T, EventArgs>));

		void Publish(T &event_args)
		{
			signal_(event_args);
		}

		EventBind Subscribe(const boost::function<void(T&)> &event_handler)
		{
			return EventBind(signal_.connect(event_handler));
		}

	private:
		boost::signals2::signal<void (T&)> signal_;
	};
}

#endif