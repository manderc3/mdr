#ifndef _MDR_ASSERT_H_
#define _MDR_ASSERT_H_

#ifdef __linux__
#include <stdlib.h>
#include <stdio.h>
#endif

namespace mdr
{
    void assert(bool expr, const char* msg = nullptr)
    {
	if (!expr)
	{
	    if (msg != nullptr)
	    {
#ifdef __linux__
		printf("%s\n", msg);
#endif
	    }
	    
#ifdef __linux__
	    exit(-1);
#endif
	}
    }
}

#endif
