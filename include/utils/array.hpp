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

		array(T arr[])
		{
			m_data = new T[m_size];

			for (int i = 0; i < m_size; i++)
			{
				m_data[i] = arr[i];
			}
		}

		array(const array& other)
		{
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

		array& operator=(T arr[])
		{
			delete[] this->m_data;

			this->m_data = new T[m_size];

			for (int i = 0; i < m_size; i++)
			{
				this->m_data[i] = arr[i];
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

	// two-dimensional class, where T is your preferred type, X is horizontal size and Y is vertical
	template <typename T, int X, int Y>
	class array_2d
	{
		T** m_upper_data;

		const int m_x = X;
		const int m_y = Y;

	public:

		array_2d()
		{
			m_upper_data = new T*[m_y];

			for (int i = 0; i < m_x; i++)
			{
				m_upper_data[i] = new T[m_x];
			}
		}

		array_2d(const array_2d& other)
		{
			m_upper_data = new T*(other.m_upper_data);

			for (int i = 0; i < m_x; i++)
			{
				m_upper_data[i] = new T(other.m_upper_data[i]);
			}
		}

		array_2d(array_2d&& other) noexcept
		{
			m_upper_data = other.m_upper_data;

			for (int i = 0; i < m_x; i++)
			{
				m_upper_data[i] = other.m_upper_data[i];
				other.m_upper_data[i] = nullptr;
			}

			other.m_upper_data = nullptr;
		}

		~array_2d()
		{
			for (int i = 0; i < m_x; i++)
			{
				delete[] m_upper_data[i];
			}

			delete[] m_upper_data;
		}

		array_2d& operator=(const array_2d& other)
		{
			if (this == &other)
			{
				return *this;
			}

			for (int i = 0; i < m_x; i++)
			{
				delete[] this->m_upper_data[i];
			}

			delete[] this->m_upper_data;

			this->m_upper_data = new T*(other.m_upper_data);

			for (int i = 0; i < m_x; i++)
			{
				this->m_upper_data[i] = new T(other.m_upper_data[i]);
			}

			return *this;
		}

		array_2d& operator=(array_2d&& other) noexcept
		{
			if (this == &other)
			{
				return *this;
			}

			for (int i = 0; i < m_x; i++)
			{
				delete[] this->m_upper_data[i];
			}

			delete[] this->m_upper_data;

			this->m_upper_data = other.m_upper_data;

			for (int i = 0; i < m_x; i++)
			{
				this->m_upper_data[i] = other.m_upper_data[i];
				other.m_upper_data[i] = nullptr;
			}

			other.m_upper_data = nullptr;

			return *this;
		}

		// returns a pointer to the start of the two-dimensional array
		T* data()
		{
			return m_upper_data;
		}

		// returns a constant pointer to the start of the two-dimensional array
		const T* data() const
		{
			return m_upper_data;
		}

		// returns a vertical strip on the index
		T* operator[](unsigned int index)
		{
			return m_upper_data[index];
		}

		// returns a constant pointer to the vertical strip at the index
		const T* operator[](unsigned int index) const
		{
			return m_upper_data[index];
		}

		// returns the vertical length of this array
		unsigned int vertical() const
		{
			return m_y;
		}

		// returns the horizontal length of this array
		unsigned int horizontal() const
		{
			return m_x;
		}

		// returns a pointer to the beginning of the array
		T* begin() const
		{
			return &m_upper_data[0];
		}

		// returns a pointer to the end of the vertical strips + 1
		T* end() const
		{
			return &m_upper_data[m_y];
		}
	};

}