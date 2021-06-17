#ifndef _MDR_UTILITY_H_
#define _MDR_UTILITY_H_

#include "types.h"
#include "assert.h"

namespace mdr
{
    template<typename T>
    void copy(T* from, T* to)
    {
	assert(from != nullptr && to != nullptr);
	
	for (size_t i = 0; i < size; i++)
	    to[i] = from[i];
    }

    template<typename T>
    void copy_elements(T* from, T* to, size_t size)
    {
	assert(from != nullptr && to != nullptr);
	
	for (size_t i = 0; i < size; i++)
	    copy(from[i], to[i]);
    }
}

#endif
