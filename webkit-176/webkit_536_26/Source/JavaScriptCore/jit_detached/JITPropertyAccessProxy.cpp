// Copyright (C) 2012 Sony Computer Entertainment Inc.
// All Rights Reserved.

#include "config.h"

#if ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

#include <wtf/OwnPtr.h>
#include "JIT.h"
#include "RepatchBuffer.h"

namespace JSC {

void JIT::patchGetByIdSelf(CodeBlock* codeBlock, StructureStubInfo* stubInfo, Structure* structure, size_t cachedOffset, ReturnAddressPtr returnAddress)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(stubInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(     static_cast<uintptr_t>(cachedOffset));
    payload->sendArgument(reinterpret_cast<uintptr_t>(returnAddress.value()));

    CodeBlock::RefundableToll toll(codeBlock ? codeBlock->obtainToll() : CodeBlock::Toll::s_nullToll);
    bridge->requestCompilerTask(JSCBridge::e_JIT_patchGetByIdSelf, NULL);
}

void JIT::patchMethodCallProto(JSGlobalData& globalData, CodeBlock* codeBlock, MethodCallLinkInfo& methodCallLinkInfo, StructureStubInfo& stubInfo, JSObject* callee, Structure* structure, JSObject* proto, ReturnAddressPtr returnAddress)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(&globalData));
    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&methodCallLinkInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&stubInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(callee));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(proto));
    payload->sendArgument(reinterpret_cast<uintptr_t>(returnAddress.value()));

    CodeBlock::RefundableToll toll(codeBlock ? codeBlock->obtainToll() : CodeBlock::Toll::s_nullToll);
    bridge->requestCompilerTask(JSCBridge::e_JIT_patchMethodCallProto, NULL);
}

void JIT::patchPutByIdReplace(CodeBlock* codeBlock, StructureStubInfo* stubInfo, Structure* structure, size_t cachedOffset, ReturnAddressPtr returnAddress, bool direct)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(codeBlock));
    payload->sendArgument(reinterpret_cast<uintptr_t>(stubInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(     static_cast<uintptr_t>(cachedOffset));
    payload->sendArgument(reinterpret_cast<uintptr_t>(returnAddress.value()));
    payload->sendArgument(     static_cast<uintptr_t>(direct));

    CodeBlock::RefundableToll toll(codeBlock ? codeBlock->obtainToll() : CodeBlock::Toll::s_nullToll);
    bridge->requestCompilerTask(JSCBridge::e_JIT_patchPutByIdReplace, NULL);
}

void JIT::privateCompileGetByIdChain(StructureStubInfo* stubInfo, Structure* structure, StructureChain* chain, size_t count, const Identifier& ident, const PropertySlot& slot, size_t cachedOffset, ReturnAddressPtr returnAddress, CallFrame* callFrame)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(this));
    payload->sendArgument(reinterpret_cast<uintptr_t>(stubInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(chain));
    payload->sendArgument(     static_cast<uintptr_t>(count));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&ident));
    payload->sendPOD(&slot);
    payload->sendArgument(     static_cast<uintptr_t>(cachedOffset));
    payload->sendArgument(reinterpret_cast<uintptr_t>(returnAddress.value()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(callFrame));

    CodeBlock::RefundableToll toll(this->obtainToll());
    bridge->requestCompilerTask(JSCBridge::e_JIT_privateCompileGetByIdChain, this);
}

void JIT::privateCompileGetByIdChainList(StructureStubInfo* stubInfo, PolymorphicAccessStructureList* prototypeStructures, int currentIndex, Structure* structure, StructureChain* chain, size_t count, const Identifier& ident, const PropertySlot& slot, size_t cachedOffset, CallFrame* callFrame)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(this));
    payload->sendArgument(reinterpret_cast<uintptr_t>(stubInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(prototypeStructures));
    payload->sendArgument(     static_cast<uintptr_t>(currentIndex));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(chain));
    payload->sendArgument(     static_cast<uintptr_t>(count));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&ident));
    payload->sendPOD(&slot);
    payload->sendArgument(     static_cast<uintptr_t>(cachedOffset));
    payload->sendArgument(reinterpret_cast<uintptr_t>(callFrame));

    CodeBlock::RefundableToll toll(this->obtainToll());
    bridge->requestCompilerTask(JSCBridge::e_JIT_privateCompileGetByIdChainList, this);
}

