#ifndef _MDR_STRING_H_
#define _MDR_STRING_H_

#include "types.h"
#include "utility.h"
#include "assert.h"
#include "iterator.h"

#include <iostream>

namespace mdr
{
    class string
    {
    public:
	using iterator = basic_iterator<string, char>;
	using const_iterator = basic_iterator<const string, const char>;

        string(const char data[])
	    : m_capacity(determine_size(data))
	    , m_size(m_capacity)
	    , m_buffer(internal_alloc(m_capacity))
	{
	    copy_elements(data, m_buffer, m_size);
	}

	string(char* data)
	    : m_capacity(determine_size(data))
	    , m_size(m_capacity)
	    , m_buffer(data)
	{
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

	iterator begin()
	{
	    return { *this, 0 };
	}

	iterator end()
	{
	    return { *this, m_size };
	}

	const_iterator cbegin() const
	{
	    return { *this, 0 };
	}

	const_iterator cend() const
	{
	    return { *this, m_size };
	}

	const char* data() const
	{
	    return m_buffer;
	}

	string substr(const char matcher[], const size_t start = 0) const
	{
	    return internal_substr(start, matcher, determine_size(matcher));
	}

	string substr(const string& matcher, const size_t start = 0) const
	{
	    return internal_substr(start, matcher.data(), matcher.size());
	}

	const size_t find(const char matcher[], const size_t start = 0) const
	{
	    return internal_find(start, matcher, determine_size(matcher));
	}

	const size_t find(const string& matcher, const size_t start = 0) const
	{
	    return internal_find(start, matcher.data(), matcher.size());
	}

	const size_t size() const
	{
	    return m_size;
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

	const size_t determine_size(const char data[]) const
	{
	    size_t result { 0 };

	    for (; data[result] != '\0'; result++)
	    {
	    }

	    return result;
	}

	string internal_substr(const size_t index, const char matcher[], const size_t matcher_size) const
	{
	    assert(index >= 0 && index < m_size, "Index provided is not valid");
	    assert(matcher != nullptr, "Matcher is nullptr");
	    assert(index + matcher_size < m_size, "Matcher size relative to index exceeds the size of the character buffer");

	    if (const size_t pos = internal_find(index, matcher, matcher_size); pos != m_size)
	    {
		char* foo = new char[matcher_size];
		copy_element_range(m_buffer, foo, pos, matcher_size);

		return string(foo);
	    }
	
	    return "";
	}

	const size_t internal_find(const size_t start, const char matcher[], const size_t matcher_size) const
	{
	    assert(start >= 0 && start < m_size, "Start provided is not valid");
	    assert(matcher != nullptr, "Matcher is nullptr");
	    assert(start + matcher_size < m_size, "Matcher size relative to start exceeds the size of the character buffer");

	    for (size_t index = start; index < m_size; index++)
	    {
		size_t matcher_count { 0 };
		for(; m_buffer[index + matcher_count] == matcher[matcher_count] && m_buffer[index + matcher_count] != '\0'; ++matcher_count)
		{
		}

		if (matcher_count == matcher_size)
		{
		    return index;
		}
	    }
	    
	    return m_size;
	}
	
	size_t m_capacity;
	size_t m_size;

	char* m_buffer;	
    };
}

#endif
