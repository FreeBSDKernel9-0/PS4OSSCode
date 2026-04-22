/*
 * Copyright (C) 2010 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer. 
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution. 
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "GCActivityCallback.h"
#include "Heap.h"

#include <wtf/text/CString.h>
#include <wtf/text/StringHash.h>
#include <wtf/text/WTFString.h>
#include <wtf/HashCountedSet.h>
#include <wtf/HashMap.h>
#include <wtf/HashTraits.h>

#if OS(ORBIS)
#define ENABLE_SIMPLE_ACTIVITY_CALLBACK 1
#endif

#include "JSMemoryStatsSCE.h"

namespace {

#if ENABLE(SIMPLE_ACTIVITY_CALLBACK)
    using namespace JSC;
    using namespace WTF;

    struct ElapsedTimer {
        ElapsedTimer(char const * envVar)
            : m_frequency(0)
            , m_prevTime(time(NULL))
            , m_elapsed(0)
            , m_prevElapsed(0)
            , m_enabled(false)
        {
            time_t frequency(0);
            if (envVar) {
                char * frequencyValue(getenv(envVar));
                if (frequencyValue) {
                    frequency = atoi(frequencyValue);
                    if (frequency < 0)
                        frequency = 0;
                }
            }
            initialize(frequency);
        }

        ElapsedTimer(time_t frequency)
            : m_frequency(0)
            , m_prevTime(time(NULL))
            , m_elapsed(0)
            , m_prevElapsed(0)
            , m_enabled(false)
        {
            initialize(frequency);
        }

        void initialize(time_t frequency)
        {
            m_frequency = frequency;
            m_enabled = frequency > 0;
        }

        inline bool update()
        {
            if (__builtin_expect(m_enabled, 0)) {
                time_t currTime(time(NULL));
                m_elapsed  += currTime - m_prevTime;
                m_prevTime = currTime;

                if (m_elapsed < m_frequency) {
                    return false;
                }

                m_prevElapsed = m_elapsed;
                m_elapsed = 0;
                return true;
            }

            return false;
        }

        time_t m_frequency;
        time_t m_prevTime;
        time_t m_elapsed;
        time_t m_prevElapsed;
        bool   m_enabled;
    };

    typedef HashMap<String, unsigned> TypeCountMap;
    typedef pair<String, unsigned>    TypeCountPair;
    typedef Vector<TypeCountPair>     TypeCountVector;

    inline bool NormalizedTypeCountSetComparator(const TypeCountPair & a, const TypeCountPair & b)
    {
        return a.second > b.second;
    }

    void printObjectTypes(TypeCountSet * typeCounts)
    {
        TypeCountSet::const_iterator typeIter(typeCounts->begin());
        TypeCountSet::const_iterator typeEnd(typeCounts->end());

        // normalize (TypeCountSet's hash function uses the pointer value instead of the string content)
        TypeCountMap normalizedMap;
        while (typeIter != typeEnd) {
            normalizedMap.add(typeIter->first, 0).iterator->second += typeIter->second;
            ++typeIter;
        };

        // vectorize and sort
        TypeCountVector normalizedVector(normalizedMap.size());
        TypeCountMap::const_iterator mapIter(normalizedMap.begin());
        TypeCountMap::const_iterator mapEnd(normalizedMap.end());
        for (unsigned i = 0; mapIter != mapEnd; ++mapIter, ++i)
            normalizedVector[i] = *mapIter;
        std::sort(normalizedVector.begin(), normalizedVector.end(), NormalizedTypeCountSetComparator);

        // output
        TypeCountVector::const_iterator vectorIter(normalizedVector.begin());
        TypeCountVector::const_iterator vectorEnd(normalizedVector.end());
        size_t count(0);
        while (vectorIter != vectorEnd) {
            if (vectorIter->second < 100) {
                break;
            }
            fprintf(stderr, "\t\t%8zd : %s\n", vectorIter->second, vectorIter->first.ascii().data());
            ++vectorIter; ++count;
        }

        // tally remaining types that have < 100
        size_t total(0);
        while (vectorIter != vectorEnd) {
            total += vectorIter->second;
            ++vectorIter;
        }
        fprintf(stderr, "\t\t   < 100 : (%zd unique types, total %zd)\n", normalizedVector.size() - count, total);

    }

    static ElapsedTimer gcTimer("JSCORE_ACTIVITY_FREQ_GC");
    static ElapsedTimer objectCountTimer("JSCORE_ACTIVITY_FREQ_OBJECTCOUNT");

    inline void reportCurrentObjectCount(JSC::Heap * heap) {
        if (__builtin_expect(objectCountTimer.update(), 0)) {
            fprintf(stderr, "[JavaScriptCore] object stats\n");
            
            {
                fprintf(stderr, "\tobjects   (global) : %zd (%zd)\n", heap->objectCount(true), heap->globalObjectCount());
                OwnPtr<TypeCountSet> typeCounts(heap->objectTypeCounts());
                printObjectTypes(typeCounts.get());
            }

            {
                fprintf(stderr, "\tprotected (global) : %zd (%zd)\n", heap->protectedObjectCount(), heap->protectedGlobalObjectCount());
                OwnPtr<TypeCountSet> typeCounts(heap->protectedObjectTypeCounts());
                printObjectTypes(typeCounts.get());
            }
        }
    }


#endif

}

namespace JSC {

struct DefaultGCActivityCallbackPlatformData {
#if ENABLE(SIMPLE_ACTIVITY_CALLBACK)
    Heap * m_heap;
#endif
};

DefaultGCActivityCallback::DefaultGCActivityCallback(Heap* heap)
{
#if ENABLE(SIMPLE_ACTIVITY_CALLBACK)
    d = adoptPtr(new DefaultGCActivityCallbackPlatformData);
    d->m_heap = heap;
#else
    (void)heap;
#endif
}

DefaultGCActivityCallback::~DefaultGCActivityCallback()
{
}

void DefaultGCActivityCallback::didAllocate(size_t)
{
#if ENABLE(SIMPLE_ACTIVITY_CALLBACK)
    reportCurrentObjectCount(d->m_heap);
#endif
}

void DefaultGCActivityCallback::willCollect()
{
#if ENABLE(SIMPLE_ACTIVITY_CALLBACK)
    static int count(0);

    ++count;
    if (__builtin_expect(gcTimer.update(), 0)) {
        fprintf(stderr, "[JavaScriptCore] Garbage collected %d times in the past %ld seconds\n", count, gcTimer.m_prevElapsed);
        count = 0;
    }
    reportCurrentObjectCount(d->m_heap);

#endif
}

void DefaultGCActivityCallback::synchronize()
{
}

void DefaultGCActivityCallback::cancel()
{
}

}

void JSMemoryActivitySettingsConfigSCE(
    JSMemoryActivitySettingsSCE settings)
{
#if ENABLE(SIMPLE_ACTIVITY_CALLBACK)
    gcTimer.initialize(settings.gcActivityFrequency);
    objectCountTimer.initialize(settings.objectCountActivityFrequency);
#endif
}
