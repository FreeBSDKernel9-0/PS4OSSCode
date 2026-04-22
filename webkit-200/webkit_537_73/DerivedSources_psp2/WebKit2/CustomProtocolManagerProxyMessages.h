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

#ifndef CustomProtocolManagerProxyMessages_h
#define CustomProtocolManagerProxyMessages_h

#if ENABLE(CUSTOM_PROTOCOLS)

#include "Arguments.h"
#include "MessageEncoder.h"
#include "StringReference.h"

namespace WebCore {
    class ResourceRequest;
}

namespace Messages {
namespace CustomProtocolManagerProxy {

static inline CoreIPC::StringReference messageReceiverName()
{
    return CoreIPC::StringReference("CustomProtocolManagerProxy");
}

struct StartLoading : CoreIPC::Arguments2<uint64_t, const WebCore::ResourceRequest&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("StartLoading"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, const WebCore::ResourceRequest&> DecodeType;
    StartLoading(uint64_t customProtocolID, const WebCore::ResourceRequest& request)
        : CoreIPC::Arguments2<uint64_t, const WebCore::ResourceRequest&>(customProtocolID, request)
    {
    }
};

struct StopLoading : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("StopLoading"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit StopLoading(uint64_t customProtocolID)
        : CoreIPC::Arguments1<uint64_t>(customProtocolID)
    {
    }
};

} // namespace CustomProtocolManagerProxy
} // namespace Messages

#endif // ENABLE(CUSTOM_PROTOCOLS)

#endif // CustomProtocolManagerProxyMessages_h
