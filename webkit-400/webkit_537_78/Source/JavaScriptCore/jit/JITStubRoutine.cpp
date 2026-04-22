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
#include "JITStubRoutine.h"

#if ENABLE(JIT)

#include "JSObject.h"

#include "SlotVisitor.h"

#if ENABLE(DETACHED_JIT)
#include "GCAwareJITStubRoutine.h"
#endif

namespace JSC {

JITStubRoutine::~JITStubRoutine()
{
#if ENABLE(DETACHED_JIT)
    RELEASE_ASSERT(m_stubRoutineType == e_StubRoutineBaseType);
#endif
}

#if ENABLE(DETACHED_JIT)
void JITStubRoutine::DETACHED_JIT_DTOR()
{
    switch (m_stubRoutineType) {
    case e_GCAwareStubRoutineType:
        reinterpret_cast<GCAwareJITStubRoutine*>(this)->DETACHED_JIT_DTOR();
        return;
    case e_StubRoutineBaseType:
        delete this;
        return;
    case e_InvalidStubRoutineType:
        ASSERT_NOT_REACHED();
        return;
    }
}
#endif

void JITStubRoutine::observeZeroRefCount()
{
    RELEASE_ASSERT(!m_refCount);

#if ENABLE(DETACHED_JIT)

    switch (m_stubRoutineType) {
    case e_GCAwareStubRoutineType:
        reinterpret_cast<GCAwareJITStubRoutine*>(this)->observeZeroRefCount();
        return;
    case e_StubRoutineBaseType:
        DETACHED_JIT_VIRTUAL_DELETE(this);
        return;
    case e_InvalidStubRoutineType:
        ASSERT_NOT_REACHED();
        return;
    }
 
#else

    delete this;

#endif
}

} // namespace JSC

#endif // ENABLE(JIT)

