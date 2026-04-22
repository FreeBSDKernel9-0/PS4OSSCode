// Copyright (C) 2012 Sony Computer Entertainment Inc.
// All Rights Reserved.

#include "config.h"

#if ENABLE(JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

#include "AbstractMacroAssembler.h"
#include "JITStubs.h"
#include "JIT.h"
#include "JSCBridge.h"
#include "Logging.h"

namespace JSC {

#pragma message "clean me up"
/*
JIT::CodeRef JIT::privateCompileCTINativeCall(VM * vm, NativeFunction func)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(this));
    payload->sendArgument(reinterpret_cast<uintptr_t>(vm));
    payload->sendArgument(reinterpret_cast<uintptr_t>(func));

    CodeRef * result(reinterpret_cast<CodeRef *>(bridge->requestCompilerTask(JSCBridge::e_JIT_privateCompileCTINativeCall, this)));

    CodeRef retval(*result);
    result->~CodeRef();
    JITSharedDataMemory::shared_free(result);
    return retval;
}
*/

} // namespace JSC

#endif // #if ENABLE(JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT
