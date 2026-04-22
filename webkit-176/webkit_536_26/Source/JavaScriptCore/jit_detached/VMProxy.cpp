// Copyright (C) 2012 Sony Computer Entertainment Inc.
// All Rights Reserved.

#include "config.h"

#if ENABLE(JIT) && ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT

#include "JSGlobalData.h"
#include <stdio.h>

namespace JSC {

void releaseExecutableMemory(JSGlobalData&)
{
    fprintf(stderr, "\n----- [not implemented] %s %s,%d -----\n\n", __FUNCTION__, __FILE__, __LINE__);
    __builtin_trap();
}

} // namespace

#endif // #if ENABLE(JIT) && ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT
