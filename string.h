#ifndef _MDR_STRING_H_
#define _MDR_STRING_H_

#include "types.h"
#include "utility.h"

#include <iostream>

namespace mdr
{
    class string
    {
    public:
        string(const char data[])
	    : m_capacity(determine_size(data))
	    , m_size(m_capacity)
	    , m_buffer(internal_alloc(m_capacity))
	{
	    copy_elements(data, m_buffer, m_size);
	}

	string(const string& rhs)
	    : m_capacity(rhs.m_capacity)
	    , m_size(rhs.m_size)
	    , m_buffer(internal_alloc(rhs.m_capacity))
	{
	    copy_elements(rhs.m_buffer, m_buffer, m_size);
	}

	string(string&& rhs)
	{
	    internal_move(move(rhs));
	}
	
	~string()
	{
	    internal_dealloc();
	}	
	
	string& operator=(const char data[])
	{	    
	    m_size = determine_size(data);
	    m_capacity = m_size;
	    m_buffer = internal_alloc(m_capacity);
	    
	    copy_elements(data, m_buffer, m_size);
	    return *this;
	}

	string& operator=(const string& rhs)
	{
	    m_capacity = rhs.m_capacity;
	    m_size = rhs.m_size;
	    m_buffer = internal_alloc(rhs.m_capacity);

	    copy_elements(rhs.m_buffer, m_buffer, m_size);
	    return *this;
	}

	string& operator=(string&& rhs)
	{
	    internal_move(move(rhs));
	    return *this;
	}

	char& operator[](size_t index) const
	{
	    assert(index >= 0 && index < m_size);
	    return m_buffer[index];
	}

	const char* data() const
	{
	    return m_buffer;
	}
	
    private:
	char* internal_alloc(const size_t capacity)
	{
	    return new char[capacity];
	}

	void internal_dealloc()
	{
	    delete[] m_buffer;
	}

	void internal_move(string&& rhs)
	{
	    if (m_buffer != nullptr)
		internal_dealloc();

	    m_capacity = rhs.m_capacity;
	    m_size = rhs.m_size;
	    m_buffer = rhs.m_buffer;

	    rhs.m_capacity = 0;
	    rhs.m_size = 0;
	    rhs.m_buffer = nullptr;
	}

	size_t determine_size(const char data[])
	{
	    size_t result { 0 };

	    for (; data[result] != '\0'; result++)
	    {
	    }
	    
	    return result;
	}
	
	size_t m_capacity;
	size_t m_size;

	char* m_buffer;	
    };
}

#endif
