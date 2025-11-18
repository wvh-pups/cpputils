#pragma once

/* returns the length of the array
* usage:
* int array[4] = { 45, 10, 25, 25 };
* int length = UARRLEN(array);
*/
#define UARRLEN(arr) (sizeof(arr) / sizeof(*arr))

namespace utl
{

	// standard array class, where T is your preferred type, and S is the length of the array
	template <typename T, int S>
	class array
	{

		T* m_data;

		// constant array size
		const unsigned int m_size = S;

	public:

		array()
		{
			m_data = new T[m_size];
		}

		array(T (&arr)[S])
		{
			if (UARRLEN(arr) != m_size)
			{
				static_assert(0, "utl::array sizes differ");
			}
			else
			{
				m_data = new T[m_size];

				for (int i = 0; i < m_size; i++)
				{
					m_data[i] = arr[i];
				}
			}
		}

		array(const array& other)
		{
			if (other.m_size != this->m_size)
			{
				static_assert(0, "utl::array sizes differ");
			}

			m_data = new T[m_size];

			for (int i = 0; i < m_size; i++)
			{
				m_data[i] = other.m_data[i];
			}
		}

		array(array&& other) noexcept : m_data(other.m_data)
		{
			other.m_data = nullptr;
		}

		~array()
		{
			delete[] m_data;
		}

		array& operator=(T (&arr)[S])
		{
			delete[] this->m_data;

			if (UARRLEN(arr) != m_size)
			{
				static_assert(0, "utl::array sizes differ");
			}
			else
			{
				this->m_data = new T[m_size];

				for (int i = 0; i < m_size; i++)
				{
					this->m_data[i] = arr[i];
				}
			}

			return *this;
		}

		array& operator=(const array& other)
		{
			if (this == &other)
			{
				return *this;
			}

			delete[] this->m_data;

			this->m_data = new T[m_size];

			for (int i = 0; i < m_size; i++)
			{
				this->m_data[i] = other.m_data[i];
			}

			return *this;
		}

		array& operator=(array&& other) noexcept
		{
			if (this == &other)
			{
				return *this;
			}

			delete[] this->m_data;

			this->m_data = other.m_data;
			other.m_data = nullptr;

			return *this;
		}

		// returns a pointer to the beginning of the array
		T* data()
		{
			return m_data;
		}

		// returns a constant pointer to the beginning of the array
		const T* data() const
		{
			return m_data;
		}

		// returns a specific element in this array
		T& operator[](unsigned int index)
		{
			return m_data[index];
		}

		// returns a specific element in this array
		const T& operator[](unsigned int index) const
		{
			return m_data[index];
		}

		// returns the length of this array
		unsigned int length() const
		{
			return m_size;
		}

		// returns the length of this array
		unsigned int size() const
		{
			return m_size;
		}

		// returns a pointer to the beginning of the array
		T* begin() const
		{
			return &m_data[0];
		}

		// returns a pointer to the end of the array + 1
		T* end() const
		{
			return &m_data[m_size];
		}
	};
}