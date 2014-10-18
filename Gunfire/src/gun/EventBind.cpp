#include "EventBind.h"

gun::EventBind::EventBind()
{
}

gun::EventBind::EventBind(const boost::signals2::connection& connection)
	: connection_(connection)
{
}

void gun::EventBind::Unsubscribe()
{
	if (connection_.connected())
	{
		connection_.disconnect();
	}
}