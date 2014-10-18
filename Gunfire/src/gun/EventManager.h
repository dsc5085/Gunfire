#ifndef GUN_EVENT_MANAGER_H
#define GUN_EVENT_MANAGER_H

#include <map>
#include <boost\concept_check.hpp>
#include <boost\ptr_container\ptr_map.hpp>

#include "Event.h"
#include "Log.h"

namespace gun
{
	class EventManager
	{
	public:
		template<class T>
		EventBind Subscribe(const boost::function<void(T&)>& event_handler)
		{
			BOOST_CONCEPT_ASSERT((boost::Convertible<T, EventArgs>));

			Event<T>* event = FindEvent<T>();

			return event->Subscribe(event_handler);
		}

		template<class T>
		void Publish(T& event_args)
		{
			BOOST_CONCEPT_ASSERT((boost::Convertible<T, EventArgs>));

			Event<T>* event = FindEvent<T>();
			event->Publish(event_args);

			BOOST_LOG_TRIVIAL(trace) << "EVENT: "
				<< static_cast<EventArgs*>(&event_args)->Details();
		}

	private:
		boost::ptr_map<int, EventBase> events_;

		template<class T>
		Event<T>* FindEvent()
		{
			BOOST_CONCEPT_ASSERT((boost::Convertible<T, EventArgs>));

			int key = typeid(T).hash_code();

			if(events_.find(key) == events_.end())
			{
				events_.insert(key, new Event<T>());
			}

			return static_cast<Event<T>*>(events_.find(key)->second);
		}
	};
}

#endif