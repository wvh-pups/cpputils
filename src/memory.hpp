#pragma once

#include <cstdlib>

namespace utl
{

	// allocates the specified size of the heap, and returns a pointer to the beginning of that block
	// uses malloc() function under the hood
	void* heap(unsigned long long size);

	// frees the allocated memory by utl::heap()
	// uses free() function under the hood
	void ufree(void* data);

	// automatic pointer with self cleanup
	// this class assumes that this is not a pointer to the array of some kind
	// for array pointers use utl::array or utl::multi_array
	template <typename T>
	class ptr
	{

		T* m_ptr;

	public:

		ptr()
		{
			m_ptr = new T[1];
		}

		explicit ptr(const T* ptr)
		{
			m_ptr = new T(*ptr);
		}

		explicit ptr(const T& data)
		{
			m_ptr = new T(data);
		}

		ptr(const ptr& other)
		{
			T* new_ptr = new T(*other.m_ptr);

			m_ptr = new_ptr;
		}

		ptr(ptr&& other) noexcept : m_ptr(other.m_ptr)
		{
			other.m_ptr = nullptr;
		}

		~ptr()
		{
			delete m_ptr;
		}

		explicit operator T*()
		{
			return m_ptr;
		}

		T& operator*()
		{
			return *m_ptr;
		}

		ptr& operator=(const ptr& other)
		{
			if (this == &other)
			{
				return *this;
			}

			delete m_ptr;

			T* new_ptr = new T(*other.m_ptr);

			this->m_ptr = new_ptr;

			return *this;
		}

		ptr& operator=(ptr&& other) noexcept
		{
			if (this == &other)
			{
				return *this;
			}

			this->m_ptr = other.m_ptr;
			other.m_ptr = nullptr;

			return *this;
		}

		// returns constant pointer
		const T* data() const
		{
			return m_ptr;
		}

		// returns mutable pointer
		T* data()
		{
			return m_ptr;
		}

		// returns whether the stored pointer is valid or not
		bool valid() const
		{
			if (m_ptr) return true;
			else
			{
				return false;
			}
		}
	};

	// a weak pointer without automatic cleanup
	// this class assumes that this is not a pointer to the array of some kind
	// for array pointers use utl::array or utl::multi_array
	template <typename T>
	class weak_ptr
	{

		T* m_ptr;

	public:

		weak_ptr()
		{
			m_ptr = new T[1];
		}

		// this actually should not be an explicit constructor, because it is a STL library implementation after all
		explicit weak_ptr(const T* ptr)
		{
			m_ptr = new T(*ptr);
		}

		// a constructor that copies the data on the stack
		weak_ptr(const T& data)
		{
			m_ptr = new T(&data);
		}

		weak_ptr(const weak_ptr& other)
		{
			m_ptr = new T(*other.m_ptr);
		}

		weak_ptr(weak_ptr&& other) noexcept
		{
			m_ptr = other.m_ptr;
			other.m_ptr = nullptr;
		}

		~weak_ptr() = default;

		// conversion operator
		explicit operator T*()
		{
			return m_ptr;
		}

		T& operator*()
		{
			return *m_ptr;
		}

		weak_ptr& operator=(const weak_ptr& other)
		{
			if (this == &other)
			{
				return *this;
			}

			delete m_ptr;

			this->m_ptr = new T(*other.m_ptr);

			return *this;
		}

		weak_ptr& operator=(weak_ptr&& other) noexcept
		{
			if (this == &other)
			{
				return *this;
			}

			delete m_ptr;

			this->m_ptr = other.m_ptr;
			other.m_ptr = nullptr;

			return *this;
		}

		// manual destructor, in case you actually want to destroy your weak pointer
		void destroy()
		{
			delete m_ptr;
			m_ptr = nullptr;
		}

		// returns a constant pointer to the data
		const T* data() const
		{
			return m_ptr;
		}

		// returns a mutable pointer to the data
		T* data()
		{
			return m_ptr;
		}

		// returns whether the data pointer is valid or not
		bool valid() const
		{
			if (m_ptr) return true;
			else
			{
				return false;
			}
		}
	};
}