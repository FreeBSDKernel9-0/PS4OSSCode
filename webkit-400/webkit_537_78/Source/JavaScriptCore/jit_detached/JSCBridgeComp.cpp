// Copyright (C) 2012 Sony Interactive Entertainment Inc.
// All Rights Reserved.

#include "config.h"

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
#include "DFGGraph.h"
#include "DFGJITCompiler.h"
#include "DFGOSRExitCompiler.h"
#include "DFGRepatch.h"
#include "DFGThunks.h"
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
#include "JSCBridge.h"
#include "JSCJSValueInlines.h"
#include "JSFunction.h"
#include "JSGlobalObject.h"
#include "LinkBuffer.h"
#if ENABLE(LLINT)
#include "LLIntThunks.h"
#endif
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

namespace {

#if !LOG_DISABLED
    char const * toString(JSC::JSCBridge::CompilerFunction func)
    {
        switch (func) {
#define CASE_CONVERT_ENUM_TO_STRING(c) case JSC::JSCBridge::c: return #c
        CASE_CONVERT_ENUM_TO_STRING(e_absThunkGenerator);
        CASE_CONVERT_ENUM_TO_STRING(e_ceilThunkGenerator);
        CASE_CONVERT_ENUM_TO_STRING(e_charAtThunkGenerator);
        CASE_CONVERT_ENUM_TO_STRING(e_charCodeAtThunkGenerator);
        CASE_CONVERT_ENUM_TO_STRING(e_charToString);
        CASE_CONVERT_ENUM_TO_STRING(e_expThunkGenerator);
        CASE_CONVERT_ENUM_TO_STRING(e_floorThunkGenerator);
        CASE_CONVERT_ENUM_TO_STRING(e_fromCharCodeThunkGenerator);
        CASE_CONVERT_ENUM_TO_STRING(e_imulThunkGenerator);
        CASE_CONVERT_ENUM_TO_STRING(e_linkCallGenerator);
        CASE_CONVERT_ENUM_TO_STRING(e_linkConstructGenerator);
        CASE_CONVERT_ENUM_TO_STRING(e_logThunkGenerator);
        CASE_CONVERT_ENUM_TO_STRING(e_nativeCallGenerator);
        CASE_CONVERT_ENUM_TO_STRING(e_nativeConstructGenerator);
        CASE_CONVERT_ENUM_TO_STRING(e_powThunkGenerator);
        CASE_CONVERT_ENUM_TO_STRING(e_roundThunkGenerator);
        CASE_CONVERT_ENUM_TO_STRING(e_sqrtThunkGenerator);
        CASE_CONVERT_ENUM_TO_STRING(e_stringLengthTrampolineGenerator);
        CASE_CONVERT_ENUM_TO_STRING(e_DFG_compile);
        CASE_CONVERT_ENUM_TO_STRING(e_DFG_compileFunction);
        CASE_CONVERT_ENUM_TO_STRING(e_DFG_compileOSRExit);
        CASE_CONVERT_ENUM_TO_STRING(e_DFG_emitPutReplaceStub);
        CASE_CONVERT_ENUM_TO_STRING(e_DFG_emitPutTransitionStub);
        CASE_CONVERT_ENUM_TO_STRING(e_DFG_generateProtoChainAccessStub);
        CASE_CONVERT_ENUM_TO_STRING(e_DFG_linkClosureCallThunkGenerator);
        CASE_CONVERT_ENUM_TO_STRING(e_DFG_linkClosureCall);
        CASE_CONVERT_ENUM_TO_STRING(e_DFG_linkForThunkGenerator);
        CASE_CONVERT_ENUM_TO_STRING(e_DFG_repatchByIdSelfAccess);
        CASE_CONVERT_ENUM_TO_STRING(e_DFG_throwExceptionFromCall);
        CASE_CONVERT_ENUM_TO_STRING(e_DFG_tryBuildGetByIDList);
        CASE_CONVERT_ENUM_TO_STRING(e_DFG_tryCacheGetByID);
        CASE_CONVERT_ENUM_TO_STRING(e_DFG_virtualForThunkGenerator);
        CASE_CONVERT_ENUM_TO_STRING(e_JIT_compile);
        CASE_CONVERT_ENUM_TO_STRING(e_JIT_compileCTINativeCall);
        CASE_CONVERT_ENUM_TO_STRING(e_JIT_compileClosureCall);
        CASE_CONVERT_ENUM_TO_STRING(e_JIT_compileGetByIdChain);
        CASE_CONVERT_ENUM_TO_STRING(e_JIT_compileGetByIdChainList);
        CASE_CONVERT_ENUM_TO_STRING(e_JIT_compileGetByIdProto);
        CASE_CONVERT_ENUM_TO_STRING(e_JIT_compileGetByIdProtoList);
        CASE_CONVERT_ENUM_TO_STRING(e_JIT_compileGetByIdSelfList);
        CASE_CONVERT_ENUM_TO_STRING(e_JIT_compileGetByVal);
        CASE_CONVERT_ENUM_TO_STRING(e_JIT_compilePatchGetArrayLength);
        CASE_CONVERT_ENUM_TO_STRING(e_JIT_compilePutByIdTransition);
        CASE_CONVERT_ENUM_TO_STRING(e_JIT_compilePutByVal);
        CASE_CONVERT_ENUM_TO_STRING(e_JIT_linkFor);
        CASE_CONVERT_ENUM_TO_STRING(e_JIT_linkSlowCall);
        CASE_CONVERT_ENUM_TO_STRING(e_JIT_patchGetByIdSelf);
        CASE_CONVERT_ENUM_TO_STRING(e_JIT_patchPutByIdReplace);
        CASE_CONVERT_ENUM_TO_STRING(e_JIT_resetPatchGetById);
        CASE_CONVERT_ENUM_TO_STRING(e_JIT_resetPatchPutById);
        CASE_CONVERT_ENUM_TO_STRING(e_LLINT_generateThunk);
        CASE_CONVERT_ENUM_TO_STRING(e_ctiPatchCallReturnAddrCodePtr);
        CASE_CONVERT_ENUM_TO_STRING(e_ctiPatchCallReturnAddrFunctionPtr);
        CASE_CONVERT_ENUM_TO_STRING(e_MacroAssembler_repatchCallFunctionPtr);
        CASE_CONVERT_ENUM_TO_STRING(e_MacroAssembler_repatchCompact);
        CASE_CONVERT_ENUM_TO_STRING(e_MacroAssembler_repatchInt32);
        CASE_CONVERT_ENUM_TO_STRING(e_MacroAssembler_repatchJump);
        CASE_CONVERT_ENUM_TO_STRING(e_MacroAssembler_repatchNearCall);
        CASE_CONVERT_ENUM_TO_STRING(e_MacroAssembler_repatchPointer);
        CASE_CONVERT_ENUM_TO_STRING(e_MacroAssembler_replaceWithAddressComputation);
        CASE_CONVERT_ENUM_TO_STRING(e_MacroAssembler_replaceWithJump);
        CASE_CONVERT_ENUM_TO_STRING(e_MacroAssembler_revertJumpReplacementToBranch);
        CASE_CONVERT_ENUM_TO_STRING(e_MacroAssembler_revertJumpReplacementToPatchableBranch);
        CASE_CONVERT_ENUM_TO_STRING(e_Yarr_jitCompile);
#undef CASE_CONVERT_ENUM_TO_STRING
        default: __debugbreak(); break;
        }
        return "<unknown function>";
    }
#endif
}

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
#if ENABLE(LLINT)
	CTI_STUB_ENTRIES_LLINT;
