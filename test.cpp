#include <iostream>

#include "utils/shared.hpp"

unsigned int test_count = 1;

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

int main()
{
	std::cout << "Testing c++ utils..." << std::endl;

	std::cout << test_function() << std::endl;
}