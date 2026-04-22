// Copyright (C) 2012 Sony Computer Entertainment Inc.
// All Rights Reserved.

#include "config.h"

#if ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

#include <wtf/OwnPtr.h>
#include "JIT.h"
//#include "JSCBridgeInternal.h"
#include "RepatchBuffer.h"

namespace JSC {

void JIT::patchGetByIdSelf(CodeBlock* codeBlock, StructureStubInfo* stubInfo, Structure* structure, PropertyOffset cachedOffset, ReturnAddressPtr returnAddress)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(stubInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(     static_cast<uintptr_t>(cachedOffset));
    payload->sendArgument(reinterpret_cast<uintptr_t>(returnAddress.value()));

    bridge->requestCompilerTask(JSCBridge::e_JIT_patchGetByIdSelf);
}

void JIT::patchPutByIdReplace(CodeBlock* codeBlock, StructureStubInfo* stubInfo, Structure* structure, PropertyOffset cachedOffset, ReturnAddressPtr returnAddress, bool direct)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(stubInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(     static_cast<uintptr_t>(cachedOffset));
    payload->sendArgument(reinterpret_cast<uintptr_t>(returnAddress.value()));
    payload->sendArgument(     static_cast<uintptr_t>(direct));

    bridge->requestCompilerTask(JSCBridge::e_JIT_patchPutByIdReplace);
}

void JIT::resetPatchGetById(RepatchBuffer& repatchBuffer, StructureStubInfo* stubInfo)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());
    RepatchBuffer * const sharedRepatchBuffer(sharedNew<RepatchBuffer>(repatchBuffer));

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(sharedRepatchBuffer));
    payload->sendArgument(reinterpret_cast<uintptr_t>(stubInfo));

    bridge->requestCompilerTask(JSCBridge::e_JIT_resetPatchGetById);

    repatchBuffer = *sharedRepatchBuffer;
    sharedDelete<RepatchBuffer>(sharedRepatchBuffer);
}

void JIT::resetPatchPutById(RepatchBuffer& repatchBuffer, StructureStubInfo* stubInfo)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());
    RepatchBuffer * const sharedRepatchBuffer(sharedNew<RepatchBuffer>(repatchBuffer));

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(sharedRepatchBuffer));
    payload->sendArgument(reinterpret_cast<uintptr_t>(stubInfo));

    bridge->requestCompilerTask(JSCBridge::e_JIT_resetPatchPutById);

    repatchBuffer = *sharedRepatchBuffer;
    sharedDelete<RepatchBuffer>(sharedRepatchBuffer);
}

} // namespace JSC

#endif // #if ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT
