#include <iostream>

#include "utils/shared.hpp"
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

int test_vector()
{
	utl::vector<int> vector = utl::vector<int>();

	vector.push_back(35);
	vector.push_back(25);

	int result = 0;

	int i = 0;
	for (int element : vector)
	{
		if (i == 0)
		{
			result = element == 35;

			if (result == 0)
			{
				return result;
			}
		}

		if (i == 1)
		{
			result = element == 25;

			if (result == 0)
			{
				return result;
			}
		}

		i++;
	}

	return result;
}

int main()
{
	std::cout << "Testing c++ utils..." << std::endl;

	run_test(test_vector, "vector");
}