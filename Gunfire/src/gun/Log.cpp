#include <boost\filesystem.hpp>

#include "Log.h"
#include "Paths.h"

void gun::Log::Initialize()
{
	boost::log::add_common_attributes();

	time_t now = time(0);
	struct tm time_info;
	localtime_s(&time_info, &now);
	char buf[80];
	strftime(buf, sizeof(buf), "%Y%m%d%H%M%S", &time_info);

	boost::log::add_file_log
    (
        boost::log::keywords::file_name = Paths::LOGS_DIR + "Gunfire_" + std::string(buf) + ".log",
        // This makes the sink write log records that look like this:
        // YYYY-MM-DD HH:MI:SS [info] An info severity message
        // YYYY-MM-DD HH:MI:SS [error] An error severity message
        boost::log::keywords::format =
        (
			boost::log::expressions::stream
				<< boost::log::expressions::format_date_time(timestamp, "%Y-%m-%d %H:%M:%S")
				<< " [" << boost::log::trivial::severity << "] "
				<< boost::log::expressions::smessage
        )
    );

#if (!_DEBUG)
	// Remove existing log files.
	// Set log filter to exclude low-level messages.
	boost::filesystem::remove_all(Paths::LOGS_DIR);
    boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= boost::log::trivial::info
    );
#endif
}