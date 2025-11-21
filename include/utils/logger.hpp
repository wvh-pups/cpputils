#pragma once

#include <cstdio>
#include <cstring>

namespace utl
{

	class string;

	// works kinda like the printf function
	// utl::println("Hello, %s", "Outsourced");
	// gets translated to "Hello, Outsourced",
	// which is then printed to the stdout
	template <typename... Args>
	void println(const char* str, Args... args)
	{
		char* formatted_string = new char[strlen(str) * 8];

		snprintf(formatted_string, str, args...);

		printf("%s\n", formatted_string);

		fflush(stdout);

		delete[] formatted_string;
	}

	// just prints a string without any variadic arguments
	void println(const char* str);

	void println(const string& str);

	enum LogLevel
	{
		Info,
		Warn,
		Error,
		Debug
	};

	/*
	 * Logs like this:
	 * [TIME] [LEVEL] *message*
	 */
	void log(const char* base_str, LogLevel level);

	void log(const string& base_str, LogLevel level);

	// internal static class (almost C# at this point) that stores static variables and some helpful functions
	// this class is used by the log() function
	class Logger_
	{
		// [INFO]
		static const char* s_info_prefix;

		// [WARN]
		static const char* s_warn_prefix;

		// [ERROR]
		static const char* s_err_prefix;

		// [DEBUG]
		static const char* s_dbg_prefix;

		// returns something like [17:25:16] in UTC
		// the result string is always 10 chars long excluding terminating character
		// returns a string which is your responsibility
		static char* get_formatted_time();

	public:

		// formats string by adding time and log level at the start.
		// the result string is your responsibility
		static char* format_log(const char* base_str, LogLevel level);
	};

}