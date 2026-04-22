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

#ifndef CustomProtocolManagerMessages_h
#define CustomProtocolManagerMessages_h

#if ENABLE(CUSTOM_PROTOCOLS)

#include "Arguments.h"
#include "MessageEncoder.h"
#include "StringReference.h"

namespace CoreIPC {
    class DataReference;
}

namespace WTF {
    class String;
}

namespace WebCore {
    class ResourceResponse;
    class ResourceError;
}

namespace Messages {
namespace CustomProtocolManager {

static inline CoreIPC::StringReference messageReceiverName()
{
    return CoreIPC::StringReference("CustomProtocolManager");
}

struct DidFailWithError : CoreIPC::Arguments2<uint64_t, const WebCore::ResourceError&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidFailWithError"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, const WebCore::ResourceError&> DecodeType;
    DidFailWithError(uint64_t customProtocolID, const WebCore::ResourceError& error)
        : CoreIPC::Arguments2<uint64_t, const WebCore::ResourceError&>(customProtocolID, error)
    {
    }
};

struct DidLoadData : CoreIPC::Arguments2<uint64_t, const CoreIPC::DataReference&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidLoadData"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, const CoreIPC::DataReference&> DecodeType;
    DidLoadData(uint64_t customProtocolID, const CoreIPC::DataReference& data)
        : CoreIPC::Arguments2<uint64_t, const CoreIPC::DataReference&>(customProtocolID, data)
    {
    }
};

struct DidReceiveResponse : CoreIPC::Arguments3<uint64_t, const WebCore::ResourceResponse&, uint32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidReceiveResponse"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<uint64_t, const WebCore::ResourceResponse&, uint32_t> DecodeType;
    DidReceiveResponse(uint64_t customProtocolID, const WebCore::ResourceResponse& response, uint32_t cacheStoragePolicy)
        : CoreIPC::Arguments3<uint64_t, const WebCore::ResourceResponse&, uint32_t>(customProtocolID, response, cacheStoragePolicy)
    {
    }
};

struct DidFinishLoading : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidFinishLoading"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit DidFinishLoading(uint64_t customProtocolID)
        : CoreIPC::Arguments1<uint64_t>(customProtocolID)
    {
    }
};

struct RegisterScheme : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RegisterScheme"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit RegisterScheme(const WTF::String& name)
        : CoreIPC::Arguments1<const WTF::String&>(name)
    {
    }
};

struct UnregisterScheme : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("UnregisterScheme"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit UnregisterScheme(const WTF::String& name)
        : CoreIPC::Arguments1<const WTF::String&>(name)
    {
    }
};

} // namespace CustomProtocolManager
} // namespace Messages

#endif // ENABLE(CUSTOM_PROTOCOLS)

#endif // CustomProtocolManagerMessages_h
