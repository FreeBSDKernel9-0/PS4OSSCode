// Copyright (C) 2013 Sony Computer Entertainment Inc.
// All Rights Reserved.

#include "config.h"
#include "DFGOSRExitCompiler.h"

#include "jit_detached/JSCBridge.h"

#if ENABLE(DFG_JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

namespace JSC {
namespace DFG {

MacroAssemblerCodeRef linkClosureCallThunkGenerator(VM* vm)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(vm));

    MacroAssemblerCodeRef * sharedCodeRef(reinterpret_cast<MacroAssemblerCodeRef *>(bridge->requestCompilerTask(JSCBridge::e_DFG_linkClosureCallThunkGenerator)));
    MacroAssemblerCodeRef codeRef(*sharedCodeRef);
    sharedDelete<MacroAssemblerCodeRef>(sharedCodeRef);

    return codeRef;
}

MacroAssemblerCodeRef linkForThunkGenerator(VM* vm, CodeSpecializationKind kind)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(vm));
    payload->sendArgument(     static_cast<uintptr_t>(kind));

    MacroAssemblerCodeRef * sharedCodeRef(reinterpret_cast<MacroAssemblerCodeRef *>(bridge->requestCompilerTask(JSCBridge::e_DFG_linkForThunkGenerator)));
    MacroAssemblerCodeRef codeRef(*sharedCodeRef);
    sharedDelete<MacroAssemblerCodeRef>(sharedCodeRef);

    return codeRef;
}

MacroAssemblerCodeRef throwExceptionFromCallSlowPathGenerator(VM* vm)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(vm));

    MacroAssemblerCodeRef * sharedCodeRef(reinterpret_cast<MacroAssemblerCodeRef *>(bridge->requestCompilerTask(JSCBridge::e_DFG_throwExceptionFromCall)));
    MacroAssemblerCodeRef codeRef(*sharedCodeRef);
    sharedDelete<MacroAssemblerCodeRef>(sharedCodeRef);

    return codeRef;
}

MacroAssemblerCodeRef virtualForThunkGenerator(VM* vm, CodeSpecializationKind kind)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(vm));
    payload->sendArgument(     static_cast<uintptr_t>(kind));

    MacroAssemblerCodeRef * sharedCodeRef(reinterpret_cast<MacroAssemblerCodeRef *>(bridge->requestCompilerTask(JSCBridge::e_DFG_virtualForThunkGenerator)));
    MacroAssemblerCodeRef codeRef(*sharedCodeRef);
    sharedDelete<MacroAssemblerCodeRef>(sharedCodeRef);

    return codeRef;
}

} // namespace DFG
} // namespace JSC

#endif // #if ENABLE(DFG_JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

