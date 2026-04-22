// Copyright (C) 2012 Sony Computer Entertainment Inc.
// All Rights Reserved.

#ifndef JSCBridge_h
#define JSCBridge_h

#include "JITStubEntryHelper.h"

#include <JITBridge.h>

#include <assert.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>

#if ENABLE_DETACHED_JIT

namespace JSC {

    struct ClassInfo;
    class JIT;
    class JSCBridgeToll;

    static size_t const s_jscbridgeRuntimeClassInfoMax = 1400;

    class JSCBridge {
        friend class JSCBridgeToll;

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
        void                    initializeFromCompiler(char const * vmTestApp = NULL, char ** vmTestAppArgs = NULL, JITBridge::RestartData const * restartData = NULL);
        void                    initializeFromVM(char const * compilerApp, char ** compilerArgs, JITBridge::RestartData const * restartData = NULL);
        void                    shutdown(bool restartOnly = false);
        void                    ringDoorbell();
        JITBridge::Doorbell     waitDoorbell();
    public:
        template <typename T> T mapFromVMToCompiler(T) const { __builtin_trap();  /* please provide specialized version of this */ }

    public:
        // list of operations that can be performed on the JIT compiler process
        enum CompilerFunction {
            // thunk generators
            e_absThunkGenerator,
            e_ceilThunkGenerator,
            e_charAtThunkGenerator,
            e_charCodeAtThunkGenerator,
            e_charToString,
            e_expThunkGenerator,
            e_floorThunkGenerator,
            e_fromCharCodeThunkGenerator,
            e_imulThunkGenerator,
            e_linkCallGenerator,
            e_linkConstructGenerator,
            e_logThunkGenerator,
            e_nativeCallGenerator,
            e_nativeConstructGenerator,
            e_powThunkGenerator,
            e_roundThunkGenerator,
            e_sqrtThunkGenerator,
            e_stringLengthTrampolineGenerator,
            
            // DFG
            e_DFG_compile,
            e_DFG_compileFunction,
            e_DFG_compileOSRExit,
            e_DFG_emitPutReplaceStub,
            e_DFG_emitPutTransitionStub,
            e_DFG_generateProtoChainAccessStub,
            e_DFG_linkClosureCallThunkGenerator,
            e_DFG_linkClosureCall,
            e_DFG_linkForThunkGenerator,
            e_DFG_repatchByIdSelfAccess,
            e_DFG_throwExceptionFromCall,
            e_DFG_tryBuildGetByIDList,
            e_DFG_tryCacheGetByID,
            e_DFG_virtualForThunkGenerator,

            // JIT compile/link/patch operations
            e_JIT_compile,
            e_JIT_compileClosureCall,
            e_JIT_compileCTINativeCall,
            e_JIT_compileGetByIdChain,
            e_JIT_compileGetByIdChainList,
            e_JIT_compileGetByIdProto,
            e_JIT_compileGetByIdProtoList,
            e_JIT_compileGetByIdSelfList,
            e_JIT_compileGetByVal,
            e_JIT_compilePatchGetArrayLength,
            e_JIT_compilePutByIdTransition,
            e_JIT_compilePutByVal,
            e_JIT_linkFor,
            e_JIT_linkSlowCall,
            e_JIT_patchGetByIdSelf,
            e_JIT_patchPutByIdReplace,
            e_JIT_resetPatchGetById,
            e_JIT_resetPatchPutById,

            // LLINT
            e_LLINT_generateThunk,

            // CTI patch routines
            e_ctiPatchCallReturnAddrCodePtr,
            e_ctiPatchCallReturnAddrFunctionPtr,

            // macro assembler repatch operations
            e_MacroAssembler_linkPointer,
            e_MacroAssembler_repatchCallFunctionPtr,
            e_MacroAssembler_repatchCompact,
            e_MacroAssembler_repatchInt32,
            e_MacroAssembler_repatchJump,
            e_MacroAssembler_repatchNearCall,
            e_MacroAssembler_repatchPointer,
            e_MacroAssembler_replaceWithAddressComputation,
            e_MacroAssembler_replaceWithJump,
            e_MacroAssembler_revertJumpReplacementToBranch,
            e_MacroAssembler_revertJumpReplacementToPatchableBranch,

            // yarr
            e_Yarr_jitCompile,
        };

        // used to send information from the VM process to the JIT compiler process
        class Payload {
            friend class JSCBridge;

        private:
            Payload(pthread_mutex_t lock)
                : m_retval(-1)
                , m_argsSendIndex(0)
                , m_argsRecvIndex(0)
                , m_lock(lock)
            {
            }

        public:
            ~Payload()
            {
                if (__builtin_expect(pthread_mutex_unlock(&m_lock) != 0, 0))
                    __builtin_trap();
            }

            static size_t const s_maxArguments = 32;
            CompilerFunction    m_compilerFunction;
            uintptr_t           m_retval;
            uintptr_t           m_args[s_maxArguments];
            size_t              m_argsSendIndex;
            size_t              m_argsRecvIndex;
            pthread_mutex_t     m_lock;
            JSCBridgeToll *     m_toll;

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

            void * operator new(size_t, void* p)            { return p; }
            void * operator new(size_t size) noexcept       { __builtin_trap(); return NULL; }
            void * operator new[](size_t, void* p) noexcept { __builtin_trap(); return NULL; }
            void * operator new[](size_t size) noexcept     { __builtin_trap(); return NULL; }
            void operator delete(void* p)                   { /* do nothing because the payload buffer is in the shared buffer */ }
            void operator delete[](void* p)                 { __builtin_trap(); }
        } __attribute__((aligned(sizeof(uintptr_t))));

        struct RuntimeClassInfo {
            uintptr_t m_classInfoPtr;
            uint8_t   m_data[208];
        };

        // used to initialize the JIT compiler process with shared information that is normally initialized on the VM process
        struct StaticVMData {
#define CTI_STUB_ENTRY(ignoredReturnValue, stub) uintptr_t m_##stub
            CTI_STUB_ENTRIES;
#if ENABLE_LLINT
            CTI_STUB_ENTRIES_LLINT;
#endif
#if ENABLE_DFG_JIT
            CTI_STUB_ENTRIES_DFG;
            CTI_STUB_ENTRIES_DFG_OPERATIONS;
#endif
#undef  CTI_STUB_ENTRY

#define CLASSINFO_STUB_ENTRY(classname) uintptr_t m_##classname##_classinfo
            // these are provided for code that references ClassInfo by symbol
            CLASSINFO_STUB_ENTRIES;
#undef  CLASSINFO_STUB_ENTRY
            RuntimeClassInfo m_runtimeClassInfo[s_jscbridgeRuntimeClassInfoMax];
            size_t           m_runtimeClassInfoCount;

            uintptr_t        m_byteMax;
            uintptr_t        m_oneConstant;
            uintptr_t        m_zeroConstant;
            uintptr_t        m_halfConstant;
            uintptr_t        m_negativeHalfConstant;
            uintptr_t        m_negativeZeroConstant;
            uintptr_t        m_NaN;
            uintptr_t        m_twoToThe32;
            uintptr_t        m_ctiVMThrowTrampoline;
            uintptr_t        m_executableAllocator;
            uintptr_t        m_regExpSpacesData;
            uintptr_t        m_regExpWordCharData;
        } __attribute__((aligned(sizeof(uintptr_t))));

    public:
        inline Payload *          createPayload()
        {
            assert(m_sharedData);
            if (__builtin_expect(pthread_mutex_lock(&m_compilerLock) != 0, 0))
                __builtin_trap();
            return new(&(m_sharedData->m_payload)) Payload(m_compilerLock);
        }
        inline StaticVMData *     staticVMData() { return &(m_sharedData->m_staticVMData); }
        uintptr_t                 requestCompilerTask(CompilerFunction);
        uintptr_t                 invokeVM();
        void                      performCompilerTask();
        void                      initializeCompilerSharedData();
        static RuntimeClassInfo * registerRuntimeClassinfo(ClassInfo const *, size_t * total = NULL);
        JSCBridgeToll *           createToll(Payload *);
        inline JSCBridgeToll *    toll()
        {
            assert(m_sharedData);
            assert(m_sharedData->m_payload.m_toll);
            if (!m_sharedData || !m_sharedData->m_payload.m_toll)
                abort();
            return m_sharedData->m_payload.m_toll;
        }

        // private APIs
    private:
        struct SharedData {
            StaticVMData      m_staticVMData;
            Payload           m_payload;
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

#endif // ENABLE(DETACHED_JIT)

#if BUILDING_DETACHED_JIT
#define ASSERT_NOT_REACHED_BY_DETACHED_JIT() do { abort(); } while(0)
#else
#define ASSERT_NOT_REACHED_BY_DETACHED_JIT() do {} while(0)
#endif

#endif // #ifndef JSCBridge_h
