// Copyright (C) 2012 Sony Computer Entertainment Inc.
// All Rights Reserved.

#include "config.h"

#if ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

#include "JSCBridge.h"
#include "JSCBridgeToll.h"
#include "MacroAssemblerCodeRef.h"
#include "ThunkGenerators.h"

namespace JSC {

#define DEFINE_THUNKGENERATOR_PROXY(generator) \
    MacroAssemblerCodeRef generator(VM * vm) \
    { \
        PROFILE_FUNCTION_CALL; \
        JSCBridge * const    bridge(JSCBridge::sharedInstance()); \
        OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload())); \
        payload->sendArgument(reinterpret_cast<uintptr_t>(vm)); \
        OwnPtr<JSCBridgeToll> toll(adoptPtr(bridge->createToll(payload.get()))); \
        toll->prepare(vm); \
        MacroAssemblerCodeRef * sharedCodeRef(reinterpret_cast<MacroAssemblerCodeRef *>(bridge->requestCompilerTask(JSCBridge::e_##generator))); \
        MacroAssemblerCodeRef codeRef(*sharedCodeRef); \
        sharedDelete<MacroAssemblerCodeRef>(sharedCodeRef); \
        return codeRef; \
    }

    DEFINE_THUNKGENERATOR_PROXY(absThunkGenerator);
    DEFINE_THUNKGENERATOR_PROXY(ceilThunkGenerator);
    DEFINE_THUNKGENERATOR_PROXY(charAtThunkGenerator);
    DEFINE_THUNKGENERATOR_PROXY(charCodeAtThunkGenerator);
    DEFINE_THUNKGENERATOR_PROXY(expThunkGenerator);
    DEFINE_THUNKGENERATOR_PROXY(floorThunkGenerator);
    DEFINE_THUNKGENERATOR_PROXY(fromCharCodeThunkGenerator);
    DEFINE_THUNKGENERATOR_PROXY(imulThunkGenerator);
    DEFINE_THUNKGENERATOR_PROXY(linkCallGenerator);
    DEFINE_THUNKGENERATOR_PROXY(linkConstructGenerator);
    DEFINE_THUNKGENERATOR_PROXY(logThunkGenerator);
    DEFINE_THUNKGENERATOR_PROXY(nativeCallGenerator);
    DEFINE_THUNKGENERATOR_PROXY(nativeConstructGenerator);
    DEFINE_THUNKGENERATOR_PROXY(powThunkGenerator);
    DEFINE_THUNKGENERATOR_PROXY(roundThunkGenerator);
    DEFINE_THUNKGENERATOR_PROXY(sqrtThunkGenerator);
    DEFINE_THUNKGENERATOR_PROXY(stringLengthTrampolineGenerator);

} // namespace JSC

#endif // #if ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT
