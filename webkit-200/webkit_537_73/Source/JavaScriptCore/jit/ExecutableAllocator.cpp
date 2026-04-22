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

#include "ExecutableAllocator.h"

#include "DemandExecutableAllocator.h"
#include "JSCBridge.h"
#include "SuperRegion.h"

#if ENABLE(EXECUTABLE_ALLOCATOR_DEMAND)
#include "CodeProfiling.h"
#include <wtf/HashSet.h>
#include <wtf/MetaAllocator.h>
#include <wtf/PageReservation.h>
#if ENABLE(ASSEMBLER_WX_EXCLUSIVE)
#include <wtf/PassOwnPtr.h>
#endif
#include <wtf/ThreadingPrimitives.h>
#include <wtf/VMTags.h>
#endif

#if OS(PSP2)
#include <manx/Memblock.h>
#endif

// Uncomment to create an artificial executable memory usage limit. This limit
// is imperfect and is primarily useful for testing the VM's ability to handle
// out-of-executable-memory situations.
// #define EXECUTABLE_MEMORY_LIMIT 1000000

#if ENABLE(ASSEMBLER)

using namespace WTF;

namespace JSC {

#if ENABLE(EXECUTABLE_ALLOCATOR_DEMAND)

DemandExecutableAllocator::DemandExecutableAllocator()
#if ENABLE(DETACHED_JIT)
    : MetaAllocator(jitAllocationGranule, MetaAllocator::e_DemandAllocatorType)
#else
    : MetaAllocator(jitAllocationGranule)
#endif
{
    MutexLocker lock(allocatorsMutex());
    allocators().add(this);
    // Don't preallocate any memory here.
}
    
DemandExecutableAllocator::~DemandExecutableAllocator()
{
    {
        MutexLocker lock(allocatorsMutex());
        allocators().remove(this);
    }
    for (unsigned i = 0; i < reservations.size(); ++i)
        reservations.at(i).deallocate();

#if ENABLE(DETACHED_JIT)
    RELEASE_ASSERT(m_type == MetaAllocator::e_DemandAllocatorType);
    m_type = MetaAllocator::e_MetaAllocatorBaseType;
#endif
}

#if ENABLE(DETACHED_JIT)
void DemandExecutableAllocator::DETACHED_JIT_DTOR()
{
    delete this;
}
#endif

size_t DemandExecutableAllocator::bytesAllocatedByAllAllocators()
{
    size_t total = 0;
    MutexLocker lock(allocatorsMutex());
    for (HashSet<DemandExecutableAllocator*>::const_iterator allocator = allocators().begin(); allocator != allocators().end(); ++allocator)
        total += (*allocator)->bytesAllocated();
    return total;
}

size_t DemandExecutableAllocator::bytesCommittedByAllocactors()
{
    size_t total = 0;
    MutexLocker lock(allocatorsMutex());
    for (HashSet<DemandExecutableAllocator*>::const_iterator allocator = allocators().begin(); allocator != allocators().end(); ++allocator)
        total += (*allocator)->bytesCommitted();
    return total;
}

#if ENABLE(META_ALLOCATOR_PROFILE)
void DemandExecutableAllocator::dumpProfileFromAllAllocators()
{
    MutexLocker lock(allocatorsMutex());
    for (HashSet<DemandExecutableAllocator*>::const_iterator allocator = allocators().begin(); allocator != allocators().end(); ++allocator)
        (*allocator)->dumpProfile();
}
#endif

void* DemandExecutableAllocator::allocateNewSpace(size_t& numPages)
{
    size_t newNumPages = (((numPages * pageSize() + JIT_ALLOCATOR_LARGE_ALLOC_SIZE - 1) / JIT_ALLOCATOR_LARGE_ALLOC_SIZE * JIT_ALLOCATOR_LARGE_ALLOC_SIZE) + pageSize() - 1) / pageSize();

    ASSERT(newNumPages >= numPages);

    numPages = newNumPages;

#ifdef EXECUTABLE_MEMORY_LIMIT
    if (bytesAllocatedByAllAllocators() >= EXECUTABLE_MEMORY_LIMIT)
        return 0;
#endif

    PageReservation reservation = PageReservation::reserve(numPages * pageSize(), OSAllocator::JSJITCodePages, EXECUTABLE_POOL_WRITABLE, true);
    RELEASE_ASSERT(reservation);

    reservations.append(reservation);

    return reservation.base();
}

void DemandExecutableAllocator::notifyNeedPage(void* page)
{
    OSAllocator::commit(page, pageSize(), EXECUTABLE_POOL_WRITABLE, true);
}

void DemandExecutableAllocator::notifyPageIsFree(void* page)
{
    OSAllocator::decommit(page, pageSize());
}

#if ENABLE(ASSEMBLER_WX_EXCLUSIVE)

void ExecutableAllocator::initializeAllocator()
{
}

#else

static DemandExecutableAllocator* gAllocator;

#if ENABLE(DETACHED_JIT)
#if BUILDING_DETACHED_JIT

void ExecutableAllocator::setMetaAllocator(MetaAllocator* metaAllocator)
{
#if !BUILDING_DETACHED_JIT
    ASSERT_NOT_REACHED();
#else
    ASSERT(!gAllocator);
    ASSERT(metaAllocator);
    gAllocator = reinterpret_cast<DemandExecutableAllocator*>(metaAllocator);
#endif
}

#else

MetaAllocator* ExecutableAllocator::metaAllocator()
{
    if (!gAllocator) {
        initializeAllocator();
    }
    ASSERT(gAllocator);
    return gAllocator;
}

#endif
#endif // #if ENABLE(DETACHED_JIT)

namespace {
static inline DemandExecutableAllocator* allocator()
{
    return gAllocator;
}
}

#if !(ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT)
void ExecutableAllocator::initializeAllocator()
{
    ASSERT(!gAllocator);
    gAllocator = new DemandExecutableAllocator();
    CodeProfiling::notifyAllocator(gAllocator);
}
#endif

#endif

ExecutableAllocator::ExecutableAllocator(VM&)
#if ENABLE(ASSEMBLER_WX_EXCLUSIVE)
    : m_allocator(adoptPtr(new  DemandExecutableAllocator()))
#endif
{
    ASSERT(allocator());
}

ExecutableAllocator::~ExecutableAllocator()
{
}

bool ExecutableAllocator::isValid() const
{
    return true;
}

bool ExecutableAllocator::underMemoryPressure()
{
#ifdef EXECUTABLE_MEMORY_LIMIT
    return DemandExecutableAllocator::bytesAllocatedByAllAllocators() > EXECUTABLE_MEMORY_LIMIT / 2;
#else
    return false;
#endif
}

double ExecutableAllocator::memoryPressureMultiplier(size_t addedMemoryUsage)
{
    double result;
#ifdef EXECUTABLE_MEMORY_LIMIT
    size_t bytesAllocated = DemandExecutableAllocator::bytesAllocatedByAllAllocators() + addedMemoryUsage;
    if (bytesAllocated >= EXECUTABLE_MEMORY_LIMIT)
        bytesAllocated = EXECUTABLE_MEMORY_LIMIT;
    result = static_cast<double>(EXECUTABLE_MEMORY_LIMIT) /
        (EXECUTABLE_MEMORY_LIMIT - bytesAllocated);
#else
    UNUSED_PARAM(addedMemoryUsage);
    result = 1.0;
#endif
    if (result < 1.0)
        result = 1.0;
    return result;

}

PassRefPtr<ExecutableMemoryHandle> ExecutableAllocator::allocate(VM&, size_t sizeInBytes, void* ownerUID, JITCompilationEffort effort)
{
    RefPtr<ExecutableMemoryHandle> result = allocator()->allocate(sizeInBytes, ownerUID);
    RELEASE_ASSERT(result || effort != JITCompilationMustSucceed);
    return result.release();
}

size_t ExecutableAllocator::committedByteCount()
{
    return DemandExecutableAllocator::bytesCommittedByAllocactors();
}

#if ENABLE(META_ALLOCATOR_PROFILE)
void ExecutableAllocator::dumpProfile()
{
    DemandExecutableAllocator::dumpProfileFromAllAllocators();
}
#endif

#endif // ENABLE(EXECUTABLE_ALLOCATOR_DEMAND)

#if ENABLE(ASSEMBLER_WX_EXCLUSIVE)

#if OS(WINDOWS) || OS(ORBIS)

#error "ASSEMBLER_WX_EXCLUSIVE not yet suported on this platform."

#elif OS(PSP2)

void ExecutableAllocator::reprotectRegion(void* start, size_t size, ProtectionSetting setting)
{
    Manx::Memblock::setWritable(setting == ExecutableAllocator::Writable);
}

#else

void ExecutableAllocator::reprotectRegion(void* start, size_t size, ProtectionSetting setting)
{
    size_t pageSize = WTF::pageSize();

    // Calculate the start of the page containing this region,
    // and account for this extra memory within size.
    intptr_t startPtr = reinterpret_cast<intptr_t>(start);
    intptr_t pageStartPtr = startPtr & ~(pageSize - 1);
    void* pageStart = reinterpret_cast<void*>(pageStartPtr);
    size += (startPtr - pageStartPtr);

    // Round size up
    size += (pageSize - 1);
    size &= ~(pageSize - 1);

    mprotect(pageStart, size, (setting == Writable) ? PROTECTION_FLAGS_RW : PROTECTION_FLAGS_RX);
}

#endif
#endif

}

