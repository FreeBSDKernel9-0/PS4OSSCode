// Copyright (C) 2012 Sony Computer Entertainment Inc.
// All Rights Reserved.

#include "config.h"

#if ENABLE(JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

#include "JIT.h"
#include "Logging.h"

namespace JSC {

void ctiPatchCallByReturnAddress(CodeBlock* codeBlock, ReturnAddressPtr returnAddress, MacroAssemblerCodePtr newCalleeFunction)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(returnAddress.value()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(newCalleeFunction.executableAddress()));

    bridge->requestCompilerTask(JSCBridge::e_ctiPatchCallReturnAddrCodePtr, NULL);
}

void ctiPatchCallByReturnAddress(CodeBlock* codeBlock, ReturnAddressPtr returnAddress, FunctionPtr newCalleeFunction)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(returnAddress.value()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(newCalleeFunction.executableAddress()));

    bridge->requestCompilerTask(JSCBridge::e_ctiPatchCallReturnAddrFunctionPtr, NULL);
}

void ctiPatchNearCallByReturnAddress(CodeBlock* codeBlock, ReturnAddressPtr returnAddress, MacroAssemblerCodePtr newCalleeFunction)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(returnAddress.value()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(newCalleeFunction.executableAddress()));

    bridge->requestCompilerTask(JSCBridge::e_ctiPatchNearCallByReturnAddress, NULL);
}

JITCode JIT::privateCompile(CodePtr* functionEntryArityCheck, JITCompilationEffort effort)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(this));
    payload->sendArgument(reinterpret_cast<uintptr_t>(functionEntryArityCheck));
    payload->sendArgument(static_cast<uintptr_t>(effort));

    CodeBlock::RefundableToll toll(this->obtainToll());
    OwnPtr<JITCode> result(adoptPtr(reinterpret_cast<JITCode *>(bridge->requestCompilerTask(JSCBridge::e_JIT_privateCompile, this))));
    return *result;
}

void JIT::linkFor(JSFunction* callee, CodeBlock* callerCodeBlock, CodeBlock* calleeCodeBlock, JIT::CodePtr code, CallLinkInfo* callLinkInfo, JSGlobalData* globalData, CodeSpecializationKind kind)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const    bridge(JSCBridge::sharedInstance());
    JIT::CodePtr * const sharedCode(new JIT::CodePtr(code));

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(callee));
    payload->sendArgument(reinterpret_cast<uintptr_t>(callerCodeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(calleeCodeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(sharedCode));
    payload->sendArgument(reinterpret_cast<uintptr_t>(callLinkInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(globalData));
    payload->sendArgument(     static_cast<uintptr_t>(kind));

    CodeBlock::RefundableToll calleeToll(calleeCodeBlock ? calleeCodeBlock->obtainToll() : CodeBlock::Toll::s_nullToll);
    CodeBlock::RefundableToll callerToll(callerCodeBlock && (callerCodeBlock != calleeCodeBlock) ? callerCodeBlock->obtainToll() : CodeBlock::Toll::s_nullToll);
    bridge->requestCompilerTask(JSCBridge::e_JIT_linkFor, NULL);

    delete sharedCode;
}

} // namespace JSC

#endif // #if ENABLE(JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT
