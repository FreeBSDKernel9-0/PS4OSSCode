// Copyright (C) 2012 Sony Interactive Entertainment Inc.
// All Rights Reserved.

#include "config.h"

#if ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

#include "JSCBridge.h"
#include "YarrJIT.h"

namespace JSC {
namespace Yarr {

void jitCompile(YarrPattern& pattern, YarrCharSize charSize, VM* vm, YarrCodeBlock& jitObject, YarrJITCompileMode mode)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&pattern));
    payload->sendArgument(     static_cast<uintptr_t>(charSize));
    payload->sendArgument(reinterpret_cast<uintptr_t>(vm));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&jitObject));
    payload->sendArgument(     static_cast<uintptr_t>(mode));

    bridge->requestCompilerTask(JSCBridge::e_Yarr_jitCompile);
}

} // namespace Yarr
} // namespace JSC

#endif // #if ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT
