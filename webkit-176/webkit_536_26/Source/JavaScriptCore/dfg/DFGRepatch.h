/*
 * Copyright (C) 2011 Apple Inc. All rights reserved.
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

#ifndef DFGRepatch_h
#define DFGRepatch_h

#include <wtf/Platform.h>

#if ENABLE(DFG_JIT)

#include "DFGJITCompiler.h"
#include "DFGOperations.h"

namespace JSC { namespace DFG {

void dfgRepatchGetByID(ExecState*, JSValue, const Identifier&, const PropertySlot&, StructureStubInfo&);
void dfgBuildGetByIDList(ExecState*, JSValue, const Identifier&, const PropertySlot&, StructureStubInfo&);
void dfgBuildGetByIDProtoList(ExecState*, JSValue, const Identifier&, const PropertySlot&, StructureStubInfo&);
void dfgRepatchPutByID(ExecState*, JSValue, const Identifier&, const PutPropertySlot&, StructureStubInfo&, PutKind);
void dfgBuildPutByIdList(ExecState*, JSValue, const Identifier&, const PutPropertySlot&, StructureStubInfo&, PutKind);
void dfgLinkFor(ExecState*, CallLinkInfo&, CodeBlock*, JSFunction* callee, MacroAssemblerCodePtr, CodeSpecializationKind);
void dfgResetGetByID(RepatchBuffer&, StructureStubInfo&);
void dfgResetPutByID(RepatchBuffer&, StructureStubInfo&);

#if ENABLE(DETACHED_JIT)
void dfgCompileBuildGetByIDList(ExecState * exec, JSGlobalData * globalData, CodeBlock * codeBlock, Structure * structure, const Identifier& ident, const PropertySlot& slot, int listIndex, StructureStubInfo& stubInfo, PolymorphicAccessStructureList * polymorphicStructureList);
void dfgRepatchByIdSelfAccess(CodeBlock* codeBlock, StructureStubInfo& stubInfo, Structure* structure, size_t offset, const FunctionPtr &slowPathFunction, bool compact);
void dfgCompileCachedGetById(ExecState* exec, CodeBlock* codeBlock, StructureStubInfo& stubInfo, StructureChain* prototypeChain, size_t offset, size_t count, Structure* structure);
void emitPutTransitionStub(ExecState*, JSValue, const Identifier&, const PutPropertySlot&, StructureStubInfo&, PutKind, Structure*, Structure*, StructureChain*, CodeLocationLabel, MacroAssemblerCodeRef&);
void emitPutReplaceStub(ExecState*, JSValue, const Identifier&, const PutPropertySlot&, StructureStubInfo&, PutKind, Structure*, CodeLocationLabel, MacroAssemblerCodeRef&);
void generateProtoChainAccessStub(ExecState* exec, StructureStubInfo& stubInfo, StructureChain* chain, size_t count, size_t offset, Structure* structure, CodeLocationLabel successLabel, CodeLocationLabel slowCaseLabel, MacroAssemblerCodeRef& stubRoutine);
void dfgCompileCacheGetByIDArray(StructureStubInfo&, CodeBlock*, JSGlobalData*);
#endif

} } // namespace JSC::DFG

#else // ENABLE(DFG_JIT)

#include <wtf/Assertions.h>

namespace JSC {

class RepatchBuffer;
struct StructureStubInfo;

namespace DFG {

inline NO_RETURN_DUE_TO_ASSERT void dfgResetGetByID(RepatchBuffer&, StructureStubInfo&) { ASSERT_NOT_REACHED(); }
inline NO_RETURN_DUE_TO_ASSERT void dfgResetPutByID(RepatchBuffer&, StructureStubInfo&) { ASSERT_NOT_REACHED(); }

} } // namespace JSC::DFG

#endif // ENABLE(DFG_JIT)
#endif // DFGRepatch_h
