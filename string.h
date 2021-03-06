#ifndef _MDR_STRING_H_
#define _MDR_STRING_H_

#include "types.h"
#include "utility.h"
#include "assert.h"
#include "iterator.h"
#include "container_common.h"

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
	    , m_buffer(container::alloc<char>(m_capacity))
	{
	    copy_elements(data, m_buffer, m_size);
	}
	
	string(char* data)
	    : m_capacity(determine_size(data))
	    , m_size(m_capacity)
	    , m_buffer(container::alloc<char>(m_capacity))
	{
	    copy_elements(data, m_buffer, m_size);
	}

	string(const string& rhs)
	    : m_capacity(rhs.m_capacity)
	    , m_size(rhs.m_size)
	    , m_buffer(container::alloc<char>(rhs.m_capacity))
	{
	    copy_elements(rhs.m_buffer, m_buffer, m_size);
	}

	string(string&& rhs)
	{
	    internal_move(move(rhs));
	}
	
	~string()
	{
	    container::dealloc(m_buffer, m_size);
	}	
	
	string& operator=(const char data[])
	{	    
	    m_size = determine_size(data);
	    m_capacity = m_size;
	    m_buffer = container::alloc<char>(m_capacity);
	    
	    copy_elements(data, m_buffer, m_size);
	    return *this;
	}

	string& operator=(const string& rhs)
	{
	    m_capacity = rhs.m_capacity;
	    m_size = rhs.m_size;
	    m_buffer = container::alloc<char>(rhs.m_capacity);

	    copy_elements(rhs.m_buffer, m_buffer, m_size);
	    return *this;
	}

	string& operator=(string&& rhs)
	{
	    internal_move(move(rhs));
	    return *this;
	}

	string& operator+=(const string& rhs)
	{
	    if (m_size == m_capacity)
		m_buffer = container::increase_capacity<char>(m_buffer, m_capacity, m_capacity * 2);
		
	    return *this;
	}

	string operator+(const string& rhs)
	{
	    string new_str("temp");
	    return new_str;
	}

	char& operator[](size_t index) const
	{
	    assert(index >= 0 && index < m_size);
	    return m_buffer[index];
	}

	const bool operator==(const string& rhs) const
	{
	    if (m_size != rhs.m_size)
		return false;

	    for (size_t i = 0; i < m_size; i++)
		if (m_buffer[i] != rhs.m_buffer[i])
		    return false;

	    return true;    
	}
	
	const bool operator!=(const string& rhs) const
	{
	    for (size_t i = 0; i < m_size; i++)
		if (m_buffer[i] != rhs.m_buffer[i])
		    return true;

	    return false;    
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

	string substr(const size_t start, const size_t size) const
	{
	    return internal_substr(start, size);
	}

	const size_t find(const char matcher[], const size_t start = 0) const
	{
	    return internal_find(start, matcher, determine_size(matcher));
	}

	const size_t find(const string& matcher, const size_t start = 0) const
	{
	    return internal_find(start, matcher.data(), matcher.size());
	}

	const void erase(const char matcher[], const size_t start = 0) const
	{
	    internal_erase(start, matcher, determine_size(matcher));
	}

	const void erase(const string& matcher, const size_t start = 0) const
	{
	    internal_erase(start, matcher.data(), matcher.size());
	}

	const size_t size() const
	{
	    return m_size;
	}

	const size_t capacity() const
	{
	    return m_capacity;
	}
	
    private:
	char* internal_alloc(const size_t capacity)
	{
	    return new char[capacity];
	}

	void internal_dealloc()
	{
	    if (m_buffer != nullptr)
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

	string internal_substr(const size_t start, const size_t size) const
	{
	    char* new_buff = new char[size];
	    copy_element_range(m_buffer, new_buff, 0, size);

	    return string(new_buff);
	}

	string internal_substr(const size_t index, const char matcher[], const size_t matcher_size) const
	{
	    assert(index >= 0 && index < m_size, "Index provided is not valid");
	    assert(matcher != nullptr, "Matcher is nullptr");
	    assert(index + matcher_size < m_size, "Matcher size relative to index exceeds the size of the character buffer");

	    if (const size_t pos = internal_find(index, matcher, matcher_size); pos != m_size)
	    {
		char* new_buff = new char[matcher_size];
		copy_element_range(m_buffer, new_buff, pos, matcher_size);

		return string(new_buff);
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

	void internal_erase(const size_t start, const char matcher[], const size_t matcher_sizean) const
	{
	    // TODO
	}
	
	size_t m_capacity;
	size_t m_size;

	char* m_buffer { nullptr };
    };
}

#endif
