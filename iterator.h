#ifndef _MDR_ITERATOR_H_
#define _MDR_ITERATOR_H_

#include "types.h"

namespace mdr
{
    template<typename container_type, typename value_type>
    class iterator
    {
	using it = iterator<container_type, value_type>;
	
    public:
	friend container_type;

	constexpr it operator+(const it& rhs) const
	{
	    return it(m_container, m_index + rhs.m_index);
	}
	
	constexpr it operator-(const it& rhs) const
	{
	    return it(m_container, m_index - rhs.m_index);
	}

	constexpr it operator++()
	{
	    ++m_index;
	    return *this;
	}
	
	constexpr it operator++(int)
	{
	    ++m_index;
	    return *this;
	}
	
	constexpr it operator--()
	{
	    --m_index;
	    return *this;
	}

	constexpr bool operator==(const it& rhs) const
	{
	    return m_index == rhs.m_index;
	}
	
	constexpr bool operator!=(const it& rhs) const
	{
	    return m_index != rhs.m_index;
	}	

	constexpr value_type& operator*() const
	{
	    return m_container[m_index];
	}

	constexpr value_type* operator->() const
	{
	    return &m_container[m_index];
	}
	
    private:
	constexpr iterator(container_type& container, size_t index)
	    : m_index(index)
	    , m_container(container)

	{
	}

	size_t m_index;
	container_type& m_container;
    };
}

#endif
