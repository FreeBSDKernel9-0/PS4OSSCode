// Copyright (C) 2014 Sony Interactive Entertainment Inc.
// All Rights Reserved.

#include "config.h"

#include "JSCBridge.h"
#include "JSCBridgeToll.h"
#include "LLIntThunks.h"
#include "MacroAssemblerCodeRef.h"

#if ENABLE(JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT
#if ENABLE(LLINT) && !ENABLE(LLINT_C_LOOP)

namespace JSC {
namespace LLInt {

MacroAssemblerCodeRef generateThunkWithJumpTo(VM* vm, void (*target)(), const char *thunkKind)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(vm));
    payload->sendArgument(reinterpret_cast<uintptr_t>(target));

    OwnPtr<JSCBridgeToll> toll(adoptPtr(bridge->createToll(payload.get())));
    toll->prepare(vm);

    MacroAssemblerCodeRef * sharedCodeRef(reinterpret_cast<MacroAssemblerCodeRef *>(bridge->requestCompilerTask(JSCBridge::e_LLINT_generateThunk)));
    MacroAssemblerCodeRef codeRef(*sharedCodeRef);
    sharedDelete<MacroAssemblerCodeRef>(sharedCodeRef);

    return codeRef;
}

} // namespace LLInt
} // namespace JSC

#endif
#endif
