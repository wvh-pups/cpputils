#include <iostream>

#include "utils/vector.hpp"

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

	explicit UtilsTesterResult(const char* name)
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

	return static_cast<int>(result);
}

int main()
{
	std::cout << "Testing c++ utils..." << std::endl;

	run_test(test_vector, "vector");
}