#endif
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
        /*DEBUG_LOG("(vm address) %lx   (comp address) %lx : %s\n", vmData->m_##classname##_classinfo, (uintptr_t)&JSC::classname::s_info, #classname);*/ \
    }
    CLASSINFO_STUB_ENTRIES;
#undef  CLASSINFO_STUB_ENTRY

    for (size_t i = 0; i < vmData->m_runtimeClassInfoCount; ++i) {
        fixupClassInfo(reinterpret_cast<ClassInfo*>(&(vmData->m_runtimeClassInfo[i].m_data[0])));
        //DEBUG_LOG("(vm address) %lx   (comp address) %lx\n", vmData->m_runtimeClassInfo[i].m_classInfoPtr, (uintptr_t)&(vmData->m_runtimeClassInfo[i].m_data[0]));
    }

    // These are needed by the ThunkGenerators, Yarr, DFG JIT, etc...
    JSC::RemoteStubs::oneConstant               = vmData->m_oneConstant;
    JSC::RemoteStubs::zeroConstant              = vmData->m_zeroConstant;
    JSC::RemoteStubs::halfConstant              = vmData->m_halfConstant;
    JSC::RemoteStubs::negativeHalfConstant      = vmData->m_negativeHalfConstant;
    JSC::RemoteStubs::negativeZeroConstant      = vmData->m_negativeZeroConstant;
    JSC::RemoteStubs::NaN                       = vmData->m_NaN;
    JSC::RemoteStubs::twoToThe32                = vmData->m_twoToThe32;
    JSC::RemoteStubs::byteMax                   = vmData->m_byteMax;
    JSC::Yarr::RemoteStubs::regExp_spacesData   = reinterpret_cast<char const *>(vmData->m_regExpSpacesData);
    JSC::Yarr::RemoteStubs::regExp_wordcharData = reinterpret_cast<char const *>(vmData->m_regExpWordCharData);

    // notify that all compiler data the VM needs are ready
    ringDoorbell();
}

