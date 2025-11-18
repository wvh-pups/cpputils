#include <iostream>

#include "utils/memory.hpp"
#include "utils/vector.hpp"
#include "utils/string.hpp"
#include "utils/array.hpp"

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

	END_TEST(result)

int test_string()
{
	UtilsTesterResult result("string");

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
	int debug_array[5] = { 25, 35, 0, 50, 15 };

	utl::array<int, 5> array();

	array[0] = 25;
	array[1] = 35;
	array[2] = 0;
	array[3] = 50;
	array[4] = 15;

	std::cout << "TEST array contents: ";

	int i = 0;
	for (const auto& element : array)
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

	std::cout << std::endl;
END_TEST(result)

int main()
{
	PRINT("Testing c++ utils...");

	ADD_TEST(vector);
	ADD_TEST(string);
	ADD_TEST(memory);
	ADD_TEST(array);
}