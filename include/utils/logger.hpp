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
		int formatted_str_length;

		if (strlen(str) * 8 > 64)
		{
			formatted_str_length = strlen(str) * 8;
		}
		else
		{
			formatted_str_length = 64;
		}

		char* formatted_string = new char[formatted_str_length];

		sprintf(formatted_string, str, args...);

		printf("%s\n", formatted_string);

		fflush(stdout);

		delete[] formatted_string;
	}

	// explicit println call with variadic arguments
	template <typename... Args>
	void printv(const char* str, Args... args)
	{
		println(str, args...);
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

		friend class LoggingHandler;

		// [INFO]
		static const char* s_info_prefix;

		// [WARN]
		static const char* s_warn_prefix;

		// [ERROR]
		static const char* s_err_prefix;

		// [DEBUG]
		static const char* s_dbg_prefix;

		// returns something like [17:25:16] in UTC
		// resulting string is your responsibility
		static char* get_formatted_time();

		// returns formatted time without the braces
		// 17:25:16
		static char* get_formatted_time_new();

	public:

		// formats string by adding time and log level at the start.
		// the result string is your responsibility
		static char* format_log(const char* base_str, LogLevel level);
		static char* format_log(const char* base_str, const char* id, LogLevel level);

	};

	// based on the Logger_ class
	// allows for logging functions with an "ID"
	class LoggingHandler
	{
		// string, owned by this class
		char* m_id;

	public:

		LoggingHandler();
		LoggingHandler(const char* id);

		LoggingHandler(const LoggingHandler& other);
		LoggingHandler(LoggingHandler&& other) noexcept;

		LoggingHandler& operator=(const LoggingHandler& other);
		LoggingHandler& operator=(LoggingHandler&& other) noexcept;

		~LoggingHandler();

		const char* GetID() const
		{
			return m_id;
		}

		void log(const char* str, LogLevel level) const;
		void log(const string& str, LogLevel level) const;

	};

}