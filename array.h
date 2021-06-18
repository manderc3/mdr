#ifndef _MDR_ARRAY_H_
#define _MDR_ARRAY_H_

#include "types.h"
#include "iterator"

namespace mdr
{
    template<typename T, size_t arr_size>
    class array
    {
	using iterator = basic_iterator<array, T>;
	using const_iterator = basic_iterator<const array, const T>;
	
    public:
	template<typename... args>
	constexpr array(args&&... pack)
	{
	    static_assert(sizeof...(pack) <= arr_size, "too many arguments");
	    size_t i = 0;
	    (void(m_data[i++] = pack), ...);
	}

	constexpr T& operator[](const size_t index)
	{
	    return m_data[index];
	}

	constexpr T& front() const
	{
	    return m_data[0];
	}

	constexpr T& back() const
	{
	    return m_data[arr_size - 1];
	}

	constexpr iterator begin()
	{
	    return { *this, 0 };
	}

	constexpr iterator end()
	{
	    return { *this, arr_size };
	}

	constexpr const_iterator cbegin() const
	{
	    return { *this, 0 };
	}

	constexpr const_iterator cend() const
	{
	    return { *this, arr_size };
	}

	constexpr const size_t size() const
	{
	    return arr_size;
	}
	
    private:
	T m_data[arr_size];
    };
}

#endif
