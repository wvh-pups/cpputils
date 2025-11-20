#pragma once

/*
 * the default size of the indexable type owner in elements
 */
#define INDEXABLE_DEFAULT_OWNER_SIZE 4096

/*
 * this macro only declares the indexing necessities
 * WARNING:
 * this macro requires #include <unordered_map>
 * the preferred type can be forward-declared,
 * and it is later wrapped in utl::Indexable_
 */
#define INDEXABLE_DECL(type) \
	extern unsigned int type##_index_count; \
	extern utl::Indexable_<type> * type##_index_owner; \
	extern std::unordered_map<const char*, utl::Indexable_<type> * > type##_index_map; \
	void type##_index_add(const utl::Indexable_< type > & object); \
	utl::Indexable_<type> * type##_index_get(const char* id);

/*
 * implements the indexing necessities
 * this should be used in .cpp file, which
 * includes .hpp file where INDEXABLE_DECL was used
 * on the same type
 * Requires Indexable<T> as an input
 *
 * WARNING:
 * this does require #include <unordered_map>
 * and full definition of the T in Indexable<T>
 */
#define INDEXABLE_IMPL(type) \
	unsigned int type##_index_count = 0; \
	bool type##_index_first_time = true; \
	utl::Indexable_<type> * type##_index_owner; \
	std::unordered_map<const char*, utl::Indexable_<type> * > type##_index_map; \
	void type##_index_add(const  utl::Indexable_< type > & object) \
	{ \
		if (type##_index_first_time) \
		{ \
			type##_index_owner = new utl::Indexable_<type> [INDEXABLE_DEFAULT_OWNER_SIZE]; \
			type##_index_first_time = false; \
		} \
		type##_index_owner[type##_index_count] = object; \
		type##_index_map[object.GetID()] = &type##_index_owner[type##_index_count]; \
		type##_index_count++; \
	} \
	utl::Indexable_<type> * type##_index_get(const char* id) \
	{ \
		auto it = type##_index_map.find(id); \
		if (it != type##_index_map.end()) \
		{ \
			return it->second; \
		} \
		else \
		{ \
			return nullptr; \
		} \
	}

namespace utl
{

	/* this value is used when Indexable<T> object
	 * is constructed without ID, if you have an object
	 * you can check whether it is valid by checking
	 * if its id is equal to this value
	 */
	extern const char* INDEXABLE_NULL_ID_VALUE;

	// Indexable_ class, stores preferred type with an id for indexing
	// for use with macros
	template <typename T>
	class Indexable_
	{

		T m_object;
		const char* m_id;

	public:

		Indexable_()
		{
			m_object = T();
			m_id = INDEXABLE_NULL_ID_VALUE;
		}

		Indexable_(const T& object, const char* id)
		{
			m_object = object;
			m_id = id;
		}

		T& GetPtr()
		{
			return m_object;
		}

		const T& GetPtr() const
		{
			return m_object;
		}

		const char* GetID() const
		{
			return m_id;
		}
	};
}