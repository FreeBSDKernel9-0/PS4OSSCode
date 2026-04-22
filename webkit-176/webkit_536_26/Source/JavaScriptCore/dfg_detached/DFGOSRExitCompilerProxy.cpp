// Copyright (C) 2013 Sony Computer Entertainment Inc.
// All Rights Reserved.

#include "config.h"
#include "DFGOSRExitCompiler.h"

#include "jit_detached/JSCBridge.h"

#if ENABLE(DFG_JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

namespace JSC {
namespace DFG {

void DFG_OPERATION compileOSRExit_vmstub(ExecState* exec)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(exec));
    bridge->requestCompilerTask(JSCBridge::e_DFG_compileOSRExit, NULL);
    return;
}

} // namespace DFG
} // namespace JSC

#endif // #if ENABLE(DFG_JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

