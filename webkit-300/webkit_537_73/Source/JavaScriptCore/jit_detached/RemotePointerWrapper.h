// Copyright (C) 2012 Sony Computer Entertainment Inc.
// All Rights Reserved.

#ifndef RemotePointerWrapper_h
#define RemotePointerWrapper_h

#if ENABLE(DETACHED_JIT)

#include "jit/JITStubTypes.h"
#include "jit_detached/JSCBridge.h"
#include "runtime/JSCJSValue.h"

#include <assert.h>

namespace JSC {
    struct ClassInfo;
    class JSObject;

    class RemotePointerWrapper {

    public:
        static uintptr_t const s_invalidAddress = 0x0;

    public:
        operator void *()                                 { assert(m_pointer != (void*)s_invalidAddress); return m_pointer; }
        operator void *() const                           { assert(m_pointer != (void*)s_invalidAddress); return m_pointer; }
        void *       operator&()                          { assert(m_pointer != (void*)s_invalidAddress); return m_pointer; }
        void const * operator&() const                    { assert(m_pointer != (void*)s_invalidAddress); return m_pointer; }
        RemotePointerWrapper & operator=(uintptr_t value) { m_pointer = reinterpret_cast<void *>(value);  return *this; }

    protected:
        void * m_pointer;
    };

    template <class FunctionPtrSignature>
    class RemoteFunctionWrapper {
    public:
        operator void *()                                 { assert(m_function != 0); return reinterpret_cast<void*>(m_function); }
        operator void *() const                           { assert(m_function != 0); return reinterpret_cast<void*>(m_function); }
        operator FunctionPtrSignature()                   { assert(m_function != 0); return m_function; }
        operator FunctionPtrSignature() const             { assert(m_function != 0); return m_function; }

    private:
        friend void JSCBridge::initializeCompilerSharedData();
        RemoteFunctionWrapper & operator=(uintptr_t func) { m_function = reinterpret_cast<FunctionPtrSignature>(func); return *this; } // TODO remove reinterpret_cast here because it defeats the purpose of having this class templetized for type safety

    private:
        FunctionPtrSignature m_function;
    };

    // provided for type safety.  each one corresponds to the enum values defined in JITStubCall's m_returnType (see JITStubCall.h)
    typedef RemotePointerWrapper RemoteFunctionReturningVoid;
    typedef RemotePointerWrapper RemoteFunctionReturningVoidPtr;
    typedef RemotePointerWrapper RemoteFunctionReturningInt;
    typedef RemotePointerWrapper RemoteFunctionReturningValue;
    typedef RemotePointerWrapper RemoteFunctionReturningCell;

    typedef RemoteFunctionWrapper<int            (*)(STUB_ARGS_DECLARATION)> RemoteCtiFunctionReturningInt;
    typedef RemoteFunctionWrapper<JSObject *     (*)(STUB_ARGS_DECLARATION)> RemoteCtiFunctionReturningObject;
    typedef RemoteFunctionWrapper<EncodedJSValue (*)(STUB_ARGS_DECLARATION)> RemoteCtiFunctionReturningValue;
    typedef RemoteFunctionWrapper<void           (*)(STUB_ARGS_DECLARATION)> RemoteCtiFunctionReturningVoid;
    typedef RemoteFunctionWrapper<void *         (*)(STUB_ARGS_DECLARATION)> RemoteCtiFunctionReturningVoidPtr;

    class RemoteClassInfoPtr : public RemotePointerWrapper {
    public:
        operator ClassInfo * ()                         { return reinterpret_cast<ClassInfo *>(m_pointer); }
        operator ClassInfo * () const                   { return reinterpret_cast<ClassInfo *>(m_pointer); }
        ClassInfo & operator *()                        { return *(reinterpret_cast<ClassInfo *>(m_pointer)); }
        RemoteClassInfoPtr & operator=(uintptr_t value) { m_pointer = reinterpret_cast<void *>(value); return *this; }
    };


} // namespace JSC

#endif // #if ENABLE(DETACHED_JIT)

#endif // #ifndef RemotePointerWrapper_h
