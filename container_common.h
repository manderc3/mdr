#ifndef _MDR_CONTAINER_COMMON_H_
#define _MDR_CONTAINER_COMMON_H_

#include "utility.h"

namespace mdr
{
    namespace container
    {
	template<typename T>
	T* alloc(const size_t capacity)
	{
	    return static_cast<T*>(::operator new(sizeof(T*) * capacity));
	}

	template<typename T>
	void dealloc(T buffer[], const size_t size)
	{
	    for (size_t i = 0; i < size; i++)
		buffer[size - 1 - i].~T();

	    ::operator delete(buffer);
	}
	
	template<typename T>
	T* increase_capacity(T buffer[], size_t buffer_size, size_t new_capacity)
	{
	    auto* new_buffer = alloc<T>(new_capacity);
	    
	    copy_elements(buffer, new_buffer, buffer_size);
	    dealloc(buffer, buffer_size);

	    return new_buffer;
	}
    }
}

#endif
