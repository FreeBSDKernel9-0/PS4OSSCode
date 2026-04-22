/*
 * Copyright (C) 2013 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DemandExecutableAllocator_h
#define DemandExecutableAllocator_h

#if ENABLE(EXECUTABLE_ALLOCATOR_DEMAND)

#include <wtf/HashSet.h>
#include <wtf/MetaAllocator.h>
#include <wtf/PageReservation.h>
#include <JITBridge.h>

namespace JSC {

class DemandExecutableAllocator : public WTF::MetaAllocator {
#if ENABLE(DETACHED_JIT)
    DETACHED_JIT_MAKE_SHARED_DATA_ALLOCATED;
    friend class WTF::MetaAllocator;
#endif

public:
    DemandExecutableAllocator();
    DETACHED_JIT_VIRTUAL_DTOR ~DemandExecutableAllocator();

public:
    static size_t bytesAllocatedByAllAllocators();
    static size_t bytesCommittedByAllocactors();
#if ENABLE(META_ALLOCATOR_PROFILE)
    static void dumpProfileFromAllAllocators();
#endif

protected:
    DETACHED_JIT_VIRTUAL void * allocateNewSpace(size_t& numPages);    
    DETACHED_JIT_VIRTUAL void notifyNeedPage(void* page);
    DETACHED_JIT_VIRTUAL void notifyPageIsFree(void* page);

private:
    Vector<PageReservation, 16> reservations;
    static HashSet<DemandExecutableAllocator*>& allocators()
    {
        DEFINE_STATIC_LOCAL(HashSet<DemandExecutableAllocator*>, sAllocators, ());
        return sAllocators;
    }

    static Mutex& allocatorsMutex()
    {
        DEFINE_STATIC_LOCAL(Mutex, mutex, ());
        return mutex;
    }
};

} // namespace JSC

#endif
#endif // SuperRegion_h
