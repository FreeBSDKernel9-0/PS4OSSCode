// Copyright (C) 2012 Sony Computer Entertainment Inc.
// All Rights Reserved.

#include "config.h"

#if ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

#include "JSCBridge.h"
#include "YarrJIT.h"

namespace JSC {
namespace Yarr {

void jitCompile(YarrPattern& pattern, YarrCharSize charSize, JSGlobalData* globalData, YarrCodeBlock& jitObject, YarrJITCompileMode mode)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    JSCBridge::Payload * const payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(&pattern));
    payload->sendArgument(     static_cast<uintptr_t>(charSize));
    payload->sendArgument(reinterpret_cast<uintptr_t>(globalData));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&jitObject));
    payload->sendArgument(     static_cast<uintptr_t>(mode));

    bridge->requestCompilerTask(JSCBridge::e_Yarr_jitCompile, NULL);
}

} // namespace Yarr
} // namespace JSC

#endif // #if ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT
