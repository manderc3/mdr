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

	string substr(const size_t pos, const char matcher[]) const
	{
	    return internal_substr(pos, matcher);
	}

	string substr(const size_t pos, const string& matcher) const
	{
	    return internal_substr(pos, matcher.data());
	}
	
    private:
	char* internal_alloc(const size_t capacity)
	{
	    std::cout << "internal_alloc\n";
	    return new char[capacity];
	    std::cout << "leaving internal_alloc\n";
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

	size_t determine_size(const char data[]) const
	{
	    std::cout << "oops\n";
	    size_t result { 0 };

	    for (; data[result] != '\0'; result++)
	    {
	    }

	    std::cout << result << '\n';
	    
	    return result;
	}

	string internal_substr(const size_t index, const char matcher[]) const
	{
	    assert(index >= 0 && index < m_size, "Index provided is not valid");
	    assert(matcher != nullptr, "Matcher is nullptr");

	    const size_t matcher_size = determine_size(matcher);

	    assert(index + matcher_size < m_size, "Matcher size relative to index exceeds the size of the character buffer");

	    for (size_t i = index; i < m_size; i++)
	    {
		size_t matcher_count { 0 };
		for(; m_buffer[i + matcher_count] == matcher[matcher_count] && m_buffer[i + matcher_count] != '\0'; ++matcher_count)
		{
		}

		if (matcher_count == matcher_size)
		{
		    char* foo = new char[matcher_size];
		    copy_element_range(m_buffer, foo, i, matcher_count);

		    return string(foo);
		}
	    }

	    return "";
	}
	
	size_t m_capacity;
	size_t m_size;

	char* m_buffer;	
    };
}

#endif
