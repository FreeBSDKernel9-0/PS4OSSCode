// Copyright (C) 2012 Sony Computer Entertainment Inc.
// All Rights Reserved.
#include "JSCBridge.h"

#if ENABLE(DETACHED_JIT)

#include <time.h>

namespace JSC {

#if ENABLE(BRIDGE_PROFILER)

size_t                JSCBridge::Profiler::m_numProfilers(0);
JSCBridge::Profiler * JSCBridge::Profiler::m_profilers[JSCBridge::Profiler::m_maxProfilers];
bool                  JSCBridge::Profiler::m_enabled(false);

JSCBridge::Profiler::Profiler(char const * label)
    : m_count(0)
    , m_elapsed(0)
{
    snprintf(m_label, sizeof(m_label), "%s", label);

    ASSERT(Profiler::m_numProfilers < Profiler::m_maxProfilers);
    m_profilers[Profiler::m_numProfilers++] = this;
}

JSCBridge::Profiler::~Profiler()
{
    dump();
}

void JSCBridge::Profiler::dump()
{
    if (m_count) {
        printf("[JSCBridge Toll] %4d : %4ld : %s\n", m_count, m_elapsed, m_label);
    }
}

void JSCBridge::Profiler::foreach(
    void (JSCBridge::Profiler::*method)())
{
    for (int i = 0; i < m_numProfilers; ++i) {
        (m_profilers[i]->*method)();
    }
}

unsigned long JSCBridge::Profiler::total()
{
    unsigned long total = 0;
    for (int i = 0; i < m_numProfilers; ++i) {
        total += m_profilers[i]->m_count;
    }

    return total;
}

uint64_t JSCBridge::Profiler::totalElapsed()
{
    clock_t total = 0;
    for (int i = 0; i < m_numProfilers; ++i) {
        total += m_profilers[i]->m_elapsed;
    }

    return total;
}

#endif // ENABLE(BRIDGE_PROFILER)

void JSCBridge::Profiler::enable(
    bool e)
{
#if ENABLE(BRIDGE_PROFILER)
    m_enabled = e;
    if (m_enabled) {
        foreach(&JSCBridge::Profiler::reset);
    } else {
        printf("[JSCBridge Toll] total : %ld, %ld\n", total(), totalElapsed());
    }
#else
    (void) e;
#endif
}

JSCBridge JSCBridge::s_instance;

JSCBridge::JSCBridge()
    : m_processType(ProcessUnknown)
    , m_isParent(false)
    , m_compilerLock(PTHREAD_MUTEX_INITIALIZER)
    , m_sharedBridge(0)
    , m_sharedData(0)
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_NORMAL);
    
    if (pthread_mutex_init(&m_compilerLock, &attr) != 0)
        __builtin_trap();

    pthread_mutexattr_destroy(&attr);
}

JSCBridge::~JSCBridge()
{
    pthread_mutex_destroy(&m_compilerLock);
}

void JSCBridge::initializeSharedData()
{
    ASSERT(m_sharedBridge);

    m_sharedData = reinterpret_cast<SharedData*>(&(m_sharedBridge->m_sharedMemoryArea[0]));

    size_t const requiredSharedMemorySize(sizeof(SharedData));
    size_t const actualSharedMemorySize(m_sharedBridge->sharedMemoryAreaSize());
    if (requiredSharedMemorySize > actualSharedMemorySize) {
        __builtin_trap();
    }
    //fprintf(stderr, "required shared memory size: %zd, actual shared memory size: %zd\n", requiredSharedMemorySize, actualSharedMemorySize);
}

void JSCBridge::ringDoorbell()
{
    switch (m_processType) {
    case ProcessCompiler:
        m_sharedBridge->ringVMDoorbell();
        break;
    case ProcessVM:
        m_sharedBridge->ringCompilerDoorbell();
        break;
    default:
        __builtin_trap();
    }

    return;
}

void JSCBridge::shutdown(bool restartOnly)
{
    if (m_processType == ProcessCompiler) {
        JITBridge::shutdownFromCompiler(m_sharedBridge, restartOnly);
    } else if (m_processType == ProcessVM) {
        JITBridge::shutdownFromVM(m_sharedBridge, restartOnly);
    }
    m_processType = ProcessUnknown;
}

JITBridge::Doorbell JSCBridge::waitDoorbell()
{
    switch (m_processType) {
    case ProcessCompiler:
        return m_sharedBridge->waitCompilerDoorbell();
    case ProcessVM:
        return m_sharedBridge->waitVMDoorbell();
    default:
        break;
    }

    __builtin_trap();
    return JITBridge::DoorbellShutdown;
}

} // namespace JSC

#else // #if ENABLE(DETACHED_JIT)

namespace JSC {

// NOTE to enable these functionalities, set ENABLE_DETACHED_JIT to 1
//      These stubs are provided to simplify builds of non DETACHED_JIT configurations
JSCBridge JSCBridge::s_instance;
JSCBridge::JSCBridge() {}
JSCBridge::~JSCBridge() {}
void JSCBridge::initializeFromCompiler(size_t, size_t, char const *, char **, JITBridge::RestartData const *) {}
void JSCBridge::initializeFromVM(char const *, char **, JITBridge::RestartData const *)                       {}
void JSCBridge::performCompilerTask()                                         { __builtin_trap(); }
void JSCBridge::ringDoorbell()                                                {}
void JSCBridge::shutdown(bool)                                                {}
JITBridge::Doorbell JSCBridge::waitDoorbell()                                 { __builtin_trap(); return JITBridge::DoorbellShutdown; }
void JSCBridge::Profiler::enable(bool)                                        {}

} // namespace JSC

#endif

