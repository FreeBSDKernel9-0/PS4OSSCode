// Copyright (C) 2012 Sony Computer Entertainment Inc.
// All Rights Reserved.

#include "config.h"

#if ENABLE(JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

#include "AbstractMacroAssembler.h"
#include "AssemblerBuffer.h"
#include "JSCBridge.h"
#include "MacroAssembler.h"

namespace JSC {

template <>
void AbstractMacroAssembler<X86Assembler>::repatchJump(CodeLocationJump jump, CodeLocationLabel destination)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(jump.executableAddress()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(destination.executableAddress()));

    bridge->requestCompilerTask(JSCBridge::e_MacroAssembler_repatchJump, NULL);
}

template <>
void AbstractMacroAssembler<X86Assembler>::repatchNearCall(CodeLocationNearCall nearCall, CodeLocationLabel destination)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(nearCall.executableAddress()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(destination.executableAddress()));

    bridge->requestCompilerTask(JSCBridge::e_MacroAssembler_repatchNearCall, NULL);
}

template <>
void AbstractMacroAssembler<X86Assembler>::repatchPointer(CodeLocationDataLabelPtr dataLabelPtr, void* value)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(dataLabelPtr.executableAddress()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(value));

    bridge->requestCompilerTask(JSCBridge::e_MacroAssembler_repatchPointer, NULL);
}

} // namespace JSC

#endif // #if ENABLE(JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT
