// Copyright (C) 2012 Sony Interactive Entertainment Inc.
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

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(call.executableAddress()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(destination.executableAddress()));

    bridge->requestCompilerTask(JSCBridge::e_MacroAssembler_repatchCallFunctionPtr);
}

void MacroAssemblerX86Common::repatchCompact(CodeLocationDataLabelCompact dataLabelCompact, int32_t value)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(dataLabelCompact.executableAddress()));
    payload->sendArgument(     static_cast<uintptr_t>(value));

    bridge->requestCompilerTask(JSCBridge::e_MacroAssembler_repatchCompact);
}

template<>
void JSC::AbstractMacroAssembler<JSC::X86Assembler>::repatchInt32(CodeLocationDataLabel32 dataLabel32, int32_t value)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(dataLabel32.executableAddress()));
    payload->sendArgument(     static_cast<uintptr_t>(value));

    bridge->requestCompilerTask(JSCBridge::e_MacroAssembler_repatchInt32);
}

template<>
void JSC::AbstractMacroAssembler<JSC::X86Assembler>::repatchJump(CodeLocationJump jump, CodeLocationLabel destination)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(jump.executableAddress()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(destination.executableAddress()));

    bridge->requestCompilerTask(JSCBridge::e_MacroAssembler_repatchJump);
}

template<>
void JSC::AbstractMacroAssembler<JSC::X86Assembler>::repatchNearCall(CodeLocationNearCall nearCall, CodeLocationLabel destination)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(nearCall.executableAddress()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(destination.executableAddress()));

    bridge->requestCompilerTask(JSCBridge::e_MacroAssembler_repatchNearCall);
}

template<>
void JSC::AbstractMacroAssembler<JSC::X86Assembler>::repatchPointer(CodeLocationDataLabelPtr dataLabelPtr, void* value)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(dataLabelPtr.executableAddress()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(value));

    bridge->requestCompilerTask(JSCBridge::e_MacroAssembler_repatchPointer);
}

template<>
void JSC::AbstractMacroAssembler<JSC::X86Assembler>::replaceWithAddressComputation(CodeLocationConvertibleLoad label)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(label.executableAddress()));

    bridge->requestCompilerTask(JSCBridge::e_MacroAssembler_replaceWithAddressComputation);
}

void MacroAssemblerX86Common::replaceWithJump(CodeLocationLabel instructionStart, CodeLocationLabel to)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(instructionStart.executableAddress()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(to.executableAddress()));
    
    bridge->requestCompilerTask(JSCBridge::e_MacroAssembler_replaceWithJump);
}

void MacroAssemblerX86_64::revertJumpReplacementToBranchPtrWithPatch(CodeLocationLabel instructionStart, MacroAssembler::RegisterID reg, void* value)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(instructionStart.executableAddress()));
    payload->sendArgument(     static_cast<uintptr_t>(reg));
    payload->sendArgument(reinterpret_cast<uintptr_t>(value));

    bridge->requestCompilerTask(JSCBridge::e_MacroAssembler_revertJumpReplacementToBranch);
}

void MacroAssemblerX86_64::revertJumpReplacementToPatchableBranchPtrWithPatch(CodeLocationLabel instructionStart, MacroAssembler::Address address, void* initialValue)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(instructionStart.executableAddress()));
    payload->sendPOD(&address);
    payload->sendArgument(reinterpret_cast<uintptr_t>(initialValue));

    bridge->requestCompilerTask(JSCBridge::e_MacroAssembler_revertJumpReplacementToPatchableBranch);
}

} // namespace JSC

#endif // #if ENABLE(JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT
