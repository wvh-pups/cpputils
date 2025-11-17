#include "memory.hpp"

#include <cstdlib>

using namespace utl;

void* utl::heap(unsigned long long size)
{
	return malloc(size);
}