// Copyright (C) 2013 Sony Computer Entertainment Inc.
// All Rights Reserved.

#include "config.h"
#include "DFGOSRExitCompiler.h"

#include "jit_detached/JSCBridgeToll.h"
#include "jit_detached/JSCBridge.h"
#include "CodeBlock.h"
#include "JSCJSValueInlines.h"

#include <wtf/OwnPtr.h>

#if ENABLE(DFG_JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

namespace JSC {
namespace DFG {

void DFG_OPERATION compileOSRExit_vmstub(ExecState* exec)
{
    PROFILE_FUNCTION_CALL;

    CodeBlock* codeBlock = exec->codeBlock();
    VM* vm = &exec->vm();
    uint32_t exitIndex = vm->osrExitIndex;
    OSRExit& exit = codeBlock->osrExit(exitIndex);

    // we perform this here before we create the toll for performing DFG
    // OSR exit compilation to ensure we don't clobber the data stored in
    // the shared data section since each call to jitCompile() will invoke
    // the JIT compiler process.
    // for more information as to why we perform jitCompile() here and not
    // in the JIT compiler process, see comment inside compileOSRExit()
    {
        for (CodeOrigin codeOrigin = exit.m_codeOrigin; codeOrigin.inlineCallFrame; codeOrigin = codeOrigin.inlineCallFrame->caller) {
            static_cast<FunctionExecutable*>(codeOrigin.inlineCallFrame->executable.get())
                ->baselineCodeBlockFor(codeOrigin.inlineCallFrame->isCall ? CodeForCall : CodeForConstruct)
                ->jitCompile(exec);
        }
    }

    JSCBridge * const bridge(JSCBridge::sharedInstance());

    OwnPtr<JSCBridge::Payload> payload(adoptPtr(bridge->createPayload()));
    payload->sendArgument(reinterpret_cast<uintptr_t>(exec));

    // prepare toll
    OwnPtr<JSCBridgeToll> toll(adoptPtr(bridge->createToll(payload.get())));
    toll->prepare(vm);
    toll->prepare(codeBlock);
    for (CodeOrigin codeOrigin = exit.m_codeOrigin; codeOrigin.inlineCallFrame; codeOrigin = codeOrigin.inlineCallFrame->caller) {
        FunctionExecutable *executable(static_cast<FunctionExecutable*>(codeOrigin.inlineCallFrame->executable.get()));
        CodeBlock * codeBlock(executable->baselineCodeBlockFor(codeOrigin.inlineCallFrame->isCall ? CodeForCall : CodeForConstruct));
        toll->prepare(codeBlock);
    }

    bridge->requestCompilerTask(JSCBridge::e_DFG_compileOSRExit);

    return;
}

} // namespace DFG
} // namespace JSC

#endif // #if ENABLE(DFG_JIT) && ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT

