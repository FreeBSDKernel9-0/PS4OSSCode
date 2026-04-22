/*
 * Copyright (C) 2012 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include "config.h"
#include "GCAwareJITStubRoutine.h"

#if ENABLE(JIT)

#include "Heap.h"
#include "VM.h"
#include "Operations.h"
#include "SlotVisitor.h"
#include "Structure.h"

#if ENABLE(DETACHED_JIT)
#include "ClosureCallStubRoutine.h"
#endif

namespace JSC {

#if ENABLE(DETACHED_JIT)
GCAwareJITStubRoutine::GCAwareJITStubRoutine(
    const MacroAssemblerCodeRef& code, VM& vm, GCAwareJITStubRoutineType type, bool isClosureCall)
    : JITStubRoutine(code, JITStubRoutine::e_GCAwareStubRoutineType)
#else
GCAwareJITStubRoutine::GCAwareJITStubRoutine(
    const MacroAssemblerCodeRef& code, VM& vm, bool isClosureCall)
    : JITStubRoutine(code)
#endif
    , m_mayBeExecuting(false)
    , m_isJettisoned(false)
    , m_isClosureCall(isClosureCall)
#if ENABLE(DETACHED_JIT)
    , m_gcAwareStubRoutineType(type)
#endif
{
    vm.heap.m_jitStubRoutines.add(this);
}

GCAwareJITStubRoutine::~GCAwareJITStubRoutine()
{
#if ENABLE(DETACHED_JIT)
    RELEASE_ASSERT(m_gcAwareStubRoutineType == e_GCAwareStubRoutineBaseType);
    RELEASE_ASSERT(m_stubRoutineType == e_GCAwareStubRoutineType);
    m_stubRoutineType = e_StubRoutineBaseType;
#endif
}

#if ENABLE(DETACHED_JIT)
void GCAwareJITStubRoutine::DETACHED_JIT_DTOR()
{
    RELEASE_ASSERT(m_stubRoutineType == e_GCAwareStubRoutineType);
    switch (m_gcAwareStubRoutineType) {
    case e_MarkingGCAwareType:
        reinterpret_cast<MarkingGCAwareJITStubRoutineWithOneObject*>(this)->DETACHED_JIT_DTOR();
        break;
    case e_ClosureCallType:
        reinterpret_cast<ClosureCallStubRoutine*>(this)->DETACHED_JIT_DTOR();
        break;
    case e_GCAwareStubRoutineBaseType:
        delete this;
        break;
    case e_InvalidGCAwareType:
        ASSERT_NOT_REACHED();
        break;
    }
}
#endif

void GCAwareJITStubRoutine::observeZeroRefCount()
{
    if (m_isJettisoned) {
        // This case is needed for when the system shuts down. It may be that
        // the JIT stub routine set gets deleted before we get around to deleting
        // this guy. In that case the GC informs us that we're jettisoned already
        // and that we should delete ourselves as soon as the ref count reaches
        // zero.
        DETACHED_JIT_VIRTUAL_DELETE(this);
        return;
    }
    
    RELEASE_ASSERT(!m_refCount);

    m_isJettisoned = true;
}

void GCAwareJITStubRoutine::deleteFromGC()
{
    ASSERT(m_isJettisoned);
    ASSERT(!m_refCount);
    ASSERT(!m_mayBeExecuting);

    DETACHED_JIT_VIRTUAL_DELETE(this);
}

#if !(ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT)
void GCAwareJITStubRoutine::markRequiredObjectsInternal(SlotVisitor& slot)
{
#if ENABLE(DETACHED_JIT)
    switch (m_gcAwareStubRoutineType) {
    case e_MarkingGCAwareType:
        reinterpret_cast<MarkingGCAwareJITStubRoutineWithOneObject*>(this)->markRequiredObjectsInternal(slot);
        break;
    case e_ClosureCallType:
        reinterpret_cast<ClosureCallStubRoutine*>(this)->markRequiredObjectsInternal(slot);
        break;
    case e_GCAwareStubRoutineBaseType:
        break;
    case e_InvalidGCAwareType:
        ASSERT_NOT_REACHED();
        break;
    }
#endif
}
#endif

MarkingGCAwareJITStubRoutineWithOneObject::MarkingGCAwareJITStubRoutineWithOneObject(
    const MacroAssemblerCodeRef& code, VM& vm, const JSCell* owner,
    JSCell* object)
#if ENABLE(DETACHED_JIT)
    : GCAwareJITStubRoutine(code, vm, e_MarkingGCAwareType)
#else
    : GCAwareJITStubRoutine(code, vm)
#endif
    , m_object(vm, owner, object)
{
}

MarkingGCAwareJITStubRoutineWithOneObject::~MarkingGCAwareJITStubRoutineWithOneObject()
{
#if ENABLE(DETACHED_JIT)
    RELEASE_ASSERT(m_gcAwareStubRoutineType == e_MarkingGCAwareType);
    m_gcAwareStubRoutineType = e_GCAwareStubRoutineBaseType;
#endif
}

#if ENABLE(DETACHED_JIT)
void MarkingGCAwareJITStubRoutineWithOneObject::DETACHED_JIT_DTOR()
{
    RELEASE_ASSERT(m_gcAwareStubRoutineType == e_MarkingGCAwareType);
    delete this;
}
#endif

#if !(ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT)
void MarkingGCAwareJITStubRoutineWithOneObject::markRequiredObjectsInternal(SlotVisitor& visitor)
{
    visitor.append(&m_object);
}
#endif

PassRefPtr<JITStubRoutine> createJITStubRoutine(
    const MacroAssemblerCodeRef& code,
    VM& vm,
    const JSCell*,
    bool makesCalls)
{
#if ENABLE(DETACHED_JIT)

    if (!makesCalls)
        return adoptRef(new JITStubRoutine(code, JITStubRoutine::e_StubRoutineBaseType));
    return static_pointer_cast<JITStubRoutine>(
        adoptRef(new GCAwareJITStubRoutine(code, vm, GCAwareJITStubRoutine::e_GCAwareStubRoutineBaseType)));

#else

    if (!makesCalls)
        return adoptRef(new JITStubRoutine(code));
    return static_pointer_cast<JITStubRoutine>(
        adoptRef(new GCAwareJITStubRoutine(code, vm)));

#endif

}

PassRefPtr<JITStubRoutine> createJITStubRoutine(
    const MacroAssemblerCodeRef& code,
    VM& vm,
    const JSCell* owner,
    bool makesCalls,
    JSCell* object)
{
#if ENABLE(DETACHED_JIT)

    if (!makesCalls)
        return adoptRef(new JITStubRoutine(code, JITStubRoutine::e_StubRoutineBaseType));

#else

    if (!makesCalls)
        return adoptRef(new JITStubRoutine(code));

#endif

    return static_pointer_cast<JITStubRoutine>(
        adoptRef(new MarkingGCAwareJITStubRoutineWithOneObject(code, vm, owner, object)));
}

} // namespace JSC

#endif // ENABLE(JIT)

