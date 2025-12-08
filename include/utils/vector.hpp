#pragma once

namespace utl
{

	// professional vector class
	template <typename T>
	class vector
	{

	private:

		T* m_data;
		unsigned int m_size;
		unsigned int m_capacity;

	public:

		// standard constructor
		vector()
		{
			m_data = new T[1];
			m_size = 0;
			m_capacity = 1;
		}

		// cool constructor
		// example: utl::vector<int>( {45, 16, 30} )
		explicit vector(T array[])
		{
			unsigned int length = sizeof(array) / sizeof(*array);

			m_data = new T[length];

			for (unsigned int i = 0; i < length; i++)
			{
				m_data[i] = array[i];
			}

			m_size = length;
			m_capacity = length;
		}

		~vector()
		{
			delete[] m_data;

			m_size = 0;
			m_capacity = 0;
		}

		vector(const vector& other)
		{
			m_data = new T[other.m_capacity];

			for (int i = 0; i < other.m_size; i++)
			{
				m_data[i] = other.m_data[i];
			}

			m_size = other.m_size;
			m_capacity = other.m_capacity;
		}

		vector(vector&& other) noexcept : m_data(other.m_data), m_capacity(other.m_capacity), m_size(other.m_size)
		{
			other.m_data = nullptr;
			other.m_size = 0;
			other.m_capacity = 0;
		}

		// deep copy
		vector& operator=(const vector& other)
		{
			if (this == &other)
			{
				return *this;
			}

			delete[] this->m_data;

			this->m_data = new T[other.m_capacity];

			for (int i = 0; i < other.m_size; i++)
			{
				this->m_data[i] = other.m_data[i];
			}

			this->m_size = other.m_size;
			this->m_capacity = other.m_capacity;
		}

		// move
		vector& operator=(vector&& other) noexcept
		{
			if (this == &other)
			{
				return *this;
			}

			delete[] this->m_data;

			this->m_data = other.m_data;
			this->m_capacity = other.m_capacity;
			this->m_size = other.m_size;

			other.m_data = nullptr;
			other.m_capacity = 0;
			other.m_size = 0;

			return *this;
		}

		// reserves a specified amount of size and adds them to the overall capacity
		void reserve(unsigned int size)
		{
			T* temp = new T[m_capacity + size];

			for (int i = 0; i < m_size; i++)
			{
				temp[i] = m_data[i];
			}

			delete[] m_data;

			m_data = temp;

			m_capacity += size;
		}

		// copies an element into the back of the vector
		void push_back(const T& element)
		{
			if (m_size == m_capacity)
			{
				reserve(2 * m_capacity);
			}

			m_data[m_size] = element;
			m_size++;
		}

		// deletes the last element of the vector
		void pop_back()
		{
			m_size--;
		}

		// fully nukes the vector, returning it into the initial state
		void clear()
		{
			delete[] m_data;

			m_data = new T[1];
			m_size = 0;
			m_capacity = 1;
		}

		T& get(unsigned int index) const
		{
			return m_data[index];
		}

		unsigned int size() const
		{
			return m_size;
		}

		unsigned int length() const
		{
			return m_size;
		}

		void erase(const unsigned int index)
		{
			if (index > m_size || index == 0)
			{
				return;
			}

			for (int i = index; i < m_size - 1; i++)
			{
				m_data[i] = m_data[i + 1];
			}

			m_size--;
		}

		T& operator[](unsigned int index)
		{
			return get(index);
		}

		T operator[](unsigned int index) const
		{
			return get(index);
		}

		const T* ptr() const
		{
			return m_data;
		}

		const T* data() const
		{
			return m_data;
		}

		T* begin() const
		{
			return &m_data[0];
		}

		T* end() const
		{
			return &m_data[m_size];
		}
	};
}