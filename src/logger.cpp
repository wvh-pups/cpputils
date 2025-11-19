#include "utils/logger.hpp"
#include "utils/string.hpp"

#include <ctime>
#include <cstdlib>

using namespace utl;

const char* Logger_::s_info_prefix = "[INFO]";
const char* Logger_::s_warn_prefix = "[WARN]";
const char* Logger_::s_err_prefix = "[ERROR]";
const char* Logger_::s_dbg_prefix = "[DEBUG]";

void utl::println(const char* str)
{
	printf("%s\n", str);
}

void utl::println(const string& str)
{
	printf("%s\n", str.c_str());
}

// Logger_ impl

char* Logger_::get_formatted_time()
{
	time_t unix_time = time(NULL);
	tm* time_struct = localtime(&unix_time);

	int hours = time_struct->tm_hour;
	int minutes = time_struct->tm_min;
	int seconds = time_struct->tm_sec;

	char* formatted_str = new char[11];

	if (minutes >= 10 && seconds >= 10)
	{
		snprintf(formatted_str, 11, "[%d:%d:%d]", hours, minutes, seconds);
	}
	else if (minutes < 10 && seconds >= 10)
	{
		snprintf(formatted_str, 11, "[%d:0%d:%d]", hours, minutes, seconds);
	}
	else if (seconds < 10 && minutes >= 10)
	{
		snprintf(formatted_str, 11, "[%d:%d:0%d]", hours, minutes, seconds);
	}
	else
	{
		snprintf(formatted_str, 11, "[%d:0%d:0%d", hours, minutes, seconds);
	}

	return formatted_str;
}

char* Logger_::format_log(const char* base_str, LogLevel level)
{
	char* time_str = get_formatted_time();

	const char* level_str;

	switch (level)
	{
	case Info:
		level_str = s_info_prefix;

		break;
	case Warn:
		level_str = s_warn_prefix;

		break;
	case Error:
		level_str = s_err_prefix;

		break;
	case Debug:
		level_str = s_dbg_prefix;

		break;
	default:
		level_str = "[NULL]";
	}

	size_t str_size;

	if (strlen(base_str) * 2 > 20)
	{
		str_size = strlen(base_str) * 2;
	}
	else
	{
		str_size = 20;
	}

	str_size += 11 + 7;

	char* result_str = new char[str_size];

	snprintf(result_str, str_size, "%s%s %s", time_str, level_str, base_str);

	delete[] time_str;

	return result_str;
}

// actual functions impl

void utl::log(const char* base_str, LogLevel level)
{
	char* result_str = Logger_::format_log(base_str, level);

	println(result_str);

	delete[] result_str;
}

void utl::log(const string& base_str, LogLevel level)
{
	char* result_str = Logger_::format_log(base_str.c_str(), level);

	println(result_str);

	delete[] result_str;
}