void JSCBridge::initializeFromCompiler(char const * vmTestApp, char ** vmTestAppArgs, JITBridge::RestartData const * restartData)
{
    if (m_processType != ProcessUnknown) {
        __builtin_trap();
    }

    m_processType = ProcessCompiler;
    m_sharedBridge = JITBridge::initializeFromCompiler(vmTestApp, vmTestAppArgs, restartData);

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
//#define CLASSINFO_STUB_ENTRY(classname) \
//    if ((ci == vmData->m_##classname##_classinfo) || (ci == reinterpret_cast<uintptr_t>(&JSC::classname::s_info))) { return &JSC::classname::s_info; }
//    CLASSINFO_STUB_ENTRIES;
//#undef CLASSINFO_STUB_ENTRY

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

    Payload * const payload(&m_sharedData->m_payload);

    LOG(DetachedJIT, "[Bridge-Compiler] %s\n", toString(m_sharedData->m_payload.m_compilerFunction));

    switch (m_sharedData->m_payload.m_compilerFunction) {

#define DEFINE_THUNKGENERATOR_CASE(generator) \
    case e_##generator: \
    { \
        VM *         vm(reinterpret_cast<VM *>(payload->recvArgument())); \
        JIT::CodeRef codeRef(generator(vm)); \
        payload->m_retval = reinterpret_cast<uintptr_t>(sharedNew<MacroAssemblerCodeRef>(codeRef)); \
        break; \
    }
    DEFINE_THUNKGENERATOR_CASE(absThunkGenerator);
    DEFINE_THUNKGENERATOR_CASE(ceilThunkGenerator);
    DEFINE_THUNKGENERATOR_CASE(charAtThunkGenerator);
    DEFINE_THUNKGENERATOR_CASE(charCodeAtThunkGenerator);
    DEFINE_THUNKGENERATOR_CASE(expThunkGenerator);
    DEFINE_THUNKGENERATOR_CASE(floorThunkGenerator);
    DEFINE_THUNKGENERATOR_CASE(fromCharCodeThunkGenerator);
    DEFINE_THUNKGENERATOR_CASE(imulThunkGenerator);
    DEFINE_THUNKGENERATOR_CASE(linkCallGenerator);
    DEFINE_THUNKGENERATOR_CASE(linkConstructGenerator);
    DEFINE_THUNKGENERATOR_CASE(logThunkGenerator);
    DEFINE_THUNKGENERATOR_CASE(nativeCallGenerator);
    DEFINE_THUNKGENERATOR_CASE(nativeConstructGenerator);
    DEFINE_THUNKGENERATOR_CASE(powThunkGenerator);
    DEFINE_THUNKGENERATOR_CASE(roundThunkGenerator);
    DEFINE_THUNKGENERATOR_CASE(sqrtThunkGenerator);
    DEFINE_THUNKGENERATOR_CASE(stringLengthTrampolineGenerator);

    case e_ctiPatchCallReturnAddrCodePtr:
        {
            CodeBlock * codeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            void *      returnAddress(reinterpret_cast<void *>(payload->recvArgument()));
            void *      newCalleeFunction(reinterpret_cast<void *>(payload->recvArgument()));
            ctiPatchCallByReturnAddress(codeBlock, ReturnAddressPtr(returnAddress), MacroAssemblerCodePtr(newCalleeFunction));
            break;
        }
    case e_ctiPatchCallReturnAddrFunctionPtr:
        {
            CodeBlock * codeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            void *      returnAddress(reinterpret_cast<void *>(payload->recvArgument()));
            void *      newCalleeFunction(reinterpret_cast<void *>(payload->recvArgument()));
            ctiPatchCallByReturnAddress(codeBlock, ReturnAddressPtr(returnAddress), FunctionPtr(newCalleeFunction));
            break;
        }
    case e_DFG_compile:
        {
            DFG::Graph *     dfg(reinterpret_cast<DFG::Graph*>(payload->recvArgument()));
            JITCode *        entry(reinterpret_cast<JITCode*>(payload->recvArgument()));
            DFG::JITCompiler dataFlowJIT(*dfg);
            payload->m_retval = static_cast<uintptr_t>(dataFlowJIT.compile(*entry));
            break;
        }
    case e_DFG_compileFunction:
        {
            DFG::Graph *            dfg(reinterpret_cast<DFG::Graph*>(payload->recvArgument()));
            JITCode *               entry(reinterpret_cast<JITCode*>(payload->recvArgument()));
            MacroAssemblerCodePtr * entryWithArityCheck(reinterpret_cast<MacroAssemblerCodePtr*>(payload->recvArgument()));
            DFG::JITCompiler dataFlowJIT(*dfg);
            payload->m_retval = static_cast<uintptr_t>(dataFlowJIT.compileFunction(*entry, *entryWithArityCheck));
            break;
        }
    case e_DFG_compileOSRExit:
        {
            ExecState * exec(reinterpret_cast<ExecState*>(payload->recvArgument()));
            DFG::compileOSRExit(exec);
            break;
        }
    case e_DFG_emitPutReplaceStub:
        {
            ExecState *              exec(reinterpret_cast<ExecState*>(payload->recvArgument()));
            JSValue                  baseValue(JSValue::decode(static_cast<EncodedJSValue>(payload->recvArgument())));
            Identifier *             ident(reinterpret_cast<Identifier*>(payload->recvArgument()));
            PutPropertySlot const *  slot(payload->recvPOD<PutPropertySlot>());
            StructureStubInfo *      stubInfo(reinterpret_cast<StructureStubInfo*>(payload->recvArgument()));
            PutKind                  putKind(static_cast<PutKind>(payload->recvArgument()));
            Structure *              structure(reinterpret_cast<Structure*>(payload->recvArgument()));
            void *                   failureLabel(reinterpret_cast<void*>(payload->recvArgument()));
            RefPtr<JITStubRoutine> * stubRoutine(reinterpret_cast<RefPtr<JITStubRoutine>*>(payload->recvArgument()));
            DFG::emitPutReplaceStub(exec, baseValue, *ident, *slot, *stubInfo, putKind, structure, CodeLocationLabel(failureLabel), *stubRoutine);
            break;
        }
    case e_DFG_emitPutTransitionStub:
        {
            ExecState *              exec(reinterpret_cast<ExecState*>(payload->recvArgument()));
            JSValue                  baseValue(JSValue::decode(static_cast<EncodedJSValue>(payload->recvArgument())));
            Identifier *             ident(reinterpret_cast<Identifier*>(payload->recvArgument()));
            PutPropertySlot const *  slot(payload->recvPOD<PutPropertySlot>());
            StructureStubInfo *      stubInfo(reinterpret_cast<StructureStubInfo*>(payload->recvArgument()));
            PutKind                  putKind(static_cast<PutKind>(payload->recvArgument()));
            Structure *              structure(reinterpret_cast<Structure*>(payload->recvArgument()));
            Structure *              oldStructure(reinterpret_cast<Structure*>(payload->recvArgument()));
            StructureChain *         prototypeChain(reinterpret_cast<StructureChain*>(payload->recvArgument()));
            void *                   failureLabel(reinterpret_cast<void*>(payload->recvArgument()));
            RefPtr<JITStubRoutine> * stubRoutine(reinterpret_cast<RefPtr<JITStubRoutine>*>(payload->recvArgument()));
            DFG::emitPutTransitionStub(exec, baseValue, *ident, *slot, *stubInfo, putKind, structure, oldStructure, prototypeChain, CodeLocationLabel(failureLabel), *stubRoutine);
            break;
        }
    case e_DFG_generateProtoChainAccessStub:
        {
            ExecState *              exec(reinterpret_cast<ExecState*>(payload->recvArgument()));
            StructureStubInfo *      stubInfo(reinterpret_cast<StructureStubInfo*>(payload->recvArgument()));
            StructureChain *         chain(reinterpret_cast<StructureChain*>(payload->recvArgument()));
            size_t                   count(static_cast<size_t>(payload->recvArgument()));
            PropertyOffset           offset(static_cast<PropertyOffset>(payload->recvArgument()));
            Structure *              structure(reinterpret_cast<Structure*>(payload->recvArgument()));
            void *                   successLabel(reinterpret_cast<void*>(payload->recvArgument()));
            void *                   slowCaseLabel(reinterpret_cast<void*>(payload->recvArgument()));
            RefPtr<JITStubRoutine> * stubRoutine(reinterpret_cast<RefPtr<JITStubRoutine>*>(payload->recvArgument()));
            DFG::generateProtoChainAccessStub(exec, *stubInfo, chain, count, offset, structure, CodeLocationLabel(successLabel), CodeLocationLabel(slowCaseLabel), *stubRoutine);
            break;
        }
    case e_DFG_linkClosureCallThunkGenerator:
        {
            VM *                  vm(reinterpret_cast<VM*>(payload->recvArgument()));
            MacroAssemblerCodeRef codeRef(DFG::linkClosureCallThunkGenerator(vm));
            payload->m_retval = reinterpret_cast<uintptr_t>(sharedNew<MacroAssemblerCodeRef>(codeRef));
            break;
        }
    case e_DFG_linkClosureCall:
        {   
            ExecState *             exec(reinterpret_cast<ExecState*>(payload->recvArgument()));
            CallLinkInfo *          callLinkInfo(reinterpret_cast<CallLinkInfo*>(payload->recvArgument()));
            CodeBlock *             calleeCodeBlock(reinterpret_cast<CodeBlock*>(payload->recvArgument()));
            Structure *             structure(reinterpret_cast<Structure*>(payload->recvArgument()));
            ExecutableBase *        executable(reinterpret_cast<ExecutableBase*>(payload->recvArgument()));
            MacroAssemblerCodePtr * codePtr(reinterpret_cast<MacroAssemblerCodePtr *>(payload->recvArgument()));
            DFG::dfgLinkClosureCall(exec, *callLinkInfo, calleeCodeBlock, structure, executable, *codePtr);
            break;
        }
    case e_DFG_linkForThunkGenerator:
        {
            VM *                   vm(reinterpret_cast<VM*>(payload->recvArgument()));
            CodeSpecializationKind kind(static_cast<CodeSpecializationKind>(payload->recvArgument()));
            MacroAssemblerCodeRef codeRef(DFG::linkForThunkGenerator(vm, kind));
            payload->m_retval = reinterpret_cast<uintptr_t>(sharedNew<MacroAssemblerCodeRef>(codeRef));
            break;
        }
    case e_DFG_repatchByIdSelfAccess:
        {
            CodeBlock *         codeBlock(reinterpret_cast<CodeBlock*>(payload->recvArgument()));
            StructureStubInfo * stubInfo(reinterpret_cast<StructureStubInfo*>(payload->recvArgument()));
            Structure *         structure(reinterpret_cast<Structure*>(payload->recvArgument()));
            PropertyOffset      offset(static_cast<PropertyOffset>(payload->recvArgument()));
            void *              slowPathFunction(reinterpret_cast<void *>(payload->recvArgument()));
            bool                compact(static_cast<bool>(payload->recvArgument()));
            DFG::dfgRepatchByIdSelfAccess(codeBlock, *stubInfo, structure, offset, FunctionPtr(slowPathFunction), compact);
            break;
        }
    case e_DFG_throwExceptionFromCall:
        {
            VM * vm(reinterpret_cast<VM*>(payload->recvArgument()));
            MacroAssemblerCodeRef codeRef(DFG::throwExceptionFromCallSlowPathGenerator(vm));
            payload->m_retval = reinterpret_cast<uintptr_t>(sharedNew<MacroAssemblerCodeRef>(codeRef));
            break;
        }
    case e_DFG_tryBuildGetByIDList:
        {
            ExecState *          exec(reinterpret_cast<ExecState*>(payload->recvArgument()));
            JSValue              baseValue(JSValue::decode(static_cast<EncodedJSValue>(payload->recvArgument())));
            Identifier const *   ident(reinterpret_cast<Identifier const *>(payload->recvArgument()));
            PropertySlot const * slot(payload->recvPOD<PropertySlot>());
            StructureStubInfo *  stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            payload->m_retval = static_cast<uintptr_t>(DFG::tryBuildGetByIDList(exec, baseValue, *ident, *slot, *stubInfo));
            break;
        }
    case e_DFG_tryCacheGetByID:
        {
            ExecState *          exec(reinterpret_cast<ExecState*>(payload->recvArgument()));
            JSValue              baseValue(JSValue::decode(static_cast<EncodedJSValue>(payload->recvArgument())));
            Identifier const *   propertyName(reinterpret_cast<Identifier const *>(payload->recvArgument()));
            PropertySlot const * slot(payload->recvPOD<PropertySlot>());
            StructureStubInfo *  stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            payload->m_retval = static_cast<uintptr_t>(DFG::tryCacheGetByID(exec, baseValue, *propertyName, *slot, *stubInfo));
            break;
        }
    case e_DFG_virtualForThunkGenerator:
        {
            VM *                   vm(reinterpret_cast<VM*>(payload->recvArgument()));
            CodeSpecializationKind kind(static_cast<CodeSpecializationKind>(payload->recvArgument()));
            MacroAssemblerCodeRef codeRef(DFG::virtualForThunkGenerator(vm, kind));
            payload->m_retval = reinterpret_cast<uintptr_t>(sharedNew<MacroAssemblerCodeRef>(codeRef));
            break;
        }
    case e_JIT_compile:
        {
            VM *                 vm(reinterpret_cast<VM *>(payload->recvArgument()));
            CodeBlock *          codeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            JITCompilationEffort effort(static_cast<JITCompilationEffort>(payload->recvArgument()));
            JIT::CodePtr *       functionEntryArityCheck (reinterpret_cast<JIT::CodePtr *>(payload->recvArgument()));
            payload->m_retval = reinterpret_cast<uintptr_t>(sharedNew<JITCode>(JIT::compile(vm, codeBlock, effort, functionEntryArityCheck)));
            break;
        }
    case e_JIT_compileClosureCall:
        {
            VM *                    vm(reinterpret_cast<VM *>(payload->recvArgument()));
            CallLinkInfo *          callLinkInfo(reinterpret_cast<CallLinkInfo *>(payload->recvArgument()));
            CodeBlock *             callerCodeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            CodeBlock *             calleeCodeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            Structure *             expectedStructure(reinterpret_cast<Structure *>(payload->recvArgument()));
            ExecutableBase *        expectedExecutable(reinterpret_cast<ExecutableBase *>(payload->recvArgument()));
            MacroAssemblerCodePtr * codePtr(reinterpret_cast<MacroAssemblerCodePtr *>(payload->recvArgument()));
            JIT::compileClosureCall(vm, callLinkInfo, callerCodeBlock, calleeCodeBlock, expectedStructure, expectedExecutable, *codePtr);
            break;
        }
    case e_JIT_compileCTINativeCall:
        {
            VM *           vm(reinterpret_cast<VM *>(payload->recvArgument()));
            NativeFunction func(reinterpret_cast<NativeFunction>(payload->recvArgument()));
            JIT::CodeRef   codeRef(JIT::compileCTINativeCall(vm, func));
            payload->m_retval = reinterpret_cast<uintptr_t>(sharedNew<MacroAssemblerCodeRef>(codeRef));
            break;
        }
    case e_JIT_compileGetByIdChain:
        {
            VM *                 vm(reinterpret_cast<VM *>(payload->recvArgument()));
            CallFrame *          callFrame(reinterpret_cast<CallFrame *>(payload->recvArgument()));
            CodeBlock *          codeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            StructureStubInfo *  stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            Structure *          structure(reinterpret_cast<Structure *>(payload->recvArgument()));
            StructureChain *     chain(reinterpret_cast<StructureChain *>(payload->recvArgument()));
            size_t               count(static_cast<size_t>(payload->recvArgument()));
            Identifier const *   ident(reinterpret_cast<Identifier const *>(payload->recvArgument()));
            PropertySlot const * slot(payload->recvPOD<PropertySlot>());
            PropertyOffset       cachedOffset(static_cast<PropertyOffset>(payload->recvArgument()));
            void *               returnAddress(reinterpret_cast<void *>(payload->recvArgument()));
            JIT::compileGetByIdChain(vm, callFrame, codeBlock, stubInfo, structure, chain, count, *ident, *slot, cachedOffset, ReturnAddressPtr(returnAddress));
            break;
        }
    case e_JIT_compileGetByIdChainList:
        {
            VM *                             vm(reinterpret_cast<VM *>(payload->recvArgument()));
            CallFrame *                      callFrame(reinterpret_cast<CallFrame *>(payload->recvArgument()));
            CodeBlock *                      codeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            StructureStubInfo *              stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            PolymorphicAccessStructureList * prototypeStructureList(reinterpret_cast<PolymorphicAccessStructureList *>(payload->recvArgument()));
            int                              currentIndex(static_cast<int>(payload->recvArgument()));
            Structure *                      structure(reinterpret_cast<Structure *>(payload->recvArgument()));
            StructureChain *                 chain(reinterpret_cast<StructureChain *>(payload->recvArgument()));
            size_t                           count(static_cast<size_t>(payload->recvArgument()));
            Identifier const *               ident(reinterpret_cast<Identifier const *>(payload->recvArgument()));
            PropertySlot const *             slot(payload->recvPOD<PropertySlot>());
            PropertyOffset                   cachedOffset(static_cast<PropertyOffset>(payload->recvArgument()));
            JIT::compileGetByIdChainList(vm, callFrame, codeBlock, stubInfo, prototypeStructureList, currentIndex, structure, chain, count, *ident, *slot, cachedOffset);
            break;
        }
    case e_JIT_compileGetByIdProto:
        {
            VM *                 vm(reinterpret_cast<VM *>(payload->recvArgument()));
            CallFrame *          callFrame(reinterpret_cast<CallFrame *>(payload->recvArgument()));
            CodeBlock *          codeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            StructureStubInfo *  stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            Structure *          structure(reinterpret_cast<Structure *>(payload->recvArgument()));
            Structure *          prototypeStructure(reinterpret_cast<Structure *>(payload->recvArgument()));
            Identifier const *   ident(reinterpret_cast<Identifier const *>(payload->recvArgument()));
            PropertySlot const * slot(payload->recvPOD<PropertySlot>());
            PropertyOffset       cachedOffset(static_cast<PropertyOffset>(payload->recvArgument()));
            void *               returnAddress(reinterpret_cast<void *>(payload->recvArgument()));
            JIT::compileGetByIdProto(vm, callFrame, codeBlock, stubInfo, structure, prototypeStructure, *ident, *slot, cachedOffset, ReturnAddressPtr(returnAddress));
            break;
        }
    case e_JIT_compileGetByIdProtoList:
        {
            VM *                             vm(reinterpret_cast<VM *>(payload->recvArgument()));
            CallFrame *                      callFrame(reinterpret_cast<CallFrame *>(payload->recvArgument()));
            CodeBlock *                      codeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            StructureStubInfo *              stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            PolymorphicAccessStructureList * prototypeStructureList(reinterpret_cast<PolymorphicAccessStructureList *>(payload->recvArgument()));
            int                              currentIndex(static_cast<int>(payload->recvArgument()));
            Structure *                      structure(reinterpret_cast<Structure *>(payload->recvArgument()));
            Structure *                      prototypeStructure(reinterpret_cast<Structure *>(payload->recvArgument()));
            Identifier const *               ident(reinterpret_cast<Identifier const *>(payload->recvArgument()));
            PropertySlot const *             slot(payload->recvPOD<PropertySlot>());
            PropertyOffset                   cachedOffset(static_cast<PropertyOffset>(payload->recvArgument()));
            JIT::compileGetByIdProtoList(vm, callFrame, codeBlock, stubInfo, prototypeStructureList, currentIndex, structure, prototypeStructure, *ident, *slot, cachedOffset);
            break;
        }
    case e_JIT_compileGetByIdSelfList:
        {
            VM *                             vm(reinterpret_cast<VM *>(payload->recvArgument()));
            CodeBlock *                      codeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            StructureStubInfo *              stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            PolymorphicAccessStructureList * polymorphicStructures(reinterpret_cast<PolymorphicAccessStructureList *>(payload->recvArgument()));
            int                              currentIndex(static_cast<int>(payload->recvArgument()));
            Structure *                      structure(reinterpret_cast<Structure *>(payload->recvArgument()));
            Identifier const *               ident(reinterpret_cast<Identifier const *>(payload->recvArgument()));
            PropertySlot const *             slot(payload->recvPOD<PropertySlot>());
            PropertyOffset                   cachedOffset(static_cast<PropertyOffset>(payload->recvArgument()));
            JIT::compileGetByIdSelfList(vm, codeBlock, stubInfo, polymorphicStructures, currentIndex, structure, *ident, *slot, cachedOffset);
            break;
        }
    case e_JIT_compileGetByVal:
        {
            VM *                 vm(reinterpret_cast<VM *>(payload->recvArgument()));
            CodeBlock *          codeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            ByValInfo *          byValInfo(reinterpret_cast<ByValInfo *>(payload->recvArgument()));
            void *               returnAddress(reinterpret_cast<void *>(payload->recvArgument()));
            JITArrayMode         arrayMode(static_cast<JITArrayMode>(payload->recvArgument()));
            JIT::compileGetByVal(vm, codeBlock, byValInfo, ReturnAddressPtr(returnAddress), arrayMode);
            break;
        }
    case e_JIT_compilePatchGetArrayLength:
        {
            VM *        vm(reinterpret_cast<VM *>(payload->recvArgument()));
            CodeBlock * codeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            void *      returnAddress(reinterpret_cast<void *>(payload->recvArgument()));
            JIT::compilePatchGetArrayLength(vm, codeBlock, ReturnAddressPtr(returnAddress));
            break;
        }
    case e_JIT_compilePutByIdTransition:
        {
            VM *                 vm(reinterpret_cast<VM *>(payload->recvArgument()));
            CodeBlock *          codeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            StructureStubInfo *  stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            Structure *          oldStructure(reinterpret_cast<Structure *>(payload->recvArgument()));
            Structure *          newStructure(reinterpret_cast<Structure *>(payload->recvArgument()));
            PropertyOffset       cachedOffset(static_cast<PropertyOffset>(payload->recvArgument()));
            StructureChain *     chain(reinterpret_cast<StructureChain *>(payload->recvArgument()));
            void *               returnAddress(reinterpret_cast<void *>(payload->recvArgument()));
            bool                 direct(static_cast<bool>(payload->recvArgument()));
            JIT::compilePutByIdTransition(vm, codeBlock, stubInfo, oldStructure, newStructure, cachedOffset, chain, ReturnAddressPtr(returnAddress), direct);
            break;
        }
    case e_JIT_compilePutByVal:
        {
            VM *                 vm(reinterpret_cast<VM *>(payload->recvArgument()));
            CodeBlock *          codeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            ByValInfo *          byValInfo(reinterpret_cast<ByValInfo *>(payload->recvArgument()));
            void *               returnAddress(reinterpret_cast<void *>(payload->recvArgument()));
            JITArrayMode         arrayMode(static_cast<JITArrayMode>(payload->recvArgument()));
            JIT::compilePutByVal(vm, codeBlock, byValInfo, ReturnAddressPtr(returnAddress), arrayMode);
            break;
        }
    case e_JIT_linkFor:
        {
            JSFunction *            callee(reinterpret_cast<JSFunction *>(payload->recvArgument()));
            CodeBlock *             callerCodeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            CodeBlock *             calleeCodeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            MacroAssemblerCodePtr * codePtr(reinterpret_cast<MacroAssemblerCodePtr *>(payload->recvArgument()));
            CallLinkInfo *          callLinkInfo(reinterpret_cast<CallLinkInfo *>(payload->recvArgument()));
            VM *                    vm(reinterpret_cast<VM*>(payload->recvArgument()));
            CodeSpecializationKind  kind(static_cast<CodeSpecializationKind>(payload->recvArgument()));
            JIT::linkFor(callee, callerCodeBlock, calleeCodeBlock, *codePtr, callLinkInfo, vm, kind);
            break;
        }
    case e_JIT_linkSlowCall:
        {
            CodeBlock *    callerCodeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            CallLinkInfo * callLinkInfo(reinterpret_cast<CallLinkInfo *>(payload->recvArgument()));
            JIT::linkSlowCall(callerCodeBlock, callLinkInfo);
            break;
        }
    case e_JIT_patchGetByIdSelf:
        {
            CodeBlock *         codeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            StructureStubInfo * stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            Structure *         structure(reinterpret_cast<Structure *>(payload->recvArgument()));
            PropertyOffset      cachedOffset(static_cast<PropertyOffset>(payload->recvArgument()));
            void *              returnAddress(reinterpret_cast<void *>(payload->recvArgument()));
            JIT::patchGetByIdSelf(codeBlock, stubInfo, structure, cachedOffset, ReturnAddressPtr(returnAddress));
            break;
        }
    case e_JIT_patchPutByIdReplace:
        {
            CodeBlock *         codeBlock(reinterpret_cast<CodeBlock *>(payload->recvArgument()));
            StructureStubInfo * stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            Structure *         structure(reinterpret_cast<Structure *>(payload->recvArgument()));
            PropertyOffset      cachedOffset(static_cast<PropertyOffset>(payload->recvArgument()));
            void *              returnAddress(reinterpret_cast<void *>(payload->recvArgument()));
            bool                direct(static_cast<bool>(payload->recvArgument()));
            JIT::patchPutByIdReplace(codeBlock, stubInfo, structure, cachedOffset, ReturnAddressPtr(returnAddress), direct);
            break;
        }
    case e_JIT_resetPatchGetById:
        {
            RepatchBuffer *     repatchBuffer(reinterpret_cast<RepatchBuffer *>(payload->recvArgument()));
            StructureStubInfo * stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            JIT::resetPatchGetById(*repatchBuffer, stubInfo);
            break;
        }
    case e_JIT_resetPatchPutById:
        {
            RepatchBuffer *     repatchBuffer(reinterpret_cast<RepatchBuffer *>(payload->recvArgument()));
            StructureStubInfo * stubInfo(reinterpret_cast<StructureStubInfo *>(payload->recvArgument()));
            JIT::resetPatchPutById(*repatchBuffer, stubInfo);
            break;
        }
#if ENABLE(LLINT)
    case e_LLINT_generateThunk:
        {
            VM * vm(reinterpret_cast<VM *>(payload->recvArgument()));
            uintptr_t target(payload->recvArgument());
            JIT::CodeRef codeRef(LLInt::generateThunkWithJumpTo(vm, reinterpret_cast<void (*)()>(target), "llint_thunk_from_compiler"));
            payload->m_retval = reinterpret_cast<uintptr_t>(sharedNew<MacroAssemblerCodeRef>(codeRef));
            break;
        }
#endif
    case e_MacroAssembler_repatchCallFunctionPtr:
        {
            void * call(reinterpret_cast<void *>(payload->recvArgument()));
            void * destination(reinterpret_cast<void *>(payload->recvArgument()));
            MacroAssembler::repatchCall(CodeLocationCall(call), FunctionPtr(destination));
            break;
        }
    case e_MacroAssembler_repatchCompact:
        {
            void *  dataLabelCompact(reinterpret_cast<void *>(payload->recvArgument()));
            int32_t value(static_cast<int32_t>(payload->recvArgument()));
            MacroAssembler::repatchCompact(CodeLocationDataLabelCompact(dataLabelCompact), value);
            break;
        }
    case e_MacroAssembler_repatchInt32:
        {
            void * dataLabel32(reinterpret_cast<void *>(payload->recvArgument()));
            int32_t value(static_cast<int32_t>(payload->recvArgument()));
            MacroAssembler::repatchInt32(CodeLocationDataLabel32(dataLabel32), value);
            break;
        }
    case e_MacroAssembler_repatchJump:
        {
            void * jump(reinterpret_cast<void *>(payload->recvArgument()));
            void * destination(reinterpret_cast<void *>(payload->recvArgument()));
            MacroAssembler::repatchJump(CodeLocationJump(jump), CodeLocationLabel(destination));
            break;
        }
    case e_MacroAssembler_repatchNearCall:
        {
            void * nearCall(reinterpret_cast<void *>(payload->recvArgument()));
            void * destination(reinterpret_cast<void *>(payload->recvArgument()));
            MacroAssembler::repatchNearCall(CodeLocationNearCall(nearCall), CodeLocationLabel(destination));
            break;
        }
    case e_MacroAssembler_repatchPointer:
        {
            void * dataLabelPtr(reinterpret_cast<void *>(payload->recvArgument()));
            void * value(reinterpret_cast<void *>(payload->recvArgument()));
            MacroAssembler::repatchPointer(CodeLocationDataLabelPtr(dataLabelPtr), value);
            break;
        }
    case e_MacroAssembler_replaceWithAddressComputation:
        {
            void * label(reinterpret_cast<void *>(payload->recvArgument()));
            MacroAssembler::replaceWithAddressComputation(CodeLocationConvertibleLoad(label));
            break;
        }
    case e_MacroAssembler_replaceWithJump:
        {
            void * instructionStart(reinterpret_cast<void *>(payload->recvArgument()));
            void * to(reinterpret_cast<void *>(payload->recvArgument()));
            MacroAssembler::replaceWithJump(CodeLocationLabel(instructionStart), CodeLocationLabel(to));
            break;
        }
    case e_MacroAssembler_revertJumpReplacementToBranch:
        {
            void *                     instructionStart(reinterpret_cast<void *>(payload->recvArgument()));
            MacroAssembler::RegisterID reg(static_cast<MacroAssembler::RegisterID>(payload->recvArgument()));
            void *                     value(reinterpret_cast<void *>(payload->recvArgument()));
            MacroAssemblerX86_64::revertJumpReplacementToBranchPtrWithPatch(CodeLocationLabel(instructionStart), reg, value);
            break;
        }
    case e_MacroAssembler_revertJumpReplacementToPatchableBranch:
        {
            void *                          instructionStart(reinterpret_cast<void *>(payload->recvArgument()));
            MacroAssembler::Address const * address(payload->recvPOD<MacroAssembler::Address>());
            void *                          initialValue(reinterpret_cast<void *>(payload->recvArgument()));
            MacroAssemblerX86_64::revertJumpReplacementToPatchableBranchPtrWithPatch(CodeLocationLabel(instructionStart), *address, initialValue);
            break;
        }
    case e_Yarr_jitCompile:
        {
            Yarr::YarrPattern *      pattern(reinterpret_cast<Yarr::YarrPattern *>(payload->recvArgument()));
            Yarr::YarrCharSize       charSize(static_cast<Yarr::YarrCharSize>(payload->recvArgument()));
            VM * const               vm(reinterpret_cast<VM*>(payload->recvArgument()));
            Yarr::YarrCodeBlock *    jitObject(reinterpret_cast<Yarr::YarrCodeBlock *>(payload->recvArgument()));
            Yarr::YarrJITCompileMode mode(static_cast<Yarr::YarrJITCompileMode>(payload->recvArgument()));
            Yarr::jitCompile(*pattern, charSize, vm, *jitObject, mode);
            break;
        }
    default:
        {
            LOG_ERROR("[Bridge-Compiler] unknown compiler task %d\n", m_sharedData->m_payload.m_compilerFunction);
            __builtin_trap();  // security breach?
            break;
        }
    }

    LOG(DetachedJIT, "[Bridge-Compiler] %s DONE\n", toString(m_sharedData->m_payload.m_compilerFunction));

    return;
}

uintptr_t JSCBridge::requestCompilerTask(CompilerFunction compilerFunction)
{
    // you MUST NOT call this from the JIT compiler process
    __builtin_trap();
    return -1; // just to silence the compiler...
}

} // namespace JSC

#endif // #if ENABLE(JIT) && ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT

