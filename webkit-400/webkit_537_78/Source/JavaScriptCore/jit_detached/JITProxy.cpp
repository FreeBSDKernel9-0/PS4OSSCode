// Copyright (C) 2012 Sony Interactive Entertainment Inc.
// All Rights Reserved.

#include "config.h"

#if ENABLE(JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

#include "JIT.h"
#include "JSCBridge.h"
#include "JSCBridgeToll.h"

#include <wtf/OwnPtr.h>

namespace JSC {

void ctiPatchCallByReturnAddress(CodeBlock* codeBlock, ReturnAddressPtr returnAddress, MacroAssemblerCodePtr newCalleeFunction)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(returnAddress.value()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(newCalleeFunction.executableAddress()));

    bridge->requestCompilerTask(JSCBridge::e_ctiPatchCallReturnAddrCodePtr);
}

void ctiPatchCallByReturnAddress(CodeBlock* codeBlock, ReturnAddressPtr returnAddress, FunctionPtr newCalleeFunction)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(returnAddress.value()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(newCalleeFunction.executableAddress()));

    bridge->requestCompilerTask(JSCBridge::e_ctiPatchCallReturnAddrFunctionPtr);
}

JITCode JIT::compile(VM* vm, CodeBlock* codeBlock, JITCompilationEffort effort, CodePtr* functionEntryArityCheck)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    CodePtr * sharedFunctionArityCheck(functionEntryArityCheck ? sharedNew<CodePtr>(*functionEntryArityCheck) : NULL);

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(vm));
    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(static_cast     <uintptr_t>(effort));
    payload->sendArgument(reinterpret_cast<uintptr_t>(sharedFunctionArityCheck));

    OwnPtr<JSCBridgeToll> toll(adoptPtr(bridge->createToll(payload.get())));
    toll->prepare(vm);
    toll->prepare(codeBlock);

    JITCode * sharedCode(reinterpret_cast<JITCode *>(bridge->requestCompilerTask(JSCBridge::e_JIT_compile)));
    JITCode result(*sharedCode);
    sharedDelete<JITCode>(sharedCode);

    if (functionEntryArityCheck) {
        *functionEntryArityCheck = *sharedFunctionArityCheck;
        sharedDelete<CodePtr>(sharedFunctionArityCheck);
    }

    return result;
}

void JIT::compileClosureCall(VM* vm, CallLinkInfo* callLinkInfo, CodeBlock* callerCodeBlock, CodeBlock* calleeCodeBlock, Structure* expectedStructure, ExecutableBase* expectedExecutable, MacroAssemblerCodePtr codePtr)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());
    MacroAssemblerCodePtr * const sharedCode(sharedNew<MacroAssemblerCodePtr>(codePtr));

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(vm));
    payload->sendArgument(reinterpret_cast<uintptr_t>(callLinkInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(callerCodeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(calleeCodeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(expectedStructure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(expectedExecutable));
    payload->sendArgument(reinterpret_cast<uintptr_t>(sharedCode));

    bridge->requestCompilerTask(JSCBridge::e_JIT_compileClosureCall);

    sharedDelete<MacroAssemblerCodePtr>(sharedCode);
}

JIT::CodeRef JIT::compileCTINativeCall(VM* vm, NativeFunction func)
{
    if (!vm->canUseJIT()) {
#if ENABLE(LLINT)
        return CodeRef::createLLIntCodeRef(llint_native_call_trampoline);
#else
        return CodeRef();
#endif
    }

    {
        PROFILE_FUNCTION_CALL;

        JSCBridge * const bridge(JSCBridge::sharedInstance());

        OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
        payload->sendArgument(reinterpret_cast<uintptr_t>(vm));
        payload->sendArgument(reinterpret_cast<uintptr_t>(func));

        MacroAssemblerCodeRef * sharedCodeRef(reinterpret_cast<MacroAssemblerCodeRef *>(bridge->requestCompilerTask(JSCBridge::e_JIT_compileCTINativeCall)));
        MacroAssemblerCodeRef codeRef(*sharedCodeRef);
        sharedDelete<MacroAssemblerCodeRef>(sharedCodeRef);
        return codeRef;
    }
}

void JIT::compileGetByIdChain(VM* vm, CallFrame* callFrame, CodeBlock* codeBlock, StructureStubInfo* stubInfo, Structure* structure, StructureChain* chain, size_t count, const Identifier& ident, const PropertySlot& slot, PropertyOffset cachedOffset, ReturnAddressPtr returnAddress)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(vm));
    payload->sendArgument(reinterpret_cast<uintptr_t>(callFrame));
    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(stubInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(chain));
    payload->sendArgument(     static_cast<uintptr_t>(count));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&ident)); // ident is only used as a TrustedImmPtr so it's ok for it to be not shared allocated
    payload->sendPOD(&slot); // slot is a const so it's safe to assume slot will not be modifed so no need to expect a return value from the compiler
    payload->sendArgument(     static_cast<uintptr_t>(cachedOffset));
    payload->sendArgument(reinterpret_cast<uintptr_t>(returnAddress.value()));

    bridge->requestCompilerTask(JSCBridge::e_JIT_compileGetByIdChain);
}

void JIT::compileGetByIdChainList(VM* vm, CallFrame* callFrame, CodeBlock* codeBlock, StructureStubInfo* stubInfo, PolymorphicAccessStructureList* prototypeStructureList, int currentIndex, Structure* structure, StructureChain* chain, size_t count, const Identifier& ident, const PropertySlot& slot, PropertyOffset cachedOffset)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(vm));
    payload->sendArgument(reinterpret_cast<uintptr_t>(callFrame));
    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(stubInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(prototypeStructureList));
    payload->sendArgument(     static_cast<uintptr_t>(currentIndex));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(chain));
    payload->sendArgument(     static_cast<uintptr_t>(count));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&ident)); // ident is only used as a TrustedImmPtr so it's ok for it to be not shared allocated
    payload->sendPOD(&slot); // slot is a const so it's safe to assume slot will not be modifed so no need to expect a return value from the compiler
    payload->sendArgument(     static_cast<uintptr_t>(cachedOffset));

    bridge->requestCompilerTask(JSCBridge::e_JIT_compileGetByIdChainList);
}

void JIT::compileGetByIdProto(VM* vm, CallFrame* callFrame, CodeBlock* codeBlock, StructureStubInfo* stubInfo, Structure* structure, Structure* prototypeStructure, const Identifier& ident, const PropertySlot& slot, PropertyOffset cachedOffset, ReturnAddressPtr returnAddress)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(vm));
    payload->sendArgument(reinterpret_cast<uintptr_t>(callFrame));
    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(stubInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(prototypeStructure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&ident)); // ident is only used as a TrustedImmPtr so it's ok for it to be not shared allocated
    payload->sendPOD(&slot); // slot is a const so it's safe to assume slot will not be modifed so no need to expect a return value from the compiler
    payload->sendArgument(     static_cast<uintptr_t>(cachedOffset));
    payload->sendArgument(reinterpret_cast<uintptr_t>(returnAddress.value()));

    bridge->requestCompilerTask(JSCBridge::e_JIT_compileGetByIdProto);
}

void JIT::compileGetByIdProtoList(VM* vm, CallFrame* callFrame, CodeBlock* codeBlock, StructureStubInfo* stubInfo, PolymorphicAccessStructureList* prototypeStructureList, int currentIndex, Structure* structure, Structure* prototypeStructure, const Identifier& ident, const PropertySlot& slot, PropertyOffset cachedOffset)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(vm));
    payload->sendArgument(reinterpret_cast<uintptr_t>(callFrame));
    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(stubInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(prototypeStructureList));
    payload->sendArgument(     static_cast<uintptr_t>(currentIndex));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(prototypeStructure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&ident)); // ident is only used as a TrustedImmPtr so it's ok for it to be not shared allocated
    payload->sendPOD(&slot); // slot is a const so it's safe to assume slot will not be modifed so no need to expect a return value from the compiler
    payload->sendArgument(     static_cast<uintptr_t>(cachedOffset));

    bridge->requestCompilerTask(JSCBridge::e_JIT_compileGetByIdProtoList);
}

