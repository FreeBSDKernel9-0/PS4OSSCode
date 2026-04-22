// Copyright (C) 2012 Sony Computer Entertainment Inc.
// All Rights Reserved.
#ifndef PerfUtils_h
#define PerfUtils_h

#if ENABLE(SCOPED_TIMERS)

namespace {

    struct Timer {
        Timer()
            : m_counter(0)
            , m_elapsed(0)
        {
        }
        ~Timer()
        {
        }
        unsigned long accumulateElapsed(unsigned long elapsed, unsigned long elapsedUsec = 0)
        {
            ++m_counter;
            
            m_elapsed += elapsed;
            return m_elapsed;
        }
        void setLabel(char const * label)
        {
            snprintf(m_label, sizeof(m_label), "%s", label ? label : "<noname>");
        }
        void dump()
        {
            fprintf(stderr, "\t%-36s : %10ld (calls), %10ld (cycles), %10ld (cycles/call)\n", m_label, m_counter, m_elapsed, m_elapsed / m_counter);
        }
        static void dumpTimers()
        {
            fprintf(stderr, "===== Timers\n");
            for (size_t i = 0; i < s_timerCount; ++i) {
                s_timers[i].dump();
            }
        }
        static bool initialize()
        {
            atexit(dumpTimers);
            return true;
        }
        static Timer * allocate(char const * label)
        {
            assert(s_timerCount < s_timerCountMax);
            Timer * t(&s_timers[s_timerCount++]);
            t->setLabel(label);
            return t;
        }

        static const size_t  s_timerCountMax = 32;
        static bool          s_initialized;
        static Timer         s_timers[s_timerCountMax];
        static size_t        s_timerCount;
       
        char                 m_label[64];
        unsigned long        m_counter;
        unsigned long        m_elapsed;
    };
    bool   Timer::s_initialized(Timer::initialize());
    Timer  Timer::s_timers[s_timerCountMax];
    size_t Timer::s_timerCount(0);

    struct ScopedTimer {
        ScopedTimer(Timer * t)
            : m_timer(t)
            , m_begin(0)
        {
            unsigned long cycles_high, cycles_low;
            asm volatile (
                "CPUID\n"
                "RDTSC\n"
                "mov %%rdx, %0\n"
                "mov %%rax, %1\n" 
                :
                "=r" (cycles_high), "=r" (cycles_low)
                :
                :
                "%rax", "%rbx", "%rcx", "%rdx");
                m_begin = ((cycles_high & 0x00000000ffffffff) << 32 )| (cycles_low & 0x00000000ffffffff);
        }
        ~ScopedTimer()
        {
            unsigned long cycles_high, cycles_low;
            unsigned long end;
            asm volatile (
                "RDTSCP\n"
                "mov %%rdx, %0\n"
                "mov %%rax, %1\n" 
                "CPUID\n"
                :
                "=r" (cycles_high), "=r" (cycles_low)
                :
                :
                "%rax", "%rbx", "%rcx", "%rdx");
            end = ((cycles_high & 0x00000000ffffffff) << 32 )| (cycles_low & 0x00000000ffffffff);

            m_timer->accumulateElapsed(end - m_begin);
        }
        Timer *       m_timer;
        unsigned long m_begin;
        unsigned long m_beginUsec;
    };

#define SCOPED_TIMER(label) static Timer * __timer(Timer::allocate(label)); ScopedTimer __scopedTimer(__timer);
}

#else // #if ENABLE(SCOPED_TIMERS)

#define SCOPED_TIMER(x) {}

#endif // #if ENABLE(SCOPED_TIMERS)

#endif // PerfUtils_h