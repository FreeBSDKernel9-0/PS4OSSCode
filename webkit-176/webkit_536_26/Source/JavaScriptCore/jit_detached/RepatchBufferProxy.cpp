// Copyright (C) 2012 Sony Computer Entertainment Inc.
// All Rights Reserved.

#include "config.h"

#if ENABLE(JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

#include "AbstractMacroAssembler.h"
#include "CodeLocation.h"
#include "JSCBridge.h"
#include "RepatchBuffer.h"

namespace JSC {

void RepatchBuffer::relink(CodeLocationCall call, FunctionPtr destination)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());
    JSCBridge::Payload * const payload(bridge->payload());

    payload->sendArgument(reinterpret_cast<uintptr_t>(call.executableAddress()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(destination.executableAddress()));

    bridge->requestCompilerTask(JSCBridge::e_RepatchBuffer_relinkCallToFuncPtr, NULL);
}

void RepatchBuffer::relink(CodeLocationNearCall nearCall, CodePtr destination)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());
    JSCBridge::Payload * const payload(bridge->payload());

    payload->sendArgument(reinterpret_cast<uintptr_t>(nearCall.executableAddress()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(destination.executableAddress()));

    bridge->requestCompilerTask(JSCBridge::e_RepatchBuffer_relinkNearCallToCodePtr, NULL);
}

void RepatchBuffer::relink(CodeLocationJump jump, CodeLocationLabel destination)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());
    JSCBridge::Payload * const payload(bridge->payload());

    payload->sendArgument(reinterpret_cast<uintptr_t>(jump.executableAddress()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(destination.executableAddress()));

    bridge->requestCompilerTask(JSCBridge::e_RepatchBuffer_relinkJumpToLabel, NULL);
}

void RepatchBuffer::repatch(CodeLocationDataLabelPtr dataLabelPtr, void* value)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());
    JSCBridge::Payload * const payload(bridge->payload());

    payload->sendArgument(reinterpret_cast<uintptr_t>(dataLabelPtr.executableAddress()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(value));

    bridge->requestCompilerTask(JSCBridge::e_RepatchBuffer_repatchLabelToVoidPtr, NULL);
}

void RepatchBuffer::repatch(CodeLocationDataLabelCompact dataLabelCompact, int32_t value)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());
    JSCBridge::Payload * const payload(bridge->payload());

    payload->sendArgument(reinterpret_cast<uintptr_t>(dataLabelCompact.executableAddress()));
    payload->sendArgument(     static_cast<uintptr_t>(value));

    bridge->requestCompilerTask(JSCBridge::e_RepatchBuffer_repatchLabelCompactToInt, NULL);
}

void RepatchBuffer::repatch(CodeLocationDataLabel32 dataLabel32, int32_t value)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());
    JSCBridge::Payload * const payload(bridge->payload());

    payload->sendArgument(reinterpret_cast<uintptr_t>(dataLabel32.executableAddress()));
    payload->sendArgument(     static_cast<uintptr_t>(value));

    bridge->requestCompilerTask(JSCBridge::e_RepatchBuffer_repatchLabel32ToInt, NULL);
}

} // namespace JSC

#endif // #if ENABLE(JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT
