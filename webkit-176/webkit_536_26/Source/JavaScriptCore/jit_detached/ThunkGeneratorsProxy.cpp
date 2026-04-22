// Copyright (C) 2012 Sony Computer Entertainment Inc.
// All Rights Reserved.

#include "config.h"

#if ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

#include "JSCBridge.h"
#include "MacroAssemblerCodeRef.h"
#include "ThunkGenerators.h"

namespace JSC {

#define DEFINE_THUNKGENERATOR_PROXY(generator) \
    MacroAssemblerCodeRef generator(JSGlobalData * globalData) \
    { \
        PROFILE_FUNCTION_CALL; \
        JSCBridge * const bridge(JSCBridge::sharedInstance()); \
        JSCBridge::Payload * payload(bridge->payload()); \
        payload->sendArgument(reinterpret_cast<uintptr_t>(globalData)); \
        MacroAssemblerCodeRef * result(reinterpret_cast<MacroAssemblerCodeRef *>(bridge->requestCompilerTask(JSCBridge::e_##generator, NULL))); \
        MacroAssemblerCodeRef retval(*result); \
        result->~MacroAssemblerCodeRef(); \
        JITSharedDataMemory::shared_free(result); \
        return retval; \
    }

    DEFINE_THUNKGENERATOR_PROXY(absThunkGenerator);
    DEFINE_THUNKGENERATOR_PROXY(ceilThunkGenerator);
    DEFINE_THUNKGENERATOR_PROXY(charAtThunkGenerator);
    DEFINE_THUNKGENERATOR_PROXY(charCodeAtThunkGenerator);
    DEFINE_THUNKGENERATOR_PROXY(expThunkGenerator);
    DEFINE_THUNKGENERATOR_PROXY(floorThunkGenerator);
    DEFINE_THUNKGENERATOR_PROXY(fromCharCodeThunkGenerator);
    DEFINE_THUNKGENERATOR_PROXY(logThunkGenerator);
    DEFINE_THUNKGENERATOR_PROXY(powThunkGenerator);
    DEFINE_THUNKGENERATOR_PROXY(roundThunkGenerator);
    DEFINE_THUNKGENERATOR_PROXY(sqrtThunkGenerator);

} // namespace JSC

#endif // #if ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT
