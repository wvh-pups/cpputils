#include "utils/string.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>

using namespace utl;

unsigned int utl::ustrlen(const char* str)
{
	return strlen(str);
}

string utl::operator+(const string& left, const string& right)
{
	unsigned int length = ustrlen(left.c_str()) + ustrlen(right.c_str());

	char* buffer = new char[length + 1];

	strcpy(buffer, left.c_str());
	strcat(buffer, right.c_str());
	buffer[length] = '\0';

	string str(buffer);

	delete[] buffer;

	return str;
}

std::ostream& utl::operator<<(std::ostream& stream, const string& string)
{
	stream << string.m_str;

	return stream;
}

string::string() : m_str(nullptr)
{

}

string::string(const char* str)
{
	if (!str)
	{
		m_str = new char[1];
		m_str[0] = '\0';
	}

	else
	{
		m_str = new char[ustrlen(str) + 1];
		strcpy(m_str, str);
		m_str[ustrlen(str)] = '\0';
	}
}

string::~string()
{
	delete[] m_str;
}

// warning: radioactive code

string::string(const string& other)
{
	m_str = new char[ustrlen(other.c_str()) + 1];
	strcpy(m_str, other.c_str());
	m_str[ustrlen(other.c_str())] = '\0';
}

string::string(string&& other) noexcept : m_str(other.m_str)
{
	other.m_str = nullptr;
}

string& string::operator=(const char* str)
{
	delete[] m_str;

	this->m_str = new char[ustrlen(str) + 1];
	strcpy(m_str, str);
	this->m_str[ustrlen(str)] = '\0';

	return *this;
}

string& string::operator=(const string& other)
{
	if (this == &other)
	{
		return *this;
	}

	delete[] m_str;

	this->m_str = new char[ustrlen(other.c_str()) + 1];
	strcpy(m_str, other.c_str());
	this->m_str[ustrlen(other.c_str())] = '\0';

	return *this;
}

string& string::operator=(string&& other) noexcept
{
	this->m_str = other.m_str;
	other.m_str = nullptr;

	return *this;
}

bool string::operator==(const string& other) const
{
	if (!strcmp(m_str, other.m_str))
	{
		return true;
	}
	else
	{
		return false;
	}
}