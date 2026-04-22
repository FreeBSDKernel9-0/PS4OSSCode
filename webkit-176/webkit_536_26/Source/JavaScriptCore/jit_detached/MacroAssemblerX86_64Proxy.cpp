// Copyright (C) 2012 Sony Computer Entertainment Inc.
// All Rights Reserved.

#include "config.h"

#if ENABLE(JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

#include "AssemblerBuffer.h"
#include "MacroAssembler.h"

namespace JSC {

void MacroAssemblerX86_64::repatchCall(CodeLocationCall call, FunctionPtr destination)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(call.executableAddress()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(destination.executableAddress()));
    bridge->requestCompilerTask(JSCBridge::e_MacroAssembler_repatchCall, NULL);
}

} // namespace JSC

#endif // #if ENABLE(JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT
