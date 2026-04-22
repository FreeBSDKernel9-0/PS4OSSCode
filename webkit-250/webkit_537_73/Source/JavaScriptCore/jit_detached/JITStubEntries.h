// Copyright (C) 2012 Sony Computer Entertainment Inc.
// All Rights Reserved.

#ifndef JITStubEntries_h
#define JITStubEntries_h

#include "JITStubEntryHelper.h"
#include "RemotePointerWrapper.h"

#if BUILDING_DETACHED_JIT
#include "DFGOperationTypes.h"
#include "JITStubTypes.h"
#endif

#if ENABLE(DETACHED_JIT)
#   if BUILDING_DETACHED_JIT
#       define REMOTE_VAR_PTR(var)                              (s_##var##_ptr)
#       define REMOTE_VAR_VALUE(var)                            (RemoteStubs::var)
#       define DECLARE_REMOTE_FUNCTION(function)                extern RemotePointerWrapper function
#       define DECLARE_REMOTE_VAR(type, var)                    namespace RemoteStubs { extern RemotePointerWrapper var; }
#       define DECLARE_REMOTE_VALUE(type, var)                  namespace RemoteStubs { extern type var; }
#       define DEFINE_REMOTE_VAR(type, var, initializer)
#       define DEFINE_REMOTE_VAR_PTR(type, var)                 type * const REMOTE_VAR_PTR(var)(reinterpret_cast<type *>(&RemoteStubs::var))
#       define DEFINE_STATIC_CLASSINFO(classname)               static ClassInfo const * const s##classname##ClassInfo(JSC::classname##Stub::s_info); ASSERT(s##classname##ClassInfo); UNUSED_PARAM(s##classname##ClassInfo)
#   else // #if BUILDING_DETACHED_JIT
#       define REMOTE_VAR_PTR(var)                              (void*)0x0bad0bad
#       define REMOTE_VAR_VALUE(var)                            (var)
#       define DECLARE_REMOTE_FUNCTION(function)
#       define DECLARE_REMOTE_VAR(type, var)                    extern type var
#       define DECLARE_REMOTE_VALUE(type, var)                  extern type var
#       define DEFINE_REMOTE_VAR(type, var, initializer)        type var = initializer
#       define DEFINE_REMOTE_VAR_PTR(type, var)
#       define DEFINE_STATIC_CLASSINFO(classname)               static ClassInfo const * const s##classname##ClassInfo(&JSC::classname::s_info); ASSERT(s##classname##ClassInfo); UNUSED_PARAM(s##classname##ClassInfo)
#   endif // #if BUILDING_DETACHED_JIT
#else // #if ENABLE(DETACHED_JIT)
#   define REMOTE_VAR_PTR(var)                                  (&(var))
#   define REMOTE_VAR_VALUE(var)                                (var)
#   define DECLARE_REMOTE_FUNCTION(function)
#   define DECLARE_REMOTE_VAR(type, var)                        extern type var
#   define DECLARE_REMOTE_VALUE(type, var)                      extern type var
#   define DEFINE_REMOTE_VAR(type, var, initializer)            type var = initializer
#   define DEFINE_REMOTE_VAR_PTR(type, var)
#   define DEFINE_STATIC_CLASSINFO(classname)                   static ClassInfo const * const s##classname##ClassInfo(&JSC::classname::s_info); ASSERT(s##classname##ClassInfo != NULL); UNUSED_PARAM(s##classname##ClassInfo)
#endif // #if ENABLE(DETACHED_JIT)

// scoped definition for how cti stubs and classinfo stubs should be declared
#if ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT
#   define CTI_STUB_ENTRY(returnType, symbol) extern returnType symbol
#   define CLASSINFO_STUB_ENTRY(classname) namespace classname##Stub { extern RemoteClassInfoPtr s_info; }
#else // #if ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT
#   define CTI_STUB_ENTRY(returnType, symbol)
#   define CLASSINFO_STUB_ENTRY(classname)
#endif // #if ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT

// the list of symbols defined on the VM side which the detached compiler needs
namespace JSC {

    // These are needed by the ThunkGenerators, DFG JIT, and others...
    DECLARE_REMOTE_VAR(const double, oneConstant);
    DECLARE_REMOTE_VAR(const double, zeroConstant);
    DECLARE_REMOTE_VAR(const double, halfConstant);
    DECLARE_REMOTE_VAR(const double, negativeHalfConstant);
    DECLARE_REMOTE_VAR(const double, negativeZeroConstant);
    DECLARE_REMOTE_VAR(const double, NaN);
    DECLARE_REMOTE_VAR(const double, twoToThe32);
    DECLARE_REMOTE_VAR(const double, byteMax);

    namespace Yarr { DECLARE_REMOTE_VALUE(const char *, regExp_spacesData); }
    namespace Yarr { DECLARE_REMOTE_VALUE(const char *, regExp_wordcharData); }

    DECLARE_REMOTE_FUNCTION(ctiVMThrowTrampoline);

    CTI_STUB_ENTRIES;
#if ENABLE(LLINT)
    CTI_STUB_ENTRIES_LLINT;
#endif
#if ENABLE(DFG_JIT)
    CTI_STUB_ENTRIES_DFG;
    namespace DFG { CTI_STUB_ENTRIES_DFG_OPERATIONS }
#endif
    CLASSINFO_STUB_ENTRIES;

}

#undef  CTI_STUB_ENTRY
#undef  CLASSINFO_STUB_ENTRY

#define DEFINE_STATIC_sArgumentsClassInfo           DEFINE_STATIC_CLASSINFO(Arguments)
#define DEFINE_STATIC_sFunctionExecutableClassInfo  DEFINE_STATIC_CLASSINFO(FunctionExecutable)
#define DEFINE_STATIC_sJSArrayClassInfo             DEFINE_STATIC_CLASSINFO(JSArray)
#define DEFINE_STATIC_sJSFinalObjectClassInfo       DEFINE_STATIC_CLASSINFO(JSFinalObject)
#define DEFINE_STATIC_sJSFunctionClassInfo          DEFINE_STATIC_CLASSINFO(JSFunction)
#define DEFINE_STATIC_sJSObjectClassInfo            DEFINE_STATIC_CLASSINFO(JSObject)
#define DEFINE_STATIC_sJSStringClassInfo            DEFINE_STATIC_CLASSINFO(JSString)
#define DEFINE_STATIC_sStringObjectClassInfo        DEFINE_STATIC_CLASSINFO(StringObject)
#define DEFINE_STATIC_sStructureClassInfo           DEFINE_STATIC_CLASSINFO(Structure)

#endif // #ifndef JITStubEntries_h