void JIT::compileGetByIdSelfList(VM* vm, CodeBlock* codeBlock, StructureStubInfo* stubInfo, PolymorphicAccessStructureList* polymorphicStructures, int currentIndex, Structure* structure, const Identifier& ident, const PropertySlot& slot, PropertyOffset cachedOffset)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(vm));
    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(stubInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(polymorphicStructures));
    payload->sendArgument(     static_cast<uintptr_t>(currentIndex));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&ident)); // ident is only used as a TrustedImmPtr so it's ok for it to be not shared allocated
    payload->sendPOD(&slot); // slot is a const so it's safe to assume slot will not be modifed so no need to expect a return value from the compiler
    payload->sendArgument(     static_cast<uintptr_t>(cachedOffset));

    bridge->requestCompilerTask(JSCBridge::e_JIT_compileGetByIdSelfList);
}

void JIT::compileGetByVal(VM* vm, CodeBlock* codeBlock, ByValInfo* byValInfo, ReturnAddressPtr returnAddress, JITArrayMode arrayMode)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(vm));
    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(byValInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(returnAddress.value()));
    payload->sendArgument(     static_cast<uintptr_t>(arrayMode));

    bridge->requestCompilerTask(JSCBridge::e_JIT_compileGetByVal);
}

void JIT::compilePatchGetArrayLength(VM* vm, CodeBlock* codeBlock, ReturnAddressPtr returnAddress)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(vm));
    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(returnAddress.value()));

    bridge->requestCompilerTask(JSCBridge::e_JIT_compilePatchGetArrayLength);
}

void JIT::compilePutByIdTransition(VM* vm, CodeBlock* codeBlock, StructureStubInfo* stubInfo, Structure* oldStructure, Structure* newStructure, PropertyOffset cachedOffset, StructureChain* chain, ReturnAddressPtr returnAddress, bool direct)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(vm));
    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(stubInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(oldStructure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(newStructure));
    payload->sendArgument(     static_cast<uintptr_t>(cachedOffset));
    payload->sendArgument(reinterpret_cast<uintptr_t>(chain));
    payload->sendArgument(reinterpret_cast<uintptr_t>(returnAddress.value()));
    payload->sendArgument(     static_cast<uintptr_t>(direct));

    OwnPtr<JSCBridgeToll> toll(adoptPtr(bridge->createToll(payload.get())));
    toll->prepare(vm);
    toll->prepare(codeBlock);

    bridge->requestCompilerTask(JSCBridge::e_JIT_compilePutByIdTransition);
}

void JIT::compilePutByVal(VM* vm, CodeBlock* codeBlock, ByValInfo* byValInfo, ReturnAddressPtr returnAddress, JITArrayMode arrayMode)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(vm));
    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(byValInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(returnAddress.value()));
    payload->sendArgument(     static_cast<uintptr_t>(arrayMode));

    bridge->requestCompilerTask(JSCBridge::e_JIT_compilePutByVal);
}

void JIT::linkFor(JSFunction* callee, CodeBlock* callerCodeBlock, CodeBlock* calleeCodeBlock, MacroAssemblerCodePtr code, CallLinkInfo* callLinkInfo, VM* vm, CodeSpecializationKind kind)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());
    MacroAssemblerCodePtr * const sharedCode(sharedNew<MacroAssemblerCodePtr>(code));

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(callee));
    payload->sendArgument(reinterpret_cast<uintptr_t>(callerCodeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(calleeCodeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(sharedCode));
    payload->sendArgument(reinterpret_cast<uintptr_t>(callLinkInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(vm));
    payload->sendArgument(     static_cast<uintptr_t>(kind));

    bridge->requestCompilerTask(JSCBridge::e_JIT_linkFor);

    sharedDelete<MacroAssemblerCodePtr>(sharedCode);
}

void JIT::linkSlowCall(CodeBlock* callerCodeBlock, CallLinkInfo* callLinkInfo)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(callerCodeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(callLinkInfo));

    bridge->requestCompilerTask(JSCBridge::e_JIT_linkSlowCall);
}

} // namespace JSC

#endif // #if ENABLE(JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT
