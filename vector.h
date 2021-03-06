#ifndef _MDR_VECTOR_H_
#define _MDR_VECTOR_H_

#include "assert.h"
#include "types.h"
#include "utility.h"
#include "iterator.h"
#include "container_common.h"

namespace mdr
{
    template<typename T>
    class vector
    {
    public:
	using iterator = basic_iterator<vector, T>;
	using const_iterator = basic_iterator<const vector, const T>;
	
	vector()
	    : m_buffer(container::alloc<T>(m_capacity))
	{
	}

	template<typename... args>
	vector(args&&... pack)
	    : m_buffer(container::alloc<T>(m_capacity))
	{
	    (void(push_back(pack)), ...);
	}

	vector(const vector<T>& rhs)
	    : m_capacity(rhs.m_capacity)
	    , m_size(rhs.m_size)
	    , m_buffer(container::alloc<T>(rhs.m_capacity))
	{
	    copy_elements(rhs.m_buffer, m_buffer, m_size);
	}

	vector(vector<T>&& rhs)
	{
	    internal_move(move(rhs));
	}
	
	~vector()
	{
	    container::dealloc(m_buffer, m_size);
	}

	vector& operator=(const vector<T>& rhs)
	{
	    m_capacity = rhs.m_capacity;
	    m_size = rhs.m_size;
	    m_buffer = container::alloc<T>(rhs.m_capacity);

	    copy_elements(rhs.m_buffer, m_buffer, m_size);
	    return *this;
	}

	vector& operator=(vector<T>&& rhs)
	{
	    internal_move(move(rhs));
	    return *this;
	}

	T& operator[](size_t index) const
	{
	    assert(index >= 0 && index < m_size);
	    return m_buffer[index];
	}

	T& front() const
	{
	    return m_buffer[0];
	}

	T& back() const
	{
	    return m_buffer[m_size - 1];
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

	const size_t size() const
	{
	    return m_size;
	}

	const size_t capacity() const
	{
	    return m_capacity;
	}

	void push_back(const T& val)
	{
	    if (capacity_exceeded())
		increase_capacity();

	    new (m_buffer + m_size) T(val);
	    ++m_size;
	}
	
	T pop_back()
	{
	    assert(m_size > 0);
	    T copy = back();
	    
	    back().~T();
	    m_size--;

	    return copy;
	}
	
    private:
	const bool capacity_exceeded() const
	{
	    return m_size == m_capacity;
	}
	
	void increase_capacity()
	{
	    auto new_capacity { m_capacity * 2 };
	    auto* new_buffer = container::alloc<T>(new_capacity);
	    
	    copy_elements(m_buffer, new_buffer, m_size);
	    container::dealloc(m_buffer, m_size);

	    m_buffer = new_buffer;
	    m_capacity = new_capacity;
	}

	void internal_move(vector<T>&& rhs)
	{
	    if (m_buffer != nullptr)
		container::dealloc(m_buffer, m_size);

	    m_capacity = rhs.m_capacity;
	    m_size = rhs.m_size;
	    m_buffer = rhs.m_buffer;

	    rhs.m_capacity = 0;
	    rhs.m_size = 0;
	    rhs.m_buffer = nullptr;
	}

	size_t m_capacity { 10 };
	size_t m_size { 0 };
	
	T* m_buffer { nullptr };
    };
}

#endif
