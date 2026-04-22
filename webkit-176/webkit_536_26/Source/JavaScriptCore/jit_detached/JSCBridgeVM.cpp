// Copyright (C) 2012 Sony Computer Entertainment Inc.
// All Rights Reserved.

#include "config.h"

#if !OS(WINDOWS)
#include "JSCBridge.cpp"
#endif

#if ENABLE(JIT)

#if ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

#include "dfg/DFGOperations.h"
#include "dfg/DFGOSRExitCompiler.h"
#include "dfg/DFGSpeculativeJIT.h"
#include "AbstractMacroAssembler.h"
#include "ArrayConstructor.h"
#include "ArrayPrototype.h"
#include "AssemblerBuffer.h"
#include "BooleanConstructor.h"
#include "DateConstructor.h"
#include "DateInstance.h"
#include "DatePrototype.h"
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
#define DEBUG_LOG(x, ...) fprintf(stderr, "[JSC bridge VM] " x, __VA_ARGS__)
#define DEBUG_ERR(x, ...) fprintf(stderr, "[JSC bridge VM] " x, __VA_ARGS__)
#else
#define DEBUG_LOG(x, ...)
#define DEBUG_ERR(x, ...)
#endif

namespace JSC {

void JSCBridge::initializeFromCompiler(size_t sharedDataMemorySize, size_t sharedTextMemorySize, char const * vmTestApp, char ** vmTestAppArgs, JITBridge::RestartData const *)
{
    // you MUST NOT call this from the VM process
    __builtin_trap();
}

void JSCBridge::initializeFromVM(char const * compilerApp, char ** compilerArgs, JITBridge::RestartData const * restartData)
{
    if (m_processType != ProcessUnknown) {
        return;
    }

    m_processType = ProcessVM;
    m_sharedBridge = JITBridge::initializeFromVM(compilerApp, compilerArgs, restartData);
    initializeSharedData();

    // VM<->Compiler handshake
    {
        using namespace DFG;

        JSC::JSCBridge::StaticVMData * vmData(this->staticVMData());
        memset(vmData, 0, sizeof(JSC::JSCBridge::StaticVMData));
        vmData->m_ctiVMThrowTrampoline = reinterpret_cast<uintptr_t>(ctiVMThrowTrampoline);
        vmData->m_zero                 = reinterpret_cast<uintptr_t>(&JSC::zero);
        vmData->m_byteMax              = reinterpret_cast<uintptr_t>(&JSC::byteMax);
        vmData->m_half                 = reinterpret_cast<uintptr_t>(&JSC::half);
        vmData->m_twoToThe32           = reinterpret_cast<uintptr_t>(&JSC::twoToThe32);

        vmData->m_NaN                  = reinterpret_cast<uintptr_t>(&JSC::NaN);
        vmData->m_oneConstant          = reinterpret_cast<uintptr_t>(&JSC::oneConstant);
        vmData->m_negativeHalfConstant = reinterpret_cast<uintptr_t>(&JSC::negativeHalfConstant);
        vmData->m_negativeZeroConstant = reinterpret_cast<uintptr_t>(&JSC::negativeZeroConstant);
        vmData->m_regExpSpacesData     = reinterpret_cast<uintptr_t>(JSC::Yarr::regExp_spacesData);
        vmData->m_regExpWordCharData   = reinterpret_cast<uintptr_t>(JSC::Yarr::regExp_wordcharData);

        size_t             runtimeClassInfoCount(0);
        RuntimeClassInfo * runtimeClassInfo(registerRuntimeClassinfo(NULL, &runtimeClassInfoCount));
        if (runtimeClassInfo && runtimeClassInfoCount) {
            DEBUG_LOG("transferring %zd instances of class information to the shared heap\n", runtimeClassInfoCount);
            ASSERT(sizeof(vmData->m_runtimeClassInfo) >= runtimeClassInfoCount * sizeof(RuntimeClassInfo));
            memcpy(vmData->m_runtimeClassInfo, runtimeClassInfo, runtimeClassInfoCount * sizeof(RuntimeClassInfo));
            vmData->m_runtimeClassInfoCount = runtimeClassInfoCount ;
        }

#define CTI_STUB_ENTRY(ignoredReturnType, stub) vmData->m_##stub = reinterpret_cast<uintptr_t>(stub)
        CTI_STUB_ENTRIES;
#if ENABLE(DFG_JIT)
        CTI_STUB_ENTRIES_DFG;
        CTI_STUB_ENTRIES_DFG_OPERATIONS;
#endif
#undef  CTI_STUB_ENTRY

#define CLASSINFO_STUB_ENTRY(classname) { \
        vmData->m_##classname##_classinfo = reinterpret_cast<uintptr_t>(& JSC::classname::s_info); \
        ASSERT(sizeof(JSC::classname::s_info) == sizeof(vmData->m_##classname##_classinfo_copy)); \
        memcpy(reinterpret_cast<void *>(vmData->m_##classname##_classinfo_copy), reinterpret_cast<void const *>(&JSC::classname::s_info), sizeof(JSC::classname::s_info)); \
        }
        CLASSINFO_STUB_ENTRIES;
#undef  CLASSINFO_STUB_ENTRY

        // wait for compiler to prepare shared data arenas
        waitDoorbell();

        // executable allocators can only be initialized when shared data arenas are ready
        vmData->m_executableAllocator = reinterpret_cast<uintptr_t>(ExecutableAllocator::metaAllocator());

        // notify compiler all VM data that the compiler needs are ready
        ringDoorbell();

        // wait for compiler to prepare all data the VM needs
        waitDoorbell();
    }
}

void JSCBridge::performCompilerTask()
{
    // you MUST NOT call this from the VM process
    __builtin_trap();
}

JSCBridge::RuntimeClassInfo * JSCBridge::registerRuntimeClassinfo(ClassInfo const * classInfo, size_t * total)
{
    static RuntimeClassInfo s_runtimeClassInfo[s_jscbridgeRuntimeClassInfoMax];  // stores runtime registered ClassInfo instances defined outside of JSC (i.e. when WebCore uses JSC ClassInfo to define object class)
    static size_t           s_runtimeClassInfoCount = 0;

    if (classInfo) {
        // allocate slot for class info
        size_t slot(s_runtimeClassInfoCount++);
        if (s_runtimeClassInfoCount >= s_jscbridgeRuntimeClassInfoMax) {
            DEBUG_ERR("dynamic class info registration full!  current size = %zd\n", s_jscbridgeRuntimeClassInfoMax);
            __builtin_trap();
            return 0;
        }

        //DEBUG_LOG("registering runtime ClassInfo '%s' : %lx\n", classInfo->className, (uintptr_t)classInfo);
        s_runtimeClassInfo[slot].m_classInfoPtr = reinterpret_cast<uintptr_t>(classInfo);
        COMPILE_ASSERT(sizeof(s_runtimeClassInfo[slot].m_data) == sizeof(*classInfo), RuntimeClassInfo_mData_LargeEnough);
        memcpy(&(s_runtimeClassInfo[slot].m_data[0]), classInfo, sizeof(*classInfo));
    }

    if (total) *total = s_runtimeClassInfoCount;
    return s_runtimeClassInfo;
}

uintptr_t JSCBridge::requestCompilerTask(CompilerFunction compilerFunction, JIT * jit)
{
    if (pthread_mutex_lock(&m_compilerLock) !=0) {
        __builtin_trap();
    }

#if ENABLE(DFG_JIT)
    if (jit) {
        jit->calculateCanBeOptimized();
    }
#endif
    Payload * const payload(&(m_sharedData->m_payload));
    payload->m_compilerFunction = compilerFunction;

    ringDoorbell();
    waitDoorbell();

    uintptr_t retval(m_sharedData->m_payload.m_retval);

    if (pthread_mutex_unlock(&m_compilerLock) != 0) {
        __builtin_trap();
    }

    return retval;
}

} // namespace JSC

#endif // #if ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

#endif // #if ENABLE(JIT)

