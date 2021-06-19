#ifndef _MDR_UTILITY_H_
#define _MDR_UTILITY_H_

#include "types.h"
#include "assert.h"
#include <iostream>

namespace mdr
{
    template<typename T>
    constexpr void copy(const T& from, T& to)
    {
	to = from;
    }

    template<typename T>
    constexpr void copy_elements(const T* from, T* to, size_t size)
    {
	for (size_t i = 0; i < size; i++)
	    copy(from[i], to[i]);
    }

    template<typename T>
    void copy_element_range(const T* from, T* to, size_t begin, size_t size)
    {
	for (size_t i = begin; i < begin + size; i++)
	    copy(from[i], to[i - begin]);
    }

    template<typename T>
    T&& move(T& t)
    {
	return static_cast<T&&>(t);
    }
}

#endif
