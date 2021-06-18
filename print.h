#ifndef _MDR_PRINT_H_
#define _MDR_PRINT_H_

#ifdef __linux__
#include <stdio.h>
#endif

#include "string.h"

namespace mdr
{
    void print(const string& str)
    {
	auto* data = str.data();
	
	#ifdef __linux__
	printf("%s", data);
	#endif
    }
}

#endif
