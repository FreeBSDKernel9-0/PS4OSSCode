// Copyright (C) 2012 Sony Computer Entertainment Inc.
// All Rights Reserved.

#ifndef JSCBridge_h
#define JSCBridge_h

#include "JITBridge.h"
#include "JITStubEntryHelper.h"
#include <assert.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>

namespace JSC {

    struct ClassInfo;
    class JIT;

    static size_t const s_jscbridgeRuntimeClassInfoMax = 1280;

    class JSCBridge {
        // constructor/destructor
    private:
        JSCBridge();
        ~JSCBridge();
    public:
        static JSCBridge *  sharedInstance() { return &s_instance; }
        JITBridge *         jitBridge() const { return m_sharedBridge; }

        // public APIs
    public:
        struct Profiler {
#if ENABLE_BRIDGE_PROFILER
            Profiler(char const * label);
            ~Profiler();
            void         dump();
            inline void  increment()                { m_count += Profiler::m_enabled ? 1 : 0; }
            inline void  incrementTimer(uint64_t t) { m_elapsed += t; }
            void         reset()                    { m_count = 0; }
            unsigned int m_count;
            char         m_label[64];
            uint64_t     m_elapsed;

            static unsigned long total();
            static uint64_t      totalElapsed();
            static void          foreach(void (JSCBridge::Profiler::*method)());
            static bool          m_enabled;
            static size_t const  m_maxProfilers = 32;
            static size_t        m_numProfilers;
            static Profiler *    m_profilers[m_maxProfilers];
#endif // ENABLE(BRIDGE_PROFILER)
            static void          enable(bool);
        };

#if ENABLE_BRIDGE_PROFILER
        struct ScopedTimer {
            ScopedTimer(Profiler * profiler) 
                : m_profiler(profiler)
                , m_begin(0)
            {
                struct timeval now;
                gettimeofday(&now, 0);
                m_begin = (now.tv_sec * 1000000) + (now.tv_usec);

            }
            ~ScopedTimer()
            {
                struct timeval now;
                gettimeofday(&now, 0);
                uint64_t end((now.tv_sec * 1000000) + (now.tv_usec));
                m_profiler->incrementTimer(end - m_begin);
            }
            Profiler * m_profiler;
            uint64_t   m_begin;
        };
#endif // ENABLE(BRIDGE_PROFILER)

    public:
        void                    initializeFromCompiler(size_t sharedDataMemorySize, size_t sharedTextMemorySize, char const * vmTestApp = NULL, char ** vmTestAppArgs = NULL, JITBridge::RestartData const * restartData = NULL);
        void                    initializeFromVM(char const * compilerApp, char ** compilerArgs, JITBridge::RestartData const * restartData = NULL);
        void                    shutdown(bool restartOnly = false);
        void                    ringDoorbell();
        JITBridge::Doorbell     waitDoorbell();
    public:
        template <typename T> T mapFromVMToCompiler(T) const { __builtin_trap();  /* please provide specialized version of this */ }

    public:
        // list of operations that can be performed on the JIT compiler process
        enum CompilerFunction {
            e_absThunkGenerator,
            e_ceilThunkGenerator,
            e_charAtThunkGenerator,
            e_charCodeAtThunkGenerator,
            e_charToString,
            e_expThunkGenerator,
            e_floorThunkGenerator,
            e_fromCharCodeThunkGenerator,
            e_logThunkGenerator,
            e_powThunkGenerator,
            e_roundThunkGenerator,
            e_sqrtThunkGenerator,
            e_stringCharLoad,
            e_ctiPatchCallReturnAddrCodePtr,
            e_ctiPatchCallReturnAddrFunctionPtr,
            e_ctiPatchNearCallByReturnAddress,
            e_DFG_compile,
            e_DFG_compileBuildGetByIDList,
            e_DFG_compileCacheGetByIDArray,
            e_DFG_compileFunction,
            e_DFG_compileOSRExit,
            e_DFG_emitPutReplaceStub,
            e_DFG_emitPutTransitionStub,
            e_DFG_generateProtoChainAccessStub,
            e_DFG_linkFor,
            e_DFG_repatchByIdSelfAccess,
            e_JIT_linkFor,
            e_JIT_patchPutByIdReplace,
            e_JIT_patchMethodCallProto,
            e_JIT_patchGetByIdSelf,
            e_JIT_privateCompile,
            e_JIT_privateCompileCTIMachineTrampolines,
            e_JIT_privateCompileCTINativeCall,
            e_JIT_privateCompileGetByIdChain,
            e_JIT_privateCompileGetByIdChainList,
            e_JIT_privateCompileGetByIdProto,
            e_JIT_privateCompileGetByIdProtoList,
            e_JIT_privateCompileGetByIdSelfList,
            e_JIT_privateCompilePatchGetArrayLength,
            e_JIT_privateCompilePutByIdTransition,
            e_JIT_resetPatchGetById,
            e_JIT_resetPatchPutById,
            e_LinkBuffer_link,
            e_MacroAssembler_repatchCall,
            e_MacroAssembler_repatchJump,
            e_MacroAssembler_repatchNearCall,
            e_MacroAssembler_repatchPointer,
            e_RepatchBuffer_relinkCallToFuncPtr,
            e_RepatchBuffer_relinkJumpToLabel,
            e_RepatchBuffer_relinkNearCallToCodePtr,
            e_RepatchBuffer_repatchLabelToVoidPtr,
            e_RepatchBuffer_repatchLabelCompactToInt,
            e_RepatchBuffer_repatchLabel32ToInt,
            e_Yarr_jitCompile
        };

