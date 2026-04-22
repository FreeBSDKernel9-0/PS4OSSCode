// Copyright (C) 2013 Sony Interactive Entertainment Inc.
// All Rights Reserved.

#include "config.h"

#if ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

#include "JIT.h"

namespace JSC {
    
void JIT::privateCompileClosureCall(CallLinkInfo* callLinkInfo, CodeBlock* calleeCodeBlock, Structure* expectedStructure, ExecutableBase* expectedExecutable, MacroAssemblerCodePtr codePtr)
{
    abort();
}

} // namespace JSC

#endif // #if ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT
