// Copyright (C) 2012 Sony Computer Entertainment Inc.
// All Rights Reserved.

#include "config.h"

#if ENABLE(JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

#include "JITStubs.h"
#include "JIT.h"
#include "JSCBridge.h"
#include "Logging.h"
#include <wtf/PassRefPtr.h>

namespace JSC {

PassRefPtr<ExecutableMemoryHandle> JIT::privateCompileCTIMachineTrampolines(JSGlobalData* globalData, TrampolineStructure *trampolines)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(this));
    payload->sendArgument(reinterpret_cast<uintptr_t>(globalData));
    payload->sendArgument(reinterpret_cast<uintptr_t>(trampolines));

    //LOG(DetachedJITProxy, "[requesting compile task] JIT::privateCompileCTIMachineTrampolines\n");
    //LOG(DetachedJITProxy, "\tthis        : %lx\n", reinterpret_cast<uintptr_t>(this));
    //LOG(DetachedJITProxy, "\tglobalData  : %lx\n", reinterpret_cast<uintptr_t>(globalData));
    //LOG(DetachedJITProxy, "\ttrampolines : %lx\n", reinterpret_cast<uintptr_t>(trampolines));
    
    uintptr_t result(bridge->requestCompilerTask(JSCBridge::e_JIT_privateCompileCTIMachineTrampolines, this));

    //LOG(DetachedJITProxy, "\tresult      : %lx\n", result);
    return reinterpret_cast<ExecutableMemoryHandle*>(result);
}

JIT::CodeRef JIT::privateCompileCTINativeCall(JSGlobalData* globalData, NativeFunction func)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(this));
    payload->sendArgument(reinterpret_cast<uintptr_t>(globalData));
    payload->sendArgument(reinterpret_cast<uintptr_t>(func));

    CodeRef * result(reinterpret_cast<CodeRef *>(bridge->requestCompilerTask(JSCBridge::e_JIT_privateCompileCTINativeCall, this)));

    CodeRef retval(*result);
    result->~CodeRef();
    JITSharedDataMemory::shared_free(result);
    return retval;
}

} // namespace JSC

#endif // #if ENABLE(JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT
