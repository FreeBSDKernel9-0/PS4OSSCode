// Copyright (C) 2013 Sony Computer Entertainment Inc.
// All Rights Reserved.

#include "config.h"
#include "DFGJITCompiler.h"

#include "jit_detached/JSCBridge.h"
#include "WTF/OwnPtr.h"

#if ENABLE(DFG_JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

namespace JSC {
namespace DFG {

bool JITCompiler::compile(JITCode& entry)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(this));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&entry));

    uintptr_t result(bridge->requestCompilerTask(JSCBridge::e_DFG_compile, NULL));
    return static_cast<bool>(result);
}

bool JITCompiler::compileFunction(JITCode& entry, MacroAssemblerCodePtr& entryWithArityCheck)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(this));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&entry));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&entryWithArityCheck));

    uintptr_t result(bridge->requestCompilerTask(JSCBridge::e_DFG_compileFunction, NULL));
    return static_cast<bool>(result);
}

} // namespace DFG
} // namespace JSC

#endif // #if ENABLE(DFG_JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT
