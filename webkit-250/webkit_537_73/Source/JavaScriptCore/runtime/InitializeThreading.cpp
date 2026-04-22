/*
 * Copyright (C) 2008 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer. 
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution. 
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "InitializeThreading.h"

#include "ExecutableAllocator.h"
#include "Heap.h"
#include "HeapStatistics.h"
#include "Options.h"
#include "Identifier.h"
#include "JSDateMath.h"
#include "JSGlobalObject.h"
#include "JSLock.h"
#include "LLIntData.h"
#include "WriteBarrier.h"
#include <wtf/dtoa.h>
#include <wtf/Threading.h>
#include <wtf/dtoa/cached-powers.h>

#if OS(ORBIS)
#include <x86intrin.h>
#endif

using namespace WTF;

namespace JSC {

#if OS(DARWIN)
static pthread_once_t initializeThreadingKeyOnce = PTHREAD_ONCE_INIT;
#endif

static void initializeThreadingOnce()
{
#if OS(ORBIS)
    _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_OFF);
#endif

#if OS(PSP2)
    // disable Flush-to-Zero
    unsigned int const flushToZeroMask = 0x01000000U;
    unsigned int const fpscr = __builtin_mrc(10, 7, 1, 0, 0);
	__builtin_mcr(10, 7, 1, 0, 0, fpscr & ~flushToZeroMask);
#endif

#if ENABLE(JIT) && ENABLE(DETACHED_JIT)
#if !BUILDING_DETACHED_JIT
    char const * jscoreVMProcessValue(getenv("JSCORE_VM_PROCESS"));
    bool         isCurrentProcessVM(jscoreVMProcessValue && (strcmp(jscoreVMProcessValue, "1") == 0));
    if (isCurrentProcessVM) {
        char * args[1] = { 0 };
        char const * compilerPath(getenv("JSCORE_JIT_COMPILER_FILE"));
        JSCBridge::sharedInstance()->initializeFromVM(compilerPath, args);
    }
#endif
#endif

    WTF::double_conversion::initialize();
    WTF::initializeThreading();
#if !(ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT)
    GlobalJSLock::initialize();
#endif
    Options::initialize();

#if !(ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT)
    if (Options::recordGCPauseTimes())
        HeapStatistics::initialize();
#if ENABLE(WRITE_BARRIER_PROFILING)
    WriteBarrierCounters::initialize();
#endif
#endif // #if !(ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT)

#if ENABLE(ASSEMBLER) && !ENABLE(DETACHED_JIT)
    ExecutableAllocator::initializeAllocator();
#endif

#if !BUILDING_DETACHED_JIT
    JSStack::initializeThreading();

#if ENABLE(LLINT)
    LLInt::initialize();
#endif

#endif // !BUILDING_DETACHED_JIT
}

void initializeThreading()
{
#if OS(DARWIN)
    pthread_once(&initializeThreadingKeyOnce, initializeThreadingOnce);
#else
    static bool initializedThreading = false;
    if (!initializedThreading) {
        initializeThreadingOnce();
        initializedThreading = true;
    }
#endif
}

} // namespace JSC
