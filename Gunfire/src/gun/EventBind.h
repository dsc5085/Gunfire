#ifndef GUN_EVENT_BIND_H
#define GUN_EVENT_BIND_H

#include <boost\signals2.hpp>

namespace gun
{
	class EventBind
	{
	public:
		EventBind();
		EventBind(const boost::signals2::connection& connection);

		void Block();
		void Unblock();
		void Unsubscribe();

	private:
		boost::signals2::connection connection_;
		boost::signals2::shared_connection_block block_;
	};
}

#endif