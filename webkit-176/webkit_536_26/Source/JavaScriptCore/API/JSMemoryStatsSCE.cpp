#include "config.h"

#include "JSMemoryStatsSCE.h"

#include "APICast.h"

void JSMemoryStatsQuerySCE(
    JSContextRef context,
    JSMemoryStatsSCE& stats
) {

    //
    // Safely cast the JSContextRef to a JSC::ExecState
    //
    JSC::ExecState* execState = ::toJS(context);

    //
    // Retrieve the heap object
    //
    JSC::Heap* heap = execState->heap();

    //
    // Fill in heap stats
    //
    stats.size        = heap->size();
    stats.capacity    = heap->capacity();
    stats.objectCount = heap->objectCount();

}