#if ENABLE(DETACHED_JIT)

namespace WTF {

void MetaAllocator::DETACHED_JIT_DTOR()
{
    switch (m_type) {
    case e_MetaAllocatorBaseType: break; // no 'delete this' because MetaAllocator is an abstract class
    case e_DemandAllocatorType:   reinterpret_cast<JSC::DemandExecutableAllocator*>(this)->DETACHED_JIT_DTOR(); return;
    case e_FixedAllocatorType:    break; // not supported yet
    
    case e_SuperRegionType:
#if !BUILDING_DETACHED_JIT
        reinterpret_cast<JSC::SuperRegion*>(this)->DETACHED_JIT_DTOR();
#endif
        ASSERT_NOT_REACHED_BY_DETACHED_JIT();
        return;
    }

    RELEASE_ASSERT_NOT_REACHED();
    return;
}

void * MetaAllocator::allocateNewSpace(size_t& numPages)
{
    switch (m_type) {
    case e_MetaAllocatorBaseType: break;
    case e_DemandAllocatorType:   return reinterpret_cast<JSC::DemandExecutableAllocator*>(this)->allocateNewSpace(numPages);
    case e_FixedAllocatorType:    break;

    case e_SuperRegionType:
#if !BUILDING_DETACHED_JIT
        return reinterpret_cast<JSC::SuperRegion*>(this)->allocateNewSpace(numPages);
#endif
        ASSERT_NOT_REACHED_BY_DETACHED_JIT();
        return NULL;
    }

    RELEASE_ASSERT(false);
    return NULL;
}

void MetaAllocator::notifyNeedPage(void* page)
{
    switch (m_type) {
    case e_MetaAllocatorBaseType: break;
    case e_DemandAllocatorType:   reinterpret_cast<JSC::DemandExecutableAllocator*>(this)->notifyNeedPage(page); return;
    case e_FixedAllocatorType:    break; // not implemented yet

    case e_SuperRegionType:
#if !BUILDING_DETACHED_JIT
        reinterpret_cast<JSC::SuperRegion*>(this)->notifyNeedPage(page);
#endif
        ASSERT_NOT_REACHED_BY_DETACHED_JIT();
        return;
    }
    RELEASE_ASSERT(false);
    return;
}

void MetaAllocator::notifyPageIsFree(void* page)
{
    switch (m_type) {
    case e_MetaAllocatorBaseType: break;
    case e_DemandAllocatorType:   reinterpret_cast<JSC::DemandExecutableAllocator*>(this)->notifyPageIsFree(page); return;
    case e_FixedAllocatorType:    break; // not implemented yet

    case e_SuperRegionType:
#if !BUILDING_DETACHED_JIT
        reinterpret_cast<JSC::SuperRegion*>(this)->notifyPageIsFree(page);
#endif
        ASSERT_NOT_REACHED_BY_DETACHED_JIT();
        return;
    }

    RELEASE_ASSERT(false);
    return;
}

} // namespace WTF

#endif


#endif // HAVE(ASSEMBLER)
