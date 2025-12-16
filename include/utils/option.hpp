#ifndef OPTION_HPP
#define OPTION_HPP

#include <cstdint>
#include <typeinfo>
#include <cstdio>

// a little bit of the old 'ultra-violence' (hi from rust)

namespace utl
{

	template <typename T>
	class option
	{

	public:

		// this function is called when you do not want to return any value,
		// so that program crashes
		typedef void (*PanicOrElseCallbackFunc)(const option&);

		// if the value is None, then unwrap_or_else() returns
		// the value that this function returns
		typedef T& (*ReturningOrElseCallbackFunc)(const option&);

	private:

		T* m_data;

		enum : uint8_t
		{
			None = 0,
			Some
		} m_type;

		static void print_error_message()
		{
			print_error_message("print_error_message");
		}

		static void print_error_message(const char* functionName)
		{
			std::printf("Failed to unwrap the value!\nFunction: utl::option<T>::%s()\nType: %s", functionName, typeid(T()).name());
		}

	public:

		option()
			: m_data(nullptr)
		{
			m_type = None;
		}

		option(const T& object)
		{
			m_data = new T(object);
			m_type = Some;
		}

		~option()
		{
			delete m_data;
		}

		option(const option& other)
		{
			m_data = new T(other.m_data);
			m_type = Some;
		}

		option(option&& other) noexcept
		{
			m_data = other.m_data;
			m_type = Some;

			other.m_data = nullptr;
			other.m_type = None;
		}

		option& operator=(const option& other)
		{
			if (this == &other)
			{
				return *this;
			}

			m_data = new T(other.m_data);
			m_type = Some;

			return *this;
		}

		option& operator=(option&& other) noexcept
		{
			if (this == &other)
			{
				return *this;
			}

			m_data = other.m_data;
			m_type = Some;

			other.m_data = nullptr;
			other.m_type = None;

			return *this;
		}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-type"

		// ts only returns a reference to the data
		T& unwrap() const
		{
			if (m_type == Some)
			{
				return *m_data;
			}

			print_error_message("unwrap");
		}

		T& unwrap_or_else(PanicOrElseCallbackFunc callback) const
		{
			if (m_type == Some)
			{
				return *m_data;
			}

			print_error_message("unwrap_or_else");

			callback(*this);
		}

#pragma clang diagnostic pop

		T& unwrap_or_else(ReturningOrElseCallbackFunc callback) const
		{
			if (m_type == Some)
			{
				return *m_data;
			}

			return callback(*this);
		}

	};

}

#endif
