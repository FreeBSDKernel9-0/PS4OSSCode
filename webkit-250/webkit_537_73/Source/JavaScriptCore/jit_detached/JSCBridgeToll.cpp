// Copyright (C) 2013 Sony Computer Entertainment Inc.
// All Rights Reserved.

#include "config.h"
#include "JSCBridgeToll.h"

#if ENABLE(DETACHED_JIT)

#include "CodeBlock.h"
#include "JSCJSValueInlines.h"
#include "Opcode.h"
#include "VM.h"

#include <assert.h>

namespace JSC {

    JSCBridgeToll::JSCBridgeToll(JSCBridge::Payload * payload)
        : m_payload(payload)
    {
        m_payload->m_toll = this;
    }

    JSCBridgeToll::~JSCBridgeToll()
    {
        // 'refund' the toll...
        m_payload->m_toll = NULL;
    }

    JSCBridgeToll::CodeBlockToll const & JSCBridgeToll::forCodeBlock(CodeBlock const * codeBlock)
    {
        return m_codeBlockTollMap.find(codeBlock)->value;
    }

    JSCBridgeToll::GlobalObjectToll const & JSCBridgeToll::forGlobalObject(JSGlobalObject const * globalObject)
    {
        return m_globalObjectTollMap.find(globalObject)->value;
    }

    void JSCBridgeToll::prepare(VM * vm)
    {
        this->m_vm.m_stringStructure = vm->stringStructure.get();
    }

#if !BUILDING_DETACHED_JIT

    void JSCBridgeToll::prepare(CodeBlock * codeBlock)
    {
        CodeBlockTollMap::AddResult entry(m_codeBlockTollMap.add(codeBlock, CodeBlockToll()));
        UnlinkedCodeBlock const * const unlinkedCodeblock(codeBlock->unlinkedCodeBlock());
        if (entry.isNewEntry) {
            CodeBlockToll & toll(entry.iterator->value);

            toll.m_codeType = codeBlock->codeType();
            toll.m_jumpTargets = unlinkedCodeblock->m_jumpTargets.data();
            toll.m_numberOfJumpTargets = unlinkedCodeblock->m_jumpTargets.size();
            toll.m_dfgCapabilityLevel = codeBlock->canCompileWithDFG();
        }

        JSGlobalObject * globalObject(codeBlock->globalObject());
        if (globalObject) {
            prepare(globalObject);
        }
    }

    void JSCBridgeToll::prepare(JSGlobalObject * globalObject)
    {
        GlobalObjectTollMap::AddResult entry(m_globalObjectTollMap.add(globalObject, GlobalObjectToll()));
        if (entry.isNewEntry) {
            GlobalObjectToll & toll(entry.iterator->value);
            memcpy(&(toll.m_specialPointers[0]), &(globalObject->m_specialPointers[0]), sizeof(void *) * Special::TableSize);
        }
    }

#endif // #if BUILDING_DETACHED_JIT

} // namespace JSC

#endif // #if ENABLE(DETACHED_JIT)
