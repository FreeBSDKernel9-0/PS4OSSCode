// Copyright (C) 2013 Sony Interactive Entertainment Inc.
// All Rights Reserved.

#include "config.h"

#if ENABLE(DFG_JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

#include "DFGRepatch.h"
#include "JSCJSValueInlines.h"

namespace JSC {
namespace DFG {

void dfgLinkClosureCall(ExecState* exec, CallLinkInfo& callLinkInfo, CodeBlock* calleeCodeBlock, Structure* structure, ExecutableBase* executable, MacroAssemblerCodePtr codePtr)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());
    MacroAssemblerCodePtr * const sharedCode(sharedNew<MacroAssemblerCodePtr>(codePtr));

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(exec));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&callLinkInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(calleeCodeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(executable));
    payload->sendArgument(reinterpret_cast<uintptr_t>(sharedCode));

    bridge->requestCompilerTask(JSCBridge::e_DFG_linkClosureCall);

    sharedDelete<MacroAssemblerCodePtr>(sharedCode);
}

void dfgRepatchByIdSelfAccess(CodeBlock* codeBlock, StructureStubInfo& stubInfo, Structure* structure, PropertyOffset offset, const FunctionPtr &slowPathFunction, bool compact)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&stubInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(     static_cast<uintptr_t>(offset));
    payload->sendArgument(reinterpret_cast<uintptr_t>(slowPathFunction.executableAddress()));
    payload->sendArgument(     static_cast<uintptr_t>(compact));

    bridge->requestCompilerTask(JSCBridge::e_DFG_repatchByIdSelfAccess);
}

void emitPutReplaceStub(
    ExecState* exec,
    JSValue baseValue,
    const Identifier& ident,
    const PutPropertySlot& slot,
    StructureStubInfo& stubInfo,
    PutKind putKind,
    Structure* structure,
    CodeLocationLabel failureLabel,
    RefPtr<JITStubRoutine>& stubRoutine)
{
    PROFILE_FUNCTION_CALL;

    RefPtr<JITStubRoutine> * stubRoutine_shared(sharedNew<RefPtr<JITStubRoutine> >(stubRoutine));

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(exec));
    payload->sendArgument(     static_cast<uintptr_t>(JSValue::encode(baseValue)));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&ident));
    payload->sendPOD(&slot); // slot is a const so it's safe to assume slot will not be modifed so no need to expect a return value from the compiler
    payload->sendArgument(reinterpret_cast<uintptr_t>(&stubInfo));
    payload->sendArgument(     static_cast<uintptr_t>(putKind));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(failureLabel.executableAddress()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(stubRoutine_shared));

    bridge->requestCompilerTask(JSCBridge::e_DFG_emitPutReplaceStub);

    stubRoutine = *stubRoutine_shared;
    sharedDelete<RefPtr<JITStubRoutine> >(stubRoutine_shared);
}

void emitPutTransitionStub(
    ExecState* exec,
    JSValue baseValue,
    const Identifier& ident,
    const PutPropertySlot& slot,
    StructureStubInfo& stubInfo,
    PutKind putKind,
    Structure* structure,
    Structure* oldStructure,
    StructureChain* prototypeChain,
    CodeLocationLabel failureLabel,
    RefPtr<JITStubRoutine>& stubRoutine)
{
    PROFILE_FUNCTION_CALL;

    RefPtr<JITStubRoutine> * stubRoutine_shared(sharedNew<RefPtr<JITStubRoutine> >(stubRoutine));

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(exec));
    payload->sendArgument(     static_cast<uintptr_t>(JSValue::encode(baseValue)));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&ident));
    payload->sendPOD(&slot); // slot is a const so it's safe to assume slot will not be modifed so no need to expect a return value from the compiler
    payload->sendArgument(reinterpret_cast<uintptr_t>(&stubInfo));
    payload->sendArgument(     static_cast<uintptr_t>(putKind));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(oldStructure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(prototypeChain));
    payload->sendArgument(reinterpret_cast<uintptr_t>(failureLabel.executableAddress()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(stubRoutine_shared));

    bridge->requestCompilerTask(JSCBridge::e_DFG_emitPutTransitionStub);

    stubRoutine = *stubRoutine_shared;
    sharedDelete<RefPtr<JITStubRoutine> >(stubRoutine_shared);
}

void generateProtoChainAccessStub(ExecState* exec, StructureStubInfo& stubInfo, StructureChain* chain, size_t count, PropertyOffset offset, Structure* structure, CodeLocationLabel successLabel, CodeLocationLabel slowCaseLabel, RefPtr<JITStubRoutine>& stubRoutine)
{
    PROFILE_FUNCTION_CALL;

    RefPtr<JITStubRoutine> * stubRoutine_shared(sharedNew<RefPtr<JITStubRoutine> >(stubRoutine));

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(exec));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&stubInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(chain));
    payload->sendArgument(     static_cast<uintptr_t>(count));
    payload->sendArgument(     static_cast<uintptr_t>(offset));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(successLabel.executableAddress()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(slowCaseLabel.executableAddress()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(stubRoutine_shared));

    bridge->requestCompilerTask(JSCBridge::e_DFG_generateProtoChainAccessStub);

    stubRoutine = *stubRoutine_shared;
    sharedDelete<RefPtr<JITStubRoutine> >(stubRoutine_shared);
}

bool tryBuildGetByIDList_vmstub(ExecState* exec, JSValue baseValue, const Identifier& ident, const PropertySlot& slot, StructureStubInfo& stubInfo)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(exec));
    payload->sendArgument(     static_cast<uintptr_t>(JSValue::encode(baseValue)));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&ident));
    payload->sendPOD(&slot); // slot is a const so it's safe to assume slot will not be modifed so no need to expect a return value from the compiler
    payload->sendArgument(reinterpret_cast<uintptr_t>(&stubInfo));

    bool result(static_cast<bool>(bridge->requestCompilerTask(JSCBridge::e_DFG_tryBuildGetByIDList)));
    return result;
}

bool tryCacheGetByID_vmstub(ExecState* exec, JSValue baseValue, const Identifier& propertyName, const PropertySlot& slot, StructureStubInfo& stubInfo)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(exec));
    payload->sendArgument(     static_cast<uintptr_t>(JSValue::encode(baseValue)));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&propertyName));
    payload->sendPOD(&slot); // slot is a const so it's safe to assume slot will not be modifed so no need to expect a return value from the compiler
    payload->sendArgument(reinterpret_cast<uintptr_t>(&stubInfo));

    bool result(static_cast<bool>(bridge->requestCompilerTask(JSCBridge::e_DFG_tryCacheGetByID)));
    return result;
}

} // namespace DFG
} // namespace JSC

#endif