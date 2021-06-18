#ifndef _MDR_PRINT_H_
#define _MDR_PRINT_H_

#ifdef __linux__
#include <stdio.h>
#endif

#include "types.h"
#include "string.h"

namespace mdr
{
    void print(const string& val)
    {
	auto* data = val.data();
	
#ifdef __linux__
	printf("%s", data);
#endif
    }

    void print(const char val)
    {
#ifdef __linux__
	printf("%d", val);
#endif
    }
    
    void print(const int val)
    {
#ifdef __linux__
	printf("%d", val);
#endif
    }
    
    void print(const size_t val)
    {
#ifdef __linux__
	printf("%lld", val);
#endif
    }
}

#endif
