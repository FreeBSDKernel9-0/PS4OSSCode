// Copyright (C) 2013 Sony Computer Entertainment Inc.
// All Rights Reserved.

#include "config.h"
#include "DFGRepatch.h"

#include "jit_detached/JSCBridge.h"

#if ENABLE(DFG_JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

namespace JSC {
namespace DFG {

void dfgCompileBuildGetByIDList(ExecState * exec, JSGlobalData * globalData, CodeBlock * codeBlock, Structure * structure, const Identifier& ident, const PropertySlot& slot, int listIndex, StructureStubInfo& stubInfo, PolymorphicAccessStructureList * polymorphicStructureList)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const           bridge(JSCBridge::sharedInstance());
    JSCBridge::Payload * const  payload(bridge->payload());

    payload->sendArgument(reinterpret_cast<uintptr_t>(exec));
    payload->sendArgument(reinterpret_cast<uintptr_t>(globalData));
    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&ident));
    payload->sendPOD(&slot);
    payload->sendArgument(     static_cast<uintptr_t>(listIndex));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&stubInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(polymorphicStructureList));

    bridge->requestCompilerTask(JSCBridge::e_DFG_compileBuildGetByIDList, NULL);
}

void dfgCompileCacheGetByIDArray(StructureStubInfo & stubInfo, CodeBlock * codeBlock, JSGlobalData * globalData)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const           bridge(JSCBridge::sharedInstance());
    JSCBridge::Payload * const  payload(bridge->payload());

    payload->sendArgument(reinterpret_cast<uintptr_t>(&stubInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(globalData));

    bridge->requestCompilerTask(JSCBridge::e_DFG_compileCacheGetByIDArray, NULL);
}

void dfgRepatchByIdSelfAccess(CodeBlock* codeBlock, StructureStubInfo& stubInfo, Structure* structure, size_t offset, const FunctionPtr &slowPathFunction, bool compact)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const           bridge(JSCBridge::sharedInstance());
    JSCBridge::Payload * const  payload(bridge->payload());

    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&stubInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(     static_cast<uintptr_t>(offset));
    payload->sendArgument(reinterpret_cast<uintptr_t>(slowPathFunction.value())); // it's a const so it's ok to send just the value over to the compiler
    payload->sendArgument(     static_cast<uintptr_t>(compact));

    bridge->requestCompilerTask(JSCBridge::e_DFG_repatchByIdSelfAccess, NULL);
}

void emitPutReplaceStub(ExecState* exec, JSValue, const Identifier&, const PutPropertySlot& slot, StructureStubInfo& stubInfo, PutKind putKind, Structure* structure, CodeLocationLabel failureLabel, MacroAssemblerCodeRef& stubRoutine)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const           bridge(JSCBridge::sharedInstance());
    JSCBridge::Payload * const  payload(bridge->payload());

    payload->sendArgument(reinterpret_cast<uintptr_t>(exec));
    payload->sendPOD(&slot);
    payload->sendArgument(reinterpret_cast<uintptr_t>(&stubInfo));
    payload->sendArgument(     static_cast<uintptr_t>(putKind));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(failureLabel.executableAddress()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&stubRoutine));

    bridge->requestCompilerTask(JSCBridge::e_DFG_emitPutReplaceStub, NULL);
}

void emitPutTransitionStub(ExecState* exec, JSValue, const Identifier&, const PutPropertySlot& slot, StructureStubInfo& stubInfo, PutKind putKind, Structure* structure, Structure* oldStructure, StructureChain* prototypeChain, CodeLocationLabel failureLabel, MacroAssemblerCodeRef& stubRoutine)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const           bridge(JSCBridge::sharedInstance());
    JSCBridge::Payload * const  payload(bridge->payload());

    payload->sendArgument(reinterpret_cast<uintptr_t>(exec));
    payload->sendPOD(&slot);
    payload->sendArgument(reinterpret_cast<uintptr_t>(&stubInfo));
    payload->sendArgument(     static_cast<uintptr_t>(putKind));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(oldStructure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(prototypeChain));
    payload->sendArgument(reinterpret_cast<uintptr_t>(failureLabel.executableAddress()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&stubRoutine));

    bridge->requestCompilerTask(JSCBridge::e_DFG_emitPutTransitionStub, NULL);
}

void generateProtoChainAccessStub(ExecState* exec, StructureStubInfo& stubInfo, StructureChain* chain, size_t count, size_t offset, Structure* structure, CodeLocationLabel successLabel, CodeLocationLabel slowCaseLabel, MacroAssemblerCodeRef& stubRoutine)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const           bridge(JSCBridge::sharedInstance());
    JSCBridge::Payload * const  payload(bridge->payload());

    payload->sendArgument(reinterpret_cast<uintptr_t>(exec));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&stubInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(chain));
    payload->sendArgument(     static_cast<uintptr_t>(count));
    payload->sendArgument(     static_cast<uintptr_t>(offset));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(successLabel.executableAddress()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(slowCaseLabel.executableAddress()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&stubRoutine));

    bridge->requestCompilerTask(JSCBridge::e_DFG_generateProtoChainAccessStub, NULL);
}

} // namespace DFG
} // namespace JSC

#endif // #if ENABLE(DFG_JIT) && ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT
