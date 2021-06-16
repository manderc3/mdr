#ifndef _MDR_VECTOR_H
#define _MDR_VECTOR_H

namespace MDR
{
    using U32 = unsigned int;
    
    template<typename T>
    class Vector
    {
    public:
	Vector()
	{
	    m_data = new T[m_capacity];
	}

	T& operator[](U32 index) const
	{
	    return m_data[index];
	}

	T& front() const
	{
	    return m_data[0];
	}

	T& back() const
	{
	    return m_data[m_size - 1];
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
	    if (m_size >= m_capacity)
		increase();

	    m_data[m_size++] = val;	    
	}
	
	void pop_back()
	{
	    back().~T();

	    m_size--;
	}
	
    private:
	void increase()
	{
	    auto new_capacity { m_capacity * 2 };
	    auto* new_data = new T[new_capacity];

	    delete[] m_data;
	    m_data = new_data;
	    m_capacity = new_capacity;
	}

	void copy_elements(T* to, T* from)
	{
	    for (U32 i = 0; i < m_size; i++)	    
		to[i] = from[i];
	}
	
	T* m_data { nullptr } ;
	U32 m_capacity { 10 };
	U32 m_size { 0 };
    };
}

#endif