        // used to send information from the VM process to the JIT compiler process
        struct Payload {
            static size_t const s_maxArguments = 32;
            CompilerFunction    m_compilerFunction;
            uintptr_t           m_retval;
            uintptr_t           m_args[s_maxArguments];
            size_t              m_argsSendIndex;
            size_t              m_argsRecvIndex;

            void                  reset()                     { m_retval = -1; m_argsSendIndex = m_argsRecvIndex = 0; }
            inline void           sendArgument(uintptr_t arg) { assert(m_argsSendIndex < s_maxArguments);  if (m_argsSendIndex >= s_maxArguments)  { __builtin_trap(); } m_args[m_argsSendIndex++] = arg; }
            inline uintptr_t      recvArgument()              { assert(m_argsRecvIndex < m_argsSendIndex); if (m_argsRecvIndex >= m_argsSendIndex) { __builtin_trap(); } return m_args[m_argsRecvIndex++]; }
            template <typename T> inline void sendPOD(T const * blob)
            {
                size_t const argSize(sizeof(m_args[0]));
                size_t const numArgs((sizeof(T) + (argSize-1)) / argSize);
                assert((m_argsSendIndex + numArgs) <= s_maxArguments);
                if ((m_argsSendIndex + numArgs) > s_maxArguments)
                    __builtin_trap();
                memcpy(&(m_args[m_argsSendIndex]), blob, sizeof(T));
                m_argsSendIndex += numArgs;
            }
            template <typename T> inline T const * recvPOD()
            {
                size_t const argSize(sizeof(m_args[0]));
                size_t const numArgs((sizeof(T) + (argSize-1)) / argSize);
                assert((m_argsRecvIndex + numArgs) <= m_argsSendIndex);
                if ((m_argsRecvIndex + numArgs) > m_argsSendIndex)
                    __builtin_trap();
                T const * retval(reinterpret_cast<T const *>(&(m_args[m_argsRecvIndex])));
                m_argsRecvIndex += numArgs;
                return retval;
            }
        } __attribute__((aligned(sizeof(uintptr_t))));

        struct RuntimeClassInfo {
            uintptr_t m_classInfoPtr;
            uint8_t   m_data[192];
        };

        // used to initialize the JIT compiler process with shared information that is normally initialized on the VM process
        struct StaticVMData {
#define CTI_STUB_ENTRY(ignoredReturnValue, stub) uintptr_t m_##stub
            CTI_STUB_ENTRIES;
#if ENABLE_DFG_JIT
            CTI_STUB_ENTRIES_DFG;
            CTI_STUB_ENTRIES_DFG_OPERATIONS;
#endif
#undef  CTI_STUB_ENTRY

#define CLASSINFO_STUB_ENTRY(classname) uintptr_t m_##classname##_classinfo; uint8_t m_##classname##_classinfo_copy[192]
            CLASSINFO_STUB_ENTRIES;
#undef  CLASSINFO_STUB_ENTRY
            RuntimeClassInfo m_runtimeClassInfo[s_jscbridgeRuntimeClassInfoMax];
            size_t           m_runtimeClassInfoCount;

            uintptr_t        m_zero;
            uintptr_t        m_byteMax;
            uintptr_t        m_half;
            uintptr_t        m_twoToThe32;
            uintptr_t        m_NaN;
            uintptr_t        m_oneConstant;
            uintptr_t        m_negativeHalfConstant;
            uintptr_t        m_negativeZeroConstant;
            uintptr_t        m_regExpSpacesData;
            uintptr_t        m_regExpWordCharData;
            uintptr_t        m_ctiVMThrowTrampoline;
            uintptr_t        m_executableAllocator;
        } __attribute__((aligned(sizeof(uintptr_t))));

    public:
        Payload *           payload()             { m_sharedData->m_payload.reset(); return &(m_sharedData->m_payload); }
        StaticVMData *      staticVMData()        { return &(m_sharedData->m_staticVMData); }
        uintptr_t           requestCompilerTask(CompilerFunction, JIT *);
        uintptr_t           invokeVM();
        void                performCompilerTask();
        void                initializeCompilerSharedData();
        static RuntimeClassInfo * registerRuntimeClassinfo(ClassInfo const *, size_t * total = NULL);

        // private APIs
    private:
        struct SharedData {
            StaticVMData    m_staticVMData;
            Payload         m_payload;
        };
    private:
        void                initializeSharedData();
        void                fixupClassInfo(ClassInfo *);
    private:
        static JSCBridge    s_instance;
    private:
        enum                ProcessType { ProcessCompiler, ProcessVM, ProcessUnknown };
        ProcessType         m_processType;
        bool                m_isParent;
        pthread_mutex_t     m_compilerLock;
        JITBridge *         m_sharedBridge;
        SharedData *        m_sharedData;
    };

    template <> ClassInfo const * JSCBridge::mapFromVMToCompiler(ClassInfo const * vmClassInfoAddress) const;

#if ENABLE_BRIDGE_PROFILER
#   define _COUNTER_DEFINE(c, label)        static JSC::JSCBridge::Profiler c(label)
#   define _COUNTER_INCREMENT(c)            { c.increment(); }
#   define _PROFILE_FUNCTION_CALL(label)                        \
        _COUNTER_DEFINE(counter_##label, label);                \
        _COUNTER_INCREMENT(counter_##label);                    \
        JSC::JSCBridge::ScopedTimer t##label(&counter_##label);
#   define PROFILE_FUNCTION_CALL            _PROFILE_FUNCTION_CALL(__FUNCTION__);
#else
#   define PROFILE_FUNCTION_CALL            {}
#endif // ENABLE(BRIDGE_PROFILER)

} // namespace JSC

#endif // #ifndef JSCBridge_h
