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

    OwnPtr<JITCode> sharedEntry(adoptPtr(sharedNew<JITCode>(entry)));

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&(this->m_graph)));
    payload->sendArgument(reinterpret_cast<uintptr_t>(sharedEntry.get()));

    // prepare toll
    OwnPtr<JSCBridgeToll> toll(adoptPtr(bridge->createToll(payload.get())));
    toll->prepare(m_graph.m_codeBlock);

    uintptr_t result(bridge->requestCompilerTask(JSCBridge::e_DFG_compile));

    entry = *sharedEntry;

    return static_cast<bool>(result);
}

bool JITCompiler::compileFunction(JITCode& entry, MacroAssemblerCodePtr& entryWithArityCheck)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JITCode> sharedEntry(adoptPtr(sharedNew<JITCode>(entry)));
    OwnPtr<MacroAssemblerCodePtr> sharedEntryWithArityCheck(adoptPtr(sharedNew<MacroAssemblerCodePtr>(entryWithArityCheck)));

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&(this->m_graph)));
    payload->sendArgument(reinterpret_cast<uintptr_t>(sharedEntry.get()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(sharedEntryWithArityCheck.get()));

    // prepare toll
    OwnPtr<JSCBridgeToll> toll(adoptPtr(bridge->createToll(payload.get())));
    toll->prepare(m_graph.m_codeBlock);

    uintptr_t result(bridge->requestCompilerTask(JSCBridge::e_DFG_compileFunction));

    entry = *sharedEntry;
    entryWithArityCheck = *sharedEntryWithArityCheck;

    return static_cast<bool>(result);
}

} // namespace DFG
} // namespace JSC

#endif // #if ENABLE(DFG_JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT
