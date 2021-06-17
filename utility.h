#ifndef _MDR_UTILITY_H_
#define _MDR_UTILITY_H_

#include "types.h"
#include "assert.h"

namespace mdr
{
    template<typename T>
    void copy(const T& from, T& to)
    {
	to = from;
    }

    template<typename T>
    void copy_elements(T* from, T* to, size_t size)
    {
	assert(from != nullptr && to != nullptr);
	
	for (size_t i = 0; i < size; i++)
	    copy(from[i], to[i]);
    }

    template<typename T>
    T&& move(T& t)
    {
	return static_cast<T&&>(t);
    }
}

#endif
