#include <iostream>

#include <chrono>
#include <thread>

#include <unordered_map>

#include "utils/memory.hpp"
#include "utils/vector.hpp"
#include "utils/string.hpp"
#include "utils/array.hpp"
#include "utils/logger.hpp"
#include "utils/index.hpp"

INDEXABLE_DECL(int)
INDEXABLE_IMPL(int)

// declares a new test
#define DECLARE_TEST(name) int test_ ## name() \
	{ \
	UtilsTesterResult result(#name);

// could have went with the implicit int converter, but whatever
// use this at the end of the test
#define END_TEST(object) return static_cast<int>(object); \
	}

// adds a test to run
// use this in the main function
#define ADD_TEST(name) run_test(test_ ## name, #name)

// prints something using the iostream
#define PRINT(str) std::cout << str << std::endl

// waits for specified amount of time
#define WAIT(time) std::this_thread::sleep_for(std::chrono::seconds(time));

unsigned int test_count = 1;

typedef int (*test_t)();

void test_failed(const char* name)
{
	std::cout << "Test " << test_count << ": " << name  << " FAILED" << std::endl;

	test_count++;
}

void test_passed(const char* name)
{
	std::cout << "Test " << test_count << ": " << name << " PASSED" << std::endl;

	test_count++;
}

void run_test(test_t test, const char* id)
{
	int result = test();

	if (result)
	{
		test_passed(id);
	}
	else
	{
		test_failed(id);
	}
}

struct UtilsTesterResult
{
	int result;
	const char* test_name;

	UtilsTesterResult()
	{
		result = 0;
		test_name = "NULL";
	}

	UtilsTesterResult(const char* name)
	{
		test_name = name;
		result = 0;
	}

	explicit operator int() const
	{
		return result;
	}

	UtilsTesterResult& operator=(const int new_result)
	{
		if (new_result != 1)
		{
			test_failed(test_name);

			exit(0);
		}

		this->result = new_result;

		return *this;
	}
};

int test_vector()
{
	utl::vector<int> vector = utl::vector<int>();

	vector.push_back(35);
	vector.push_back(25);

	UtilsTesterResult result("vector");

	int i = 0;
	for (const int element : vector)
	{
		if (i == 0)
		{
			result = element == 35;
		}

		if (i == 1)
		{
			result = element == 25;
		}

		i++;
	}

	vector.pop_back();

	result = vector[0] == 35;

	vector.clear();

	for (const auto element: vector)
	{
		result = 0;
	}

	vector.push_back(55);
	vector.push_back(65);
	vector.push_back(75);

	vector.erase(1);

	i = 0;

	for (const auto element : vector)
	{
		if (i == 0)
		{
			result = element == 55;
		}

		if (i == 1)
		{
			result = element == 75;
		}

		i++;
	}

	END_TEST(result)

DECLARE_TEST(string)

	utl::string string = "Hello, World! %d";

	if (string == "Hello, World! %d")
	{
		result = 1;
	}

	std::cout << "TEST string: " << string << " LENGTH: " << string.length() << std::endl;

	utl::string string2 = utl::string::strfmt(string, 45);

	if (string2 == "Hello, World! 45")
	{
		result = 1;
	}

	std::cout << "TEST string2: " << string2 << " LENGTH: " << string.length() << std::endl;

END_TEST(result)

int test_memory()
{
	void* memory = utl::heap(sizeof(int) * 5);

	UtilsTesterResult result("memory");

	utl::ufree(memory);

	utl::weak_ptr<int> weak_ptr(new int(45));

	if (weak_ptr.valid())
	{
		result = 1;
	}
	else
	{
		result = 0;
	}

	std::cout << "TEST weak_ptr value: " << *weak_ptr << std::endl;

	weak_ptr.destroy();

	utl::ptr<float> ptr(new float(3.5f));

	std::cout << "TEST ptr value: " << *ptr << std::endl;

	if (ptr.valid())
	{
		result = 1;
	}
	else
	{
		result = 0;
	}

END_TEST(result)

DECLARE_TEST(array)

	const int debug_array[5] = { 25, 35, 0, 50, 15 };

	utl::array<int, 5> test_array;

	test_array[0] = 25;
	test_array[1] = 35;
	test_array[2] = 0;
	test_array[3] = 50;
	test_array[4] = 15;

	std::cout << "TEST array contents: ";

	int i = 0;
	for (const auto& element : test_array)
	{
		std::cout << element << " ";

		if (element != debug_array[i])
		{
			result = 0;
		}
		else
		{
			result = 1;
		}

		i++;
	}

	utl::array_2d<float, 3, 3> two_dimensional_array;

	two_dimensional_array[2][1] = 5.0f;

	if (two_dimensional_array[2][1] != 5.0f)
	{
		result = 0;
	}

	std::cout << std::endl;
END_TEST(result)

DECLARE_TEST(logger)

	PRINT("testing da logging functions");

	utl::log("information", utl::Info);
	WAIT(1);
	utl::log("warning", utl::Warn);
	WAIT(1);
	utl::log("error", utl::Error);
	WAIT(1);
	utl::log("debug", utl::Debug);
	WAIT(1);
	utl::log("this is a very long string for testing, please be careful", utl::Debug);

	result = 1;

END_TEST(result)

DECLARE_TEST(index)

	int test_number = 25;
	int_index_add(utl::Indexable_<int>(25, "test"));

	auto* test_ptr = int_index_get("test");

	if (test_ptr->GetPtr() != 25)
	{
		result = 0;
	}
	else
	{
		result = 1;
	}

END_TEST(result)

int main()
{
	PRINT("Testing c++ utils...");

	ADD_TEST(vector);
	ADD_TEST(string);
	ADD_TEST(memory);
	ADD_TEST(array);
	ADD_TEST(index);
	ADD_TEST(logger);
}