#pragma once

#include <cstdio>

namespace utl
{

	// returns the length of the string, without accounting for terminating character
	unsigned int ustrlen(const char* str);

	// works kinda like printf()
	// the result string is your responsibility, please free it
	template <typename... Args>
	char* strfmt(const char* str, Args... args)
	{
		char* result_string = new char[ustrlen(str) * 5];
		sprintf(result_string, str, args...);
		return result_string;
	}

	// string class bro
	class string
	{

		char* m_str;

		// concatenates two strings together
		friend string operator+(const string& left, const string& right);

	public:

		// constructors & destructors stuff

		string();
		string(const char* str);

		~string();

		string(const string& other);
		string(string&& other) noexcept;

		string& operator=(const char* str);

		string& operator=(const string& other);
		string& operator=(string&& other) noexcept;

		// returns length of the string, without accounting for the terminating character
		unsigned int length() const
		{
			return ustrlen(m_str);
		}

		// returns length of the string, without accounting for the terminating character
		unsigned int size() const
		{
			return ustrlen(m_str);
		}

		// works kinda like printf()
		template <typename... Args>
		static string strfmt(const string& str, Args... args)
		{
			char* result_string = new char[ustrlen(str.c_str()) * 5];

			sprintf(result_string, str.c_str(), args...);

			string new_str(result_string);

			delete[] result_string;

			return new_str;
		}

		// returns a pointer to the beginning of the string
		const char* c_str() const
		{
			return m_str;
		}

		// compares two strings together
		bool operator==(const string& other) const;

		// returns a pointer to the first element of the string
		char* begin() const
		{
			return &m_str[0];
		}

		// returns a pointer to the last element of the string
		char* end() const
		{
			return &m_str[ustrlen(m_str)];
		}
	};

}