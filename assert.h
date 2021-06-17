#ifndef _MDR_ASSERT_H_
#define _MDR_ASSERT_H_

#include <stdlib.h>

namespace mdr
{
    void assert(bool expr)
    {
	if (!expr) { exit(-1); }
    }
}

#endif
