#ifndef _MDR_VECTOR_H_
#define _MDR_VECTOR_H_

#include "types.h"
#include "iterator.h"

namespace mdr
{
    template<typename T>
    class vector
    {
    public:
	using iterator = mdr::iterator<vector, T>;
	using const_iterator = mdr::iterator<vector const, T const>;
	
	vector() : m_buffer(internal_alloc(m_capacity))
	{
	}

	~vector()
	{
	    internal_dealloc(m_buffer, m_size);
	}

	T& operator[](size_t index) const
	{
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
	    return iterator(*this, 0);
	}

	iterator end()
	{
	    return iterator(*this, m_size - 1);
	}

	const_iterator cbegin() const
	{
	    return const_iterator(*this, 0);
	}

	const_iterator cend() const
	{
	    return const_iterator(*this, m_size - 1);
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
	    if (m_size == m_capacity)
		increase();

	    new (m_buffer + m_size) T(val);
	    ++m_size;
	}
	
	T pop_back()
	{
	    T copy = back();
	    
	    back().~T();
	    m_size--;

	    return copy;
	}
	
    private:
	void increase()
	{
	    auto new_capacity { m_capacity * 2 };
	    auto* new_buffer = internal_alloc(new_capacity);
	    
	    copy_elements(m_buffer, new_buffer);
	    internal_dealloc(m_buffer, m_size);

	    m_buffer = new_buffer;
	    m_capacity = new_capacity;
	}

	T* internal_alloc(const size_t capacity)
	{
	    return static_cast<T*>(::operator new(sizeof(T*) * capacity));
	}

	void internal_dealloc(T* buffer, const size_t size)
	{
	    for (size_t i = 0; i < size; i++)
		buffer[size - 1 - i].~T();

	    ::operator delete(buffer);
	}

	void copy_elements(T* from, T* to)
	{
	    for (size_t i = 0; i < m_size; i++)	    
		to[i] = from[i];
	}

	size_t m_capacity { 10 };
	size_t m_size { 0 };
	
	T* m_buffer { nullptr };
    };
}

#endif
