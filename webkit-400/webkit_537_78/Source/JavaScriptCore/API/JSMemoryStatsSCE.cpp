#include "config.h"

#include "APICast.h"
#include "VM.h"
#include "JSCJSValueInlines.h"
#include "JSMemoryStatsSCE.h"

#include <wtf/MetaAllocator.h>

extern "C" void JSMemoryStatsQuerySCE(
    JSContextRef context,
    JSMemoryStatsSCE & stats)
{
    JSC::ExecState* execState = ::toJS(context);

    if (stats.flags & JS_MEMORY_STATS_SCE_FLAG_EXECALLOC) {
#if ENABLE(ASSEMBLER)
        JSC::VM & vm(execState->vm());
        JSC::ExecutableAllocator allocator(vm.executableAllocator);
        stats.executableAllocator.committed = allocator.committedByteCount();
#else
        stats.executableAllocator.committed = 0;
#endif
    }

    if (stats.flags & JS_MEMORY_STATS_SCE_FLAG_GC) {
        JSC::Heap* heap = execState->heap();
        stats.gcHeap.size        = heap->size();
        stats.gcHeap.capacity    = heap->capacity();
        stats.gcHeap.objectCount = heap->objectCount();
    }
}
