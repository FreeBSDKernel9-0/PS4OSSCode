/*
 * Copyright (C) 2008 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include "config.h"
#include "StructureChain.h"

#include "JSObject.h"
#include "Operations.h"
#include "Structure.h"
#include <wtf/RefPtr.h>

namespace JSC {
    
#if !(ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT)

ClassInfo StructureChain::s_info = { "StructureChain", 0, 0, 0, CREATE_METHOD_TABLE(StructureChain) };

#endif

StructureChain::StructureChain(VM& vm, Structure* structure)
    : JSCell(vm, structure)
{
}

#if !(ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT)

void StructureChain::destroy(JSCell* cell)
{
#if ENABLE(JIT) && ENABLE(DETACHED_JIT)
    // we need to cleanup the array ourselves here as we cannot allow it to be destroyed by a call to delete[]
    StructureChain * me(static_cast<StructureChain*>(cell));

    WriteBarrier<Structure> * structureVector(me->m_vector.leakPtr());
    void * structureVectorBuffer(reinterpret_cast<size_t*>(structureVector) - 1);

    size_t length(*(reinterpret_cast<size_t*>(structureVector) - 1));
    for (size_t i = 0; i < length; ++i) {
        structureVector->WriteBarrier<Structure>::~WriteBarrier();
        ++structureVector;
    }
    JITSharedDataMemory::shared_free(structureVectorBuffer);
#endif

    static_cast<StructureChain*>(cell)->StructureChain::~StructureChain();
}

void StructureChain::visitChildren(JSCell* cell, SlotVisitor& visitor)
{
    StructureChain* thisObject = jsCast<StructureChain*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, &s_info);
    ASSERT(thisObject->structure()->typeInfo().overridesVisitChildren());
    size_t i = 0;
    while (thisObject->m_vector[i])
        visitor.append(&thisObject->m_vector[i++]);
}

#endif // #if !(ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT)

} // namespace JSC
