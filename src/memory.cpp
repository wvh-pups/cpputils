#include "utils/memory.hpp"

using namespace utl;

void* utl::heap(unsigned long long size)
{
	return malloc(size);
}

void utl::ufree(void* data)
{
	free(data);
}