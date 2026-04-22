// Copyright (C) 2013 Sony Computer Entertainment Inc.
// All Rights Reserved.
#ifndef JSCBridgeToll_h
#define JSCBridgeToll_h

#include "BytecodeConventions.h"
#include "CodeType.h"
#include "DFGCommon.h"
#include "SpecialPointer.h"

#include "unicode/umachine.h"

#include <wtf/HashMap.h>
#include <wtf/StdLibExtras.h>
#include <wtf/Vector.h>

#include <JITBridge.h>

#if ENABLE_DETACHED_JIT

namespace JSC {

    class CodeBlock;
    class Identifier;
    class JSCBridge;
    class Structure;
    class VM;

    class JSCBridgeToll {
    public:
        DETACHED_JIT_MAKE_SHARED_DATA_ALLOCATED;
    public:
        JSCBridgeToll(JSCBridge::Payload *);
        virtual ~JSCBridgeToll();

        void prepare(VM *);
        void prepare(CodeBlock *);
        void prepare(JSGlobalObject *);

    public:
        struct VMToll {
            Structure * m_stringStructure;
        };
        struct CodeBlockToll {
            CodeType                                 m_codeType;
            unsigned const *                         m_jumpTargets;
            size_t                                   m_numberOfJumpTargets;
            DFG::CapabilityLevel                     m_dfgCapabilityLevel;
        };
        struct GlobalObjectToll {
            void * m_specialPointers[Special::TableSize];
        };

        VMToll m_vm;
        CodeBlockToll const & forCodeBlock(CodeBlock const *);
        GlobalObjectToll const & forGlobalObject(JSGlobalObject const *);

    private:
        typedef HashMap_shared<CodeBlock const *, CodeBlockToll> CodeBlockTollMap;
        typedef HashMap_shared<JSGlobalObject const *, GlobalObjectToll> GlobalObjectTollMap;

        JSCBridge::Payload * m_payload;
        CodeBlockTollMap m_codeBlockTollMap;
        GlobalObjectTollMap m_globalObjectTollMap;
    };

} // namespace JSC

#endif
#endif
