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

#ifndef SharedWorkerProcessMessages_h
#define SharedWorkerProcessMessages_h

#if ENABLE(SHARED_WORKER_PROCESS)

#include "Arguments.h"
#include "MessageEncoder.h"
#include "StringReference.h"

namespace WebKit {
    struct SharedWorkerProcessCreationParameters;
}

namespace Messages {
namespace SharedWorkerProcess {

static inline CoreIPC::StringReference messageReceiverName()
{
    return CoreIPC::StringReference("SharedWorkerProcess");
}

struct InitializeSharedWorkerProcess : CoreIPC::Arguments1<const WebKit::SharedWorkerProcessCreationParameters&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("InitializeSharedWorkerProcess"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebKit::SharedWorkerProcessCreationParameters&> DecodeType;
    explicit InitializeSharedWorkerProcess(const WebKit::SharedWorkerProcessCreationParameters& processCreationParameters)
        : CoreIPC::Arguments1<const WebKit::SharedWorkerProcessCreationParameters&>(processCreationParameters)
    {
    }
};

struct CreateWebProcessConnection : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CreateWebProcessConnection"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

#if PLATFORM(MAC)
struct SetProcessSuppressionEnabled : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetProcessSuppressionEnabled"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetProcessSuppressionEnabled(bool flag)
        : CoreIPC::Arguments1<bool>(flag)
    {
    }
};
#endif

} // namespace SharedWorkerProcess
} // namespace Messages

#endif // ENABLE(SHARED_WORKER_PROCESS)

#endif // SharedWorkerProcessMessages_h
