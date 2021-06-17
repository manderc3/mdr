#ifndef _MDR_VECTOR_H
#define _MDR_VECTOR_H

#include <iostream>

namespace MDR
{
    using U32 = unsigned int;
    
    template<typename T>
    class Vector
    {
    public:
	Vector()
	    : m_buffer(static_cast<T*>(::operator new(sizeof(T*) * m_capacity)))
	{
	}

	~Vector()
	{
	    for (U32 i = 0; i < m_size; i++)
		m_buffer[m_size - 1 - i].~T();

	    ::operator delete(m_buffer);
	}

	T& operator[](U32 index) const
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

	const U32 size() const
	{
	    return m_size;
	}

	const U32 capacity() const
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
	    auto* new_buffer = static_cast<T*>(::operator new(sizeof(T*) * m_capacity));
	    
	    copy_elements(m_buffer, new_buffer);

	    for (U32 i = 0; i < m_size; i++)
		m_buffer[m_size - 1 - i].~T();

	    ::operator delete(m_buffer);

	    m_buffer = new_buffer;
	    m_capacity = new_capacity;
	}

	void copy_elements(T* from, T* to)
	{
	    for (U32 i = 0; i < m_size; i++)	    
		to[i] = from[i];
	}

	U32 m_capacity { 10 };
	U32 m_size { 0 };
	
	T* m_buffer { nullptr };
    };
}

#endif