void JIT::privateCompileGetByIdProto(StructureStubInfo* stubInfo, Structure* structure, Structure* prototypeStructure, const Identifier& ident, const PropertySlot& slot, size_t cachedOffset, ReturnAddressPtr returnAddress, CallFrame* callFrame)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(this));
    payload->sendArgument(reinterpret_cast<uintptr_t>(stubInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(prototypeStructure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&ident));
    payload->sendPOD(&slot);
    payload->sendArgument(     static_cast<uintptr_t>(cachedOffset));
    payload->sendArgument(reinterpret_cast<uintptr_t>(returnAddress.value()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(callFrame));

    CodeBlock::RefundableToll toll(this->obtainToll());
    bridge->requestCompilerTask(JSCBridge::e_JIT_privateCompileGetByIdProto, this);
}

void JIT::privateCompileGetByIdProtoList(StructureStubInfo* stubInfo, PolymorphicAccessStructureList* prototypeStructures, int currentIndex, Structure* structure, Structure* prototypeStructure, const Identifier& ident, const PropertySlot& slot, size_t cachedOffset, CallFrame* callFrame)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());
    
    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(this));
    payload->sendArgument(reinterpret_cast<uintptr_t>(stubInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(prototypeStructures));
    payload->sendArgument(     static_cast<uintptr_t>(currentIndex));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(prototypeStructure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&ident));
    payload->sendPOD(&slot);
    payload->sendArgument(     static_cast<uintptr_t>(cachedOffset));
    payload->sendArgument(reinterpret_cast<uintptr_t>(callFrame));
    
    CodeBlock::RefundableToll toll(this->obtainToll());
    bridge->requestCompilerTask(JSCBridge::e_JIT_privateCompileGetByIdProtoList, this);
}

void JIT::privateCompileGetByIdSelfList(StructureStubInfo* stubInfo, PolymorphicAccessStructureList* polymorphicStructures, int currentIndex, Structure* structure, const Identifier& ident, const PropertySlot& slot, size_t cachedOffset)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());
    
    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(this));
    payload->sendArgument(reinterpret_cast<uintptr_t>(stubInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(polymorphicStructures));
    payload->sendArgument(     static_cast<uintptr_t>(currentIndex));
    payload->sendArgument(reinterpret_cast<uintptr_t>(structure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(&ident));
    payload->sendPOD(&slot);
    payload->sendArgument(     static_cast<uintptr_t>(cachedOffset));
    
    CodeBlock::RefundableToll toll(this->obtainToll());
    bridge->requestCompilerTask(JSCBridge::e_JIT_privateCompileGetByIdSelfList, this);
}

void JIT::privateCompilePatchGetArrayLength(ReturnAddressPtr returnAddress)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(this));
    payload->sendArgument(reinterpret_cast<uintptr_t>(returnAddress.value()));

    CodeBlock::RefundableToll toll(this->obtainToll());
    bridge->requestCompilerTask(JSCBridge::e_JIT_privateCompilePatchGetArrayLength, this);
}

void JIT::privateCompilePutByIdTransition(StructureStubInfo* stubInfo, Structure* oldStructure, Structure* newStructure, size_t cachedOffset, StructureChain* chain, ReturnAddressPtr returnAddress, bool direct)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(this));
    payload->sendArgument(reinterpret_cast<uintptr_t>(stubInfo));
    payload->sendArgument(reinterpret_cast<uintptr_t>(oldStructure));
    payload->sendArgument(reinterpret_cast<uintptr_t>(newStructure));
    payload->sendArgument(     static_cast<uintptr_t>(cachedOffset));
    payload->sendArgument(reinterpret_cast<uintptr_t>(chain));
    payload->sendArgument(reinterpret_cast<uintptr_t>(returnAddress.value()));
    payload->sendArgument(     static_cast<uintptr_t>(direct));

    CodeBlock::RefundableToll toll(this->obtainToll());
    bridge->requestCompilerTask(JSCBridge::e_JIT_privateCompilePutByIdTransition, this);
}

void JIT::resetPatchGetById(RepatchBuffer& repatchBuffer, StructureStubInfo* stubInfo)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const     bridge(JSCBridge::sharedInstance());
    OwnPtr<RepatchBuffer> sharedRepatchBuffer(adoptPtr(new RepatchBuffer(repatchBuffer)));

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(sharedRepatchBuffer.get()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(stubInfo));

    bridge->requestCompilerTask(JSCBridge::e_JIT_resetPatchGetById, NULL);
}

void JIT::resetPatchPutById(RepatchBuffer& repatchBuffer, StructureStubInfo* stubInfo)
{
    PROFILE_FUNCTION_CALL;

    JSCBridge * const     bridge(JSCBridge::sharedInstance());
    OwnPtr<RepatchBuffer> sharedRepatchBuffer(adoptPtr(new RepatchBuffer(repatchBuffer)));

    JSCBridge::Payload * payload(bridge->payload());
    payload->sendArgument(reinterpret_cast<uintptr_t>(sharedRepatchBuffer.get()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(stubInfo));

    bridge->requestCompilerTask(JSCBridge::e_JIT_resetPatchPutById, NULL);
}

} // namespace JSC

#endif // #if ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT
