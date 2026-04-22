/*
 * Copyright (C) 2010 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SharedWorkerProcessProxyMessages_h
#define SharedWorkerProcessProxyMessages_h

#if ENABLE(SHARED_WORKER_PROCESS)

#include "Arguments.h"
#include "MessageEncoder.h"
#include "StringReference.h"

namespace CoreIPC {
    class Attachment;
}

namespace Messages {
namespace SharedWorkerProcessProxy {

static inline CoreIPC::StringReference messageReceiverName()
{
    return CoreIPC::StringReference("SharedWorkerProcessProxy");
}

struct DidCreateWebProcessConnection : CoreIPC::Arguments1<const CoreIPC::Attachment&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidCreateWebProcessConnection"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const CoreIPC::Attachment&> DecodeType;
    explicit DidCreateWebProcessConnection(const CoreIPC::Attachment& connectionIdentifier)
        : CoreIPC::Arguments1<const CoreIPC::Attachment&>(connectionIdentifier)
    {
    }
};

} // namespace SharedWorkerProcessProxy
} // namespace Messages

#endif // ENABLE(SHARED_WORKER_PROCESS)

#endif // SharedWorkerProcessProxyMessages_h
