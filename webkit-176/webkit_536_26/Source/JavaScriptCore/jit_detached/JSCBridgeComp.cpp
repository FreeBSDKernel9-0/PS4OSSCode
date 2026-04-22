// Copyright (C) 2012 Sony Computer Entertainment Inc.
// All Rights Reserved.

#include "config.h"

#include "JSCBridge.cpp"

#if ENABLE(JIT) && ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT

#include "AbstractMacroAssembler.h"
#include "ArrayConstructor.h"
#include "ArrayPrototype.h"
#include "AssemblerBuffer.h"
#include "BooleanConstructor.h"
#include "DateConstructor.h"
#include "DateInstance.h"
#include "DatePrototype.h"
#if ENABLE(DFG_JIT)
#include "DFGJITCompiler.h"
#include "DFGOSRExitCompiler.h"
#include "DFGRepatch.h"
#endif
#include "Error.h"
#include "ErrorConstructor.h"
#include "FunctionConstructor.h"
#include "FunctionPrototype.h"
#include "InternalFunction.h"
#include "InitializeThreading.h"
#include "JIT.h"
#include "JITStubEntries.h"
#include "JSActivation.h"
#include "JSArray.h"
#include "JSBoundFunction.h"
#include "JSFunction.h"
#include "JSGlobalObject.h"
#include "LinkBuffer.h"
#include "Logging.h"
#include "MacroAssembler.h"
#include "MathObject.h"
#include "NativeErrorConstructor.h"
#include "NumberConstructor.h"
#include "ObjectConstructor.h"
#include "ObjectPrototype.h"
#include "RegExpConstructor.h"
#include "RegExpPrototype.h"
#include "RepatchBuffer.h"
#include "StringConstructor.h"
#include "ThunkGenerators.h"
#include "YarrJIT.h"

#if !defined(NDEBUG)
#define DEBUG_LOG(x, ...) fprintf(stderr, "[JSC bridge comp] " x, __VA_ARGS__)
#else
#define DEBUG_LOG(x, ...)
#endif
#define DEBUG_ERR(x, ...) fprintf(stderr, "[JSC bridge comp] " x, __VA_ARGS__)

namespace JSC {

void JSCBridge::fixupClassInfo(ClassInfo * classInfo)
{
    ClassInfo * ci(classInfo);
    while (ci) {
        ClassInfo const * parent(ci->parentClass);
        ClassInfo const * resolvedParent(NULL);
        if (parent && (resolvedParent = mapFromVMToCompiler(parent))) {
            ci->parentClass = resolvedParent;
        }
        ci = const_cast<ClassInfo *>(resolvedParent);
    }
}

void JSCBridge::initializeCompilerSharedData()
{
    // wait for VM to prepare all data the compiler process needs
    waitDoorbell();

    JSC::JSCBridge::StaticVMData * vmData(staticVMData());

    ExecutableAllocator::setMetaAllocator(reinterpret_cast<WTF::MetaAllocator *>(vmData->m_executableAllocator));

    ctiVMThrowTrampoline = vmData->m_ctiVMThrowTrampoline;

#define CTI_STUB_ENTRY(ignoredReturnType, stub) stub = vmData->m_##stub;
    CTI_STUB_ENTRIES;
#if ENABLE(DFG_JIT)
    CTI_STUB_ENTRIES_DFG;
#endif
#undef  CTI_STUB_ENTRY

#if ENABLE(DFG_JIT)
#define CTI_STUB_ENTRY(ignoredReturnType, stub) DFG::stub = vmData->m_##stub;
    CTI_STUB_ENTRIES_DFG_OPERATIONS;
#undef  CTI_STUB_ENTRY
#endif

#define CLASSINFO_STUB_ENTRY(classname) \
    { \
        JSC:: classname##Stub ::s_info = vmData->m_##classname##_classinfo; \
        ASSERT(sizeof(vmData->m_##classname##_classinfo_copy) == sizeof(JSC::classname::s_info)); \
        memcpy(reinterpret_cast<void *>(&JSC::classname::s_info), reinterpret_cast<void *>(vmData->m_##classname##_classinfo_copy), sizeof(JSC::classname::s_info)); \
        /*DEBUG_LOG("(vm address) %lx   (comp address) %lx : %s\n", vmData->m_##classname##_classinfo, (uintptr_t)&JSC::classname::s_info, #classname);*/ \
    }
    CLASSINFO_STUB_ENTRIES;
#undef  CLASSINFO_STUB_ENTRY

    // perform classinfo fixup after all classinfo data have been loaded in the previous code block
#define CLASSINFO_STUB_ENTRY(classname) fixupClassInfo(&JSC::classname::s_info);
    CLASSINFO_STUB_ENTRIES;
#undef  CLASSINFO_STUB_ENTRY
    for (size_t i = 0; i < vmData->m_runtimeClassInfoCount; ++i) {
        fixupClassInfo(reinterpret_cast<ClassInfo*>(&(vmData->m_runtimeClassInfo[i].m_data[0])));
        //DEBUG_LOG("(vm address) %lx   (comp address) %lx\n", vmData->m_runtimeClassInfo[i].m_classInfoPtr, (uintptr_t)&(vmData->m_runtimeClassInfo[i].m_data[0]));
    }

    // These are needed by the ThunkGenerators
    JSC::RemoteStubs::oneConstant          = vmData->m_oneConstant;
    JSC::RemoteStubs::negativeHalfConstant = vmData->m_negativeHalfConstant;
    JSC::RemoteStubs::negativeZeroConstant = vmData->m_negativeZeroConstant;

    // These are needed by Yarr
    JSC::Yarr::RemoteStubs::regExp_spacesData   = reinterpret_cast<char const *>(vmData->m_regExpSpacesData);
    JSC::Yarr::RemoteStubs::regExp_wordcharData = reinterpret_cast<char const *>(vmData->m_regExpWordCharData);

    // These are needed by DFG JIT
    JSC::RemoteStubs::zero = vmData->m_zero;
    JSC::RemoteStubs::byteMax = vmData->m_byteMax;
    JSC::RemoteStubs::half = vmData->m_half;
    JSC::RemoteStubs::twoToThe32 = vmData->m_twoToThe32;
    JSC::RemoteStubs::NaN = vmData->m_NaN;

    // notify that all compiler data the VM needs are ready
    ringDoorbell();
}

void JSCBridge::initializeFromCompiler(size_t sharedDataMemorySize, size_t sharedTextMemorySize, char const * vmTestApp, char ** vmTestAppArgs, JITBridge::RestartData const * restartData)
{
    if (m_processType != ProcessUnknown) {
        __builtin_trap();
    }

    m_processType = ProcessCompiler;
    m_sharedBridge = JITBridge::initializeFromCompiler(sharedDataMemorySize, sharedTextMemorySize, vmTestApp, vmTestAppArgs, restartData);

    // initialize, then notify shared data arenas are ready
    initializeSharedData();
    ringDoorbell();

    JSC::initializeThreading();

    initializeCompilerSharedData();
}

void JSCBridge::initializeFromVM(char const *, char **, JITBridge::RestartData const *)
{
    // you MUST NOT call this function from the compiler process
    __builtin_trap();
}

/*!
 * @brief Given a classInfo instance defined in the VM side, returns the corresponding
 *        classInfo defined in the detached JIT compiler side.  Use of this is mainly
 *        needed by the JIT compiler to perform runtime type checking of JS objects
 */
template <> ClassInfo const * JSCBridge::mapFromVMToCompiler(ClassInfo const * vmClassInfoAddress) const
{
    JSCBridge const    * bridge(JSCBridge::sharedInstance());
    StaticVMData const * vmData(&(bridge->m_sharedData->m_staticVMData));
    uintptr_t            ci(reinterpret_cast<uintptr_t>(vmClassInfoAddress));

    // look at the list of all ClassInfo objects statically defined within Source/JavaScriptCore
#define CLASSINFO_STUB_ENTRY(classname) \
    if ((ci == vmData->m_##classname##_classinfo) || (ci == reinterpret_cast<uintptr_t>(&JSC::classname::s_info))) { return &JSC::classname::s_info; }
    CLASSINFO_STUB_ENTRIES;
#undef CLASSINFO_STUB_ENTRY

    // these are the 'dynamic' ones which are not defined in Source/JavaScriptCore
    // (except for the one in jsc.cpp, these are mainly defined in WebCore when it
    //  uses internal JSCore C++ APIs)
    for (size_t i = 0; i < vmData->m_runtimeClassInfoCount; ++i) {
        if ((ci == reinterpret_cast<uintptr_t>(&(vmData->m_runtimeClassInfo[i].m_data[0]))) ||  // is vmClassInfoAddress already mapped to compiler?
            (ci == vmData->m_runtimeClassInfo[i].m_classInfoPtr)) {                                     // or, does vmClassInfoAddress map to one of our compiler-side classInfo?
            return reinterpret_cast<ClassInfo const*>(&(vmData->m_runtimeClassInfo[i].m_data[0]));
        }
    }

    DEBUG_ERR("failed to VM->Compiler map classinfo %lx\n", (uintptr_t)vmClassInfoAddress);
    __builtin_trap();
    ASSERT(false);
    return NULL;
}

void JSCBridge::performCompilerTask()
{
    PROFILE_FUNCTION_CALL;

#define DEFINE_THUNKGENERATOR_CASE(generator) \
    case e_##generator: \
    { \
        LOG(DetachedJIT, "[Bridge-Compiler] e_%s\n", #generator); \
        JSGlobalData *        globalData(reinterpret_cast<JSGlobalData *>(payload->recvArgument())); \
        void *                resultBuffer(JITSharedDataMemory::shared_malloc(sizeof(MacroAssemblerCodeRef))); \
        MacroAssemblerCodeRef result(generator(globalData)); \
        payload->m_retval = reinterpret_cast<uintptr_t>(new(resultBuffer) MacroAssemblerCodeRef(result)); \
        LOG(DetachedJIT, "[Bridge-Compiler] e_%s DONE\n", #generator); \
        break; \
    }

    Payload * const  payload(&m_sharedData->m_payload);

    switch (m_sharedData->m_payload.m_compilerFunction) {

    DEFINE_THUNKGENERATOR_CASE(absThunkGenerator)
    DEFINE_THUNKGENERATOR_CASE(ceilThunkGenerator)
    DEFINE_THUNKGENERATOR_CASE(charAtThunkGenerator)
    DEFINE_THUNKGENERATOR_CASE(charCodeAtThunkGenerator)
    DEFINE_THUNKGENERATOR_CASE(expThunkGenerator)
    DEFINE_THUNKGENERATOR_CASE(floorThunkGenerator)
    DEFINE_THUNKGENERATOR_CASE(fromCharCodeThunkGenerator)
    DEFINE_THUNKGENERATOR_CASE(logThunkGenerator)
    DEFINE_THUNKGENERATOR_CASE(powThunkGenerator)
    DEFINE_THUNKGENERATOR_CASE(roundThunkGenerator)
    DEFINE_THUNKGENERATOR_CASE(sqrtThunkGenerator)

    case e_JIT_linkFor:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_linkFor\n");
            JSFunction *                        callee(reinterpret_cast<JSFunction *>(payload->recvArgument()));
            CodeBlock *                         callerCodeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            CodeBlock *                         calleeCodeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            JIT::CodePtr *                      code(reinterpret_cast<JIT::CodePtr *>(payload->recvArgument()));
            CallLinkInfo *                      callLinkInfo(reinterpret_cast<CallLinkInfo *>(payload->recvArgument()));
            JSGlobalData *                      globalData(reinterpret_cast<JSGlobalData *>(payload->recvArgument()));
            CodeSpecializationKind              kind(static_cast<CodeSpecializationKind>(payload->recvArgument()));
            JIT::linkFor(callee, callerCodeBlock, calleeCodeBlock, *code, callLinkInfo, globalData, kind);
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_linkFor DONE\n");
            break;
        }
    case e_ctiPatchCallReturnAddrCodePtr:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_ctiPatchCallByReturnAddressForCodePtr\n");
            CodeBlock *                         codeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            void *                              returnAddress(reinterpret_cast<void *>(payload->recvArgument()));
            void *                              newCalleeFunction(reinterpret_cast<void *>(payload->recvArgument()));
            ctiPatchCallByReturnAddress(codeBlock, ReturnAddressPtr(returnAddress), MacroAssemblerCodePtr(newCalleeFunction));
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_ctiPatchCallByReturnAddressForCodePtr DONE\n");
            break;
        }
    case e_ctiPatchCallReturnAddrFunctionPtr:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_ctiPatchCallByReturnAddressForFunctionPtr\n");
            CodeBlock *                         codeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            void *                              returnAddress(reinterpret_cast<void *>(payload->recvArgument()));
            void *                              newCalleeFunction(reinterpret_cast<void *>(payload->recvArgument()));
            ctiPatchCallByReturnAddress(codeBlock, ReturnAddressPtr(returnAddress), FunctionPtr(newCalleeFunction));
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_ctiPatchCallByReturnAddressForFunctionPtr DONE\n");
            break;
        }
    case e_ctiPatchNearCallByReturnAddress:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_ctiPatchNearCallByReturnAddress\n");
            CodeBlock *                         codeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            void *                              returnAddress(reinterpret_cast<void *>(payload->recvArgument()));
            void *                              newCalleeFunction(reinterpret_cast<void *>(payload->recvArgument()));
            ctiPatchNearCallByReturnAddress(codeBlock, ReturnAddressPtr(returnAddress), MacroAssemblerCodePtr(newCalleeFunction));
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_ctiPatchNearCallByReturnAddress DONE\n");
            break;
        }
    case e_DFG_compile:
        {
#if ENABLE(DFG_JIT)
            LOG(DetachedJIT, "[Bridge-Compiler] e_DFG_compile\n");
            DFG::JITCompiler *                  dfgCompiler(reinterpret_cast<DFG::JITCompiler*>(payload->recvArgument()));
            JITCode *                           entry(reinterpret_cast<JITCode *>(payload->recvArgument()));
            payload->m_retval = static_cast<uintptr_t>(dfgCompiler->compile(*entry));
            LOG(DetachedJIT, "[Bridge-Compiler] e_DFG_compile DONE\n");
#endif
            break;
        }
    case e_DFG_compileBuildGetByIDList:
        {
#if ENABLE(DFG_JIT)
            LOG(DetachedJIT, "[Bridge-Compiler] e_DFG_compileBuildGetByIDList\n");
            ExecState *                         exec(reinterpret_cast<ExecState *>(payload->recvArgument()));
            JSGlobalData *                      globalData(reinterpret_cast<JSGlobalData *>(payload->recvArgument()));
            CodeBlock *                         codeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            Structure *                         structure(reinterpret_cast<Structure *>(payload->recvArgument()));
            Identifier const *                  ident(reinterpret_cast<Identifier const *>(payload->recvArgument()));
            PropertySlot const *                slot(payload->recvPOD<PropertySlot>());
            int                                 listIndex(static_cast<int>(payload->recvArgument()));
            StructureStubInfo *                 stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            PolymorphicAccessStructureList *    polymorphicStructureList(reinterpret_cast<PolymorphicAccessStructureList *>(payload->recvArgument()));
            JSC::DFG::dfgCompileBuildGetByIDList(exec, globalData, codeBlock, structure, *ident, *slot, listIndex, *stubInfo, polymorphicStructureList);
            LOG(DetachedJIT, "[Bridge-Compiler] e_DFG_compileBuildGetByIDList DONE\n");
#endif
            break;
        }
    case e_DFG_compileCacheGetByIDArray:
        {
#if ENABLE(DFG_JIT)
            LOG(DetachedJIT, "[Bridge-Compiler] e_DFG_compileCacheGetByIDArray\n");
            StructureStubInfo *                 stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            CodeBlock *                         codeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            JSGlobalData *                      globalData(reinterpret_cast<JSGlobalData *>(payload->recvArgument()));
            JSC::DFG::dfgCompileCacheGetByIDArray(*stubInfo, codeBlock, globalData);
            LOG(DetachedJIT, "[Bridge-Compiler] e_DFG_compileCacheGetByIDArray DONE\n");
#endif
            break;
        }
    case e_DFG_compileFunction:
        {
#if ENABLE(DFG_JIT)
            LOG(DetachedJIT, "[Bridge-Compiler] e_DFG_compileFunction\n");
            DFG::JITCompiler *                  dfgCompiler(reinterpret_cast<DFG::JITCompiler*>(payload->recvArgument()));
            JITCode *                           entry(reinterpret_cast<JITCode *>(payload->recvArgument()));
            MacroAssemblerCodePtr *             entryWithArityCheck(reinterpret_cast<MacroAssemblerCodePtr *>(payload->recvArgument()));
            payload->m_retval = static_cast<uintptr_t>(dfgCompiler->compileFunction(*entry, *entryWithArityCheck));
            LOG(DetachedJIT, "[Bridge-Compiler] e_DFG_compileFunction DONE\n");
#endif
            break;
        }
    case e_DFG_compileOSRExit:
        {
#if ENABLE(DFG_JIT)
            LOG(DetachedJIT, "[Bridge-Compiler] e_DFG_compileOSRExit\n");
            ExecState *                         exec(reinterpret_cast<ExecState *>(payload->recvArgument()));
            JSC::DFG::compileOSRExit(exec);
            LOG(DetachedJIT, "[Bridge-Compiler] e_DFG_compileOSRExit DONE\n");
#endif
            break;
        }
    case e_DFG_emitPutReplaceStub:
        {
#if ENABLE(DFG_JIT)
            LOG(DetachedJIT, "[Bridge-Compiler] e_DFG_emitPutReplaceStub\n");
            ExecState *                         exec(reinterpret_cast<ExecState *>(payload->recvArgument()));
            PutPropertySlot const *             slot(payload->recvPOD<PutPropertySlot>());
            StructureStubInfo *                 stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            PutKind                             putKind(static_cast<PutKind>(payload->recvArgument()));
            Structure *                         structure(reinterpret_cast<Structure *>(payload->recvArgument()));
            CodeLocationLabel                   failureLabel(reinterpret_cast<void *>(payload->recvArgument()));
            MacroAssemblerCodeRef *             stubRoutine(reinterpret_cast<MacroAssemblerCodeRef *>(payload->recvArgument()));
            JSC::DFG::emitPutReplaceStub(exec, JSValue(), Identifier(), *slot, *stubInfo, putKind, structure, failureLabel, *stubRoutine);
            LOG(DetachedJIT, "[Bridge-Compiler] e_DFG_emitPutReplaceStub DONE\n");
#endif
            break;
        }
    case e_DFG_emitPutTransitionStub:
        {
#if ENABLE(DFG_JIT)
            LOG(DetachedJIT, "[Bridge-Compiler] e_DFG_emitPutTransitionStub\n");
            ExecState *                         exec(reinterpret_cast<ExecState *>(payload->recvArgument()));
            PutPropertySlot const *             slot(payload->recvPOD<PutPropertySlot>());
            StructureStubInfo *                 stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            PutKind                             putKind(static_cast<PutKind>(payload->recvArgument()));
            Structure *                         structure(reinterpret_cast<Structure *>(payload->recvArgument()));
            Structure *                         oldStructure(reinterpret_cast<Structure *>(payload->recvArgument()));
            StructureChain *                    prototypeChain(reinterpret_cast<StructureChain *>(payload->recvArgument()));
            CodeLocationLabel                   failureLabel(reinterpret_cast<void *>(payload->recvArgument()));
            MacroAssemblerCodeRef *             stubRoutine(reinterpret_cast<MacroAssemblerCodeRef *>(payload->recvArgument()));
            JSC::DFG::emitPutTransitionStub(exec, JSValue(), Identifier(), *slot, *stubInfo, putKind, structure, oldStructure, prototypeChain, failureLabel, *stubRoutine);
            LOG(DetachedJIT, "[Bridge-Compiler] e_DFG_emitPutTransitionStub DONE\n");
#endif
            break;
        }
    case e_DFG_generateProtoChainAccessStub:
        {
#if ENABLE(DFG_JIT)
            LOG(DetachedJIT, "[Bridge-Compiler] e_DFG_generateProtoChainAccessStub\n");
            ExecState *                         exec(reinterpret_cast<ExecState *>(payload->recvArgument()));
            StructureStubInfo *                 stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            StructureChain *                    chain(reinterpret_cast<StructureChain *>(payload->recvArgument()));
            size_t                              count(static_cast<size_t>(payload->recvArgument()));
            size_t                              offset(static_cast<size_t>(payload->recvArgument()));
            Structure *                         structure(reinterpret_cast<Structure *>(payload->recvArgument()));
            CodeLocationLabel                   successLabel(reinterpret_cast<void *>(payload->recvArgument()));
            CodeLocationLabel                   slowCaseLabel(reinterpret_cast<void *>(payload->recvArgument()));
            MacroAssemblerCodeRef *             stubRoutine(reinterpret_cast<MacroAssemblerCodeRef *>(payload->recvArgument()));
            JSC::DFG::generateProtoChainAccessStub(exec, *stubInfo, chain, count, offset, structure, successLabel, slowCaseLabel, *stubRoutine);
            LOG(DetachedJIT, "[Bridge-Compiler] e_DFG_generateProtoChainAccessStub DONE\n");
#endif
            break;
        }
    case e_DFG_repatchByIdSelfAccess:
        {
#if ENABLE(DFG_JIT)
            LOG(DetachedJIT, "[Bridge-Compiler] e_DFG_repatchByIdSelfAccess\n");
            CodeBlock *                         codeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            StructureStubInfo *                 stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            Structure *                         structure(reinterpret_cast<Structure *>(payload->recvArgument()));
            size_t                              offset(static_cast<size_t>(payload->recvArgument()));
            FunctionPtr const                   slowPathFunction(reinterpret_cast<void *>(payload->recvArgument()));
            bool                                compact(static_cast<bool>(payload->recvArgument()));
            JSC::DFG::dfgRepatchByIdSelfAccess(codeBlock, *stubInfo, structure, offset, slowPathFunction, compact);
            LOG(DetachedJIT, "[Bridge-Compiler] e_DFG_repatchByIdSelfAccess DONE\n");
#endif
            break;
        }
    case e_JIT_patchGetByIdSelf:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_patchGetByIdSelf\n");
            CodeBlock *                         codeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            StructureStubInfo *                 stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            Structure *                         structure(reinterpret_cast<Structure *>(payload->recvArgument()));
            size_t                              cachedOffset(static_cast<size_t>(payload->recvArgument()));
            void *                              returnAddress(reinterpret_cast<void *>(payload->recvArgument()));
            JIT::patchGetByIdSelf(codeBlock, stubInfo, structure, cachedOffset, ReturnAddressPtr(returnAddress));
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_patchGetByIdSelf DONE\n");
            break;
        }
    case e_JIT_patchMethodCallProto:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_patchMethodCallProto\n");
            JSGlobalData *                      globalData(reinterpret_cast<JSGlobalData *>(payload->recvArgument()));
            CodeBlock *                         codeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            MethodCallLinkInfo *                methodCallLinkInfo(reinterpret_cast<MethodCallLinkInfo *>(payload->recvArgument()));
            StructureStubInfo *                 stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            JSObject *                          callee(reinterpret_cast<JSObject *>(payload->recvArgument()));
            Structure *                         structure(reinterpret_cast<Structure *>(payload->recvArgument()));
            JSObject *                          proto(reinterpret_cast<JSObject *>(payload->recvArgument()));
            void *                              returnAddress(reinterpret_cast<void *>(payload->recvArgument()));
            JIT::patchMethodCallProto(*globalData, codeBlock, *methodCallLinkInfo, *stubInfo, callee, structure, proto, ReturnAddressPtr(returnAddress));
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_patchMethodCallProto DONE\n");
            break;
       }
    case e_JIT_patchPutByIdReplace:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_patchGetByIdReplace\n");
            CodeBlock *                         codeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            StructureStubInfo *                 stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            Structure *                         structure(reinterpret_cast<Structure *>(payload->recvArgument()));
            size_t                              cachedOffset(static_cast<size_t>(payload->recvArgument()));
            void *                              returnAddress(reinterpret_cast<void *>(payload->recvArgument()));
            bool                                direct(!!payload->recvArgument());
            JIT::patchPutByIdReplace(codeBlock, stubInfo, structure, cachedOffset, ReturnAddressPtr(returnAddress), direct);
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_patchGetByIdReplace DONE\n");
            break;
        }
    case e_JIT_privateCompileCTIMachineTrampolines:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_privateCompileCTIMachineTrampolines\n");
            JIT *                               jit(reinterpret_cast<JIT *>(payload->recvArgument()));
            JSGlobalData *                      globalData(reinterpret_cast<JSGlobalData *>(payload->recvArgument()));
            TrampolineStructure *               trampolines(reinterpret_cast<TrampolineStructure *>(payload->recvArgument()));
            PassRefPtr<ExecutableMemoryHandle>  result(jit->privateCompileCTIMachineTrampolines(globalData, trampolines));
            payload->m_retval = reinterpret_cast<uintptr_t>(result.leakRef());
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_privateCompileCTIMachineTrampolines DONE\n");
            break;
        }
    case e_JIT_privateCompileCTINativeCall:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_privateCompileCTINativeCall\n");
            JIT *                               jit(reinterpret_cast<JIT *>(payload->recvArgument()));
            JSGlobalData *                      globalData(reinterpret_cast<JSGlobalData *>(payload->recvArgument()));
            NativeFunction                      func(reinterpret_cast<NativeFunction>(payload->recvArgument()));
            JIT::CodeRef                        result(jit->privateCompileCTINativeCall(globalData, func));
            void *                              resultBuffer(JITSharedDataMemory::shared_malloc(sizeof(JIT::CodeRef)));
            payload->m_retval = reinterpret_cast<uintptr_t>(new(resultBuffer) JIT::CodeRef(result));
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_privateCompileCTINativeCall DONE\n");
            break;
        }
    case e_JIT_privateCompile:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_privateCompile\n");
            JIT *                               jit(reinterpret_cast<JIT *>(payload->recvArgument()));
            JIT::CodePtr *                      functionEntryArityCheck (reinterpret_cast<JIT::CodePtr *>(payload->recvArgument()));
            JITCompilationEffort                effort(static_cast<JITCompilationEffort>(payload->recvArgument()));
            payload->m_retval = reinterpret_cast<uintptr_t>(new JITCode(jit->privateCompile(functionEntryArityCheck, effort)));
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_privateCompile DONE\n");
            break;
        }
    case e_JIT_privateCompileGetByIdChain:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_privateCompileGetByIdChain\n");
            JIT *                               jit(reinterpret_cast<JIT *>(payload->recvArgument()));
            StructureStubInfo *                 stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            Structure *                         structure(reinterpret_cast<Structure *>(payload->recvArgument()));
            StructureChain *                    chain(reinterpret_cast<StructureChain *>(payload->recvArgument()));
            size_t                              count(static_cast<size_t>(payload->recvArgument()));
            Identifier const *                  ident(reinterpret_cast<Identifier const *>(payload->recvArgument()));
            PropertySlot const *                slot(payload->recvPOD<PropertySlot>());
            size_t                              cachedOffset(static_cast<size_t>(payload->recvArgument()));
            void *                              returnAddress(reinterpret_cast<void *>(payload->recvArgument()));
            CallFrame *                         callFrame(reinterpret_cast<CallFrame *>(payload->recvArgument()));
            jit->privateCompileGetByIdChain(stubInfo, structure, chain, count, *ident, *slot, cachedOffset, ReturnAddressPtr(returnAddress), callFrame);
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_privateCompileGetByIdChain DONE\n");
            break;
        }
    case e_JIT_privateCompileGetByIdChainList:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_privateCompileGetByIdChainList\n");
            JIT *                               jit(reinterpret_cast<JIT *>(payload->recvArgument()));
            StructureStubInfo *                 stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            PolymorphicAccessStructureList *    prototypeStructures(reinterpret_cast<PolymorphicAccessStructureList *>(payload->recvArgument()));
            int                                 currentIndex(static_cast<int>(payload->recvArgument()));
            Structure *                         structure(reinterpret_cast<Structure *>(payload->recvArgument()));
            StructureChain *                    chain(reinterpret_cast<StructureChain *>(payload->recvArgument()));
            size_t                              count(static_cast<size_t>(payload->recvArgument()));
            Identifier const *                  ident(reinterpret_cast<Identifier const *>(payload->recvArgument()));
            PropertySlot const *                slot(payload->recvPOD<PropertySlot>());
            size_t                              cachedOffset(static_cast<size_t>(payload->recvArgument()));
            CallFrame *                         callFrame(reinterpret_cast<CallFrame *>(payload->recvArgument()));
            jit->privateCompileGetByIdChainList(stubInfo, prototypeStructures, currentIndex, structure, chain, count, *ident, *slot, cachedOffset, callFrame);
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_privateCompileGetByIdChainList DONE\n");
            break;
        }
    case e_JIT_privateCompileGetByIdProto:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_privateCompileGetByIdProto\n");
            JIT *                               jit(reinterpret_cast<JIT *>(payload->recvArgument()));
            StructureStubInfo *                 stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            Structure *                         structure(reinterpret_cast<Structure *>(payload->recvArgument()));
            Structure *                         prototypeStructure(reinterpret_cast<Structure *>(payload->recvArgument()));
            Identifier const *                  ident(reinterpret_cast<Identifier const *>(payload->recvArgument()));
            PropertySlot const *                slot(payload->recvPOD<PropertySlot>());
            size_t                              cachedOffset(static_cast<size_t>(payload->recvArgument()));
            void *                              returnAddress(reinterpret_cast<void *>(payload->recvArgument()));
            CallFrame *                         callFrame(reinterpret_cast<CallFrame *>(payload->recvArgument()));
            jit->privateCompileGetByIdProto(stubInfo, structure, prototypeStructure, *ident, *slot, cachedOffset, ReturnAddressPtr(returnAddress), callFrame);
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_privateCompileGetByIdProto DONE\n");
            break;
        }
    case e_JIT_privateCompileGetByIdProtoList:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_privateCompileGetByIdProtoList\n");
            JIT *                               jit(reinterpret_cast<JIT *>(payload->recvArgument()));
            StructureStubInfo *                 stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            PolymorphicAccessStructureList *    prototypeStructures(reinterpret_cast<PolymorphicAccessStructureList *>(payload->recvArgument()));
            int                                 currentIndex(static_cast<int>(payload->recvArgument()));
            Structure *                         structure(reinterpret_cast<Structure *>(payload->recvArgument()));
            Structure *                         prototypeStructure(reinterpret_cast<Structure *>(payload->recvArgument()));
            Identifier const *                  ident(reinterpret_cast<Identifier const *>(payload->recvArgument()));
            PropertySlot const *                slot(payload->recvPOD<PropertySlot>());
            size_t                              cachedOffset(static_cast<size_t>(payload->recvArgument()));
            CallFrame *                         callFrame(reinterpret_cast<CallFrame *>(payload->recvArgument()));
            jit->privateCompileGetByIdProtoList(stubInfo, prototypeStructures, currentIndex, structure, prototypeStructure, *ident, *slot, cachedOffset, callFrame);
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_privateCompileGetByIdProtoList DONE\n");
            break;
        }
    case e_JIT_privateCompileGetByIdSelfList:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_privateCompileGetByIdSelfList\n");
            JIT *                               jit(reinterpret_cast<JIT *>(payload->recvArgument()));
            StructureStubInfo *                 stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            PolymorphicAccessStructureList *    polymorphicStructures(reinterpret_cast<PolymorphicAccessStructureList *>(payload->recvArgument()));
            int                                 currentIndex(static_cast<int>(payload->recvArgument()));
            Structure *                         structure(reinterpret_cast<Structure *>(payload->recvArgument()));
            Identifier const *                  ident(reinterpret_cast<Identifier const *>(payload->recvArgument()));
            PropertySlot const *                slot(payload->recvPOD<PropertySlot>());
            size_t                              cachedOffset(static_cast<size_t>(payload->recvArgument()));
            jit->privateCompileGetByIdSelfList(stubInfo, polymorphicStructures, currentIndex, structure, *ident, *slot, cachedOffset);
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_privateCompileGetByIdSelfList DONE\n");
            break;
        }
    case e_JIT_privateCompilePatchGetArrayLength:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_privateCompilePatchGetArrayLength\n");
            JIT *                               jit(reinterpret_cast<JIT *>(payload->recvArgument()));
            void *                              returnAddress(reinterpret_cast<void *>(payload->recvArgument()));
            jit->privateCompilePatchGetArrayLength(ReturnAddressPtr(returnAddress));
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_privateCompilePatchGetArrayLength DONE\n");
            break;
        }
    case e_JIT_privateCompilePutByIdTransition:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_privateCompilePutByIdTransition\n");
            JIT *                               jit(reinterpret_cast<JIT *>(payload->recvArgument()));
            StructureStubInfo *                 stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            Structure *                         oldStructure(reinterpret_cast<Structure *>(payload->recvArgument()));
            Structure *                         newStructure(reinterpret_cast<Structure *>(payload->recvArgument()));
            size_t                              cachedOffset(static_cast<size_t>(payload->recvArgument()));
            StructureChain *                    chain(reinterpret_cast<StructureChain *>(payload->recvArgument()));
            void *                              returnAddress(reinterpret_cast<void *>(payload->recvArgument()));
            bool                                direct(!!payload->recvArgument());
            jit->privateCompilePutByIdTransition(stubInfo, oldStructure, newStructure, cachedOffset, chain, ReturnAddressPtr(returnAddress), direct);
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_privateCompilePutByIdTransition DONE\n");
            break;
        }
    case e_JIT_resetPatchGetById:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_resetPatchGetById\n");
            RepatchBuffer * const               repatchBuffer(reinterpret_cast<RepatchBuffer *>(payload->recvArgument()));
            StructureStubInfo *                 stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            JIT::resetPatchGetById(*repatchBuffer, stubInfo);
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_resetPatchGetById DONE\n");
            break;
        }
    case e_JIT_resetPatchPutById:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_resetPatchPutById\n");
            RepatchBuffer * const               repatchBuffer(reinterpret_cast<RepatchBuffer *>(payload->recvArgument()));
            StructureStubInfo *                 stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            JIT::resetPatchPutById(*repatchBuffer, stubInfo);
            LOG(DetachedJIT, "[Bridge-Compiler] e_JIT_resetPatchPutById DONE\n");
            break;
        }
    case e_MacroAssembler_repatchCall:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_MacroAssembler_repatchCall\n");
            void *                              call(reinterpret_cast<void *>(payload->recvArgument()));
            void *                              destination(reinterpret_cast<void *>(payload->recvArgument()));
            MacroAssembler::repatchCall(CodeLocationCall(call), FunctionPtr(destination));
            LOG(DetachedJIT, "[Bridge-Compiler] e_MacroAssembler_repatchCall DONE\n");
            break;
        }
    case e_MacroAssembler_repatchJump:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_MacroAssembler_repatchJump\n");
            void *                              jump(reinterpret_cast<void *>(payload->recvArgument()));
            void *                              destination(reinterpret_cast<void *>(payload->recvArgument()));
            MacroAssembler::repatchJump(CodeLocationJump(jump), CodeLocationLabel(destination));
            LOG(DetachedJIT, "[Bridge-Compiler] e_MacroAssembler_repatchJump DONE\n");
            break;
        }
    case e_MacroAssembler_repatchNearCall:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_MacroAssembler_repatchNearCall\n");
            void *                              nearCall(reinterpret_cast<void *>(payload->recvArgument()));
            void *                              destination(reinterpret_cast<void *>(payload->recvArgument()));
            MacroAssembler::repatchNearCall(CodeLocationNearCall(nearCall), CodeLocationLabel(destination));
            LOG(DetachedJIT, "[Bridge-Compiler] e_MacroAssembler_repatchNearCall DONE\n");
            break;
        }
    case e_MacroAssembler_repatchPointer:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_MacroAssembler_repatchPointer\n");
            void *                              dataLabelPointer(reinterpret_cast<void *>(payload->recvArgument()));
            void *                              value(reinterpret_cast<void *>(payload->recvArgument()));
            MacroAssembler::repatchPointer(CodeLocationDataLabelPtr(dataLabelPointer), value);
            LOG(DetachedJIT, "[Bridge-Compiler] e_MacroAssembler_repatchPointer DONE\n");
            break;
        }
    case e_RepatchBuffer_relinkCallToFuncPtr:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_RepatchBuffer_relinkCallToFuncPtr\n");
            void *                              call(reinterpret_cast<void *>(payload->recvArgument()));
            void *                              destination(reinterpret_cast<void *>(payload->recvArgument()));
            MacroAssembler::repatchCall(CodeLocationCall(call), FunctionPtr(destination));
            LOG(DetachedJIT, "[Bridge-Compiler] e_RepatchBuffer_relinkCallToFuncPtr DONE\n");
            break;
        }
    case e_RepatchBuffer_relinkJumpToLabel:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_RepatchBuffer_relinkNearCallToCodePtr\n");
            void *                              jump(reinterpret_cast<void *>(payload->recvArgument()));
            void *                              destination(reinterpret_cast<void *>(payload->recvArgument()));
            MacroAssembler::repatchJump(CodeLocationJump(jump), CodeLocationLabel(destination));
            LOG(DetachedJIT, "[Bridge-Compiler] e_RepatchBuffer_relinkNearCallToCodePtr DONE\n");
            break;
        }
    case e_RepatchBuffer_relinkNearCallToCodePtr:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_RepatchBuffer_relinkNearCallToCodePtr\n");
            void *                              nearCall(reinterpret_cast<void *>(payload->recvArgument()));
            void *                              destination(reinterpret_cast<void *>(payload->recvArgument()));
            MacroAssembler::repatchNearCall(CodeLocationNearCall(nearCall), CodeLocationLabel(RepatchBuffer::CodePtr(destination)));
            LOG(DetachedJIT, "[Bridge-Compiler] e_RepatchBuffer_relinkNearCallToCodePtr DONE\n");
            break;
        }
    case e_RepatchBuffer_repatchLabelToVoidPtr:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_RepatchBuffer_repatchLabelToVoidPtr\n");
            void *                              dataLabelPtr(reinterpret_cast<void *>(payload->recvArgument()));
            void *                              value(reinterpret_cast<void *>(payload->recvArgument()));
            MacroAssembler::repatchPointer(CodeLocationDataLabelPtr(dataLabelPtr), value);
            LOG(DetachedJIT, "[Bridge-Compiler] e_RepatchBuffer_repatchLabelToVoidPtr DONE\n");
            break;
        }
    case e_RepatchBuffer_repatchLabelCompactToInt:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_RepatchBuffer_repatchLabelCompactToInt\n");
            void *                              dataLabelCompact(reinterpret_cast<void *>(payload->recvArgument()));
            int32_t                             value(static_cast<int32_t>(payload->recvArgument()));
            MacroAssembler::repatchCompact(CodeLocationDataLabelCompact(dataLabelCompact), value);
            LOG(DetachedJIT, "[Bridge-Compiler] e_RepatchBuffer_repatchLabelCompactToInt DONE\n");
            break;
        }
    case e_RepatchBuffer_repatchLabel32ToInt:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_RepatchBuffer_repatchLabel32ToInt\n");
            void *                              dataLabel32(reinterpret_cast<void *>(payload->recvArgument()));
            int32_t                             value(static_cast<int32_t>(payload->recvArgument()));
            MacroAssembler::repatchInt32(CodeLocationDataLabel32(dataLabel32), value);
            LOG(DetachedJIT, "[Bridge-Compiler] e_RepatchBuffer_repatchLabel32ToInt DONE\n");
            break;
        }
    case e_Yarr_jitCompile:
        {
            LOG(DetachedJIT, "[Bridge-Compiler] e_Yarr_jitCompile\n");
            Yarr::YarrPattern * const           pattern(reinterpret_cast<Yarr::YarrPattern *>(payload->recvArgument()));
            Yarr::YarrCharSize                  charSize(static_cast<Yarr::YarrCharSize>(payload->recvArgument()));
            JSGlobalData * const                globalData(reinterpret_cast<JSGlobalData *>(payload->recvArgument()));
            Yarr::YarrCodeBlock * const         jitObject(reinterpret_cast<Yarr::YarrCodeBlock *>(payload->recvArgument()));
            Yarr::YarrJITCompileMode            mode(static_cast<Yarr::YarrJITCompileMode>(payload->recvArgument()));
            Yarr::jitCompile(*pattern, charSize, globalData, *jitObject, mode);
            LOG(DetachedJIT, "[Bridge-Compiler] e_Yarr_jitCompile DONE\n");
            break;
        }
    default:
        {
            __builtin_trap();  // security breach?
        }
    }

    return;
}

uintptr_t JSCBridge::requestCompilerTask(CompilerFunction compilerFunction, JIT *)
{
    // you MUST NOT call this from the JIT compiler process
    __builtin_trap();
    return -1; // just to silence the compiler...
}

} // namespace JSC

#endif // #if ENABLE(JIT) && ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT

