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

#ifndef DownloadProxyMessages_h
#define DownloadProxyMessages_h

#include "Arguments.h"
#include "MessageEncoder.h"
#include "SandboxExtension.h"
#include "StringReference.h"

namespace CoreIPC {
    class DataReference;
}

namespace WTF {
    class String;
}

namespace WebCore {
    class ResourceRequest;
    class AuthenticationChallenge;
    class ResourceError;
    class ResourceResponse;
}

namespace Messages {
namespace DownloadProxy {

static inline CoreIPC::StringReference messageReceiverName()
{
    return CoreIPC::StringReference("DownloadProxy");
}

struct DidStart : CoreIPC::Arguments1<const WebCore::ResourceRequest&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidStart"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebCore::ResourceRequest&> DecodeType;
    explicit DidStart(const WebCore::ResourceRequest& request)
        : CoreIPC::Arguments1<const WebCore::ResourceRequest&>(request)
    {
    }
};

struct DidReceiveAuthenticationChallenge : CoreIPC::Arguments2<const WebCore::AuthenticationChallenge&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidReceiveAuthenticationChallenge"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WebCore::AuthenticationChallenge&, uint64_t> DecodeType;
    DidReceiveAuthenticationChallenge(const WebCore::AuthenticationChallenge& challenge, uint64_t challengeID)
        : CoreIPC::Arguments2<const WebCore::AuthenticationChallenge&, uint64_t>(challenge, challengeID)
    {
    }
};

struct DidReceiveResponse : CoreIPC::Arguments1<const WebCore::ResourceResponse&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidReceiveResponse"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebCore::ResourceResponse&> DecodeType;
    explicit DidReceiveResponse(const WebCore::ResourceResponse& response)
        : CoreIPC::Arguments1<const WebCore::ResourceResponse&>(response)
    {
    }
};

struct DidReceiveData : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidReceiveData"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit DidReceiveData(uint64_t length)
        : CoreIPC::Arguments1<uint64_t>(length)
    {
    }
};

struct ShouldDecodeSourceDataOfMIMEType : CoreIPC::Arguments1<const String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ShouldDecodeSourceDataOfMIMEType"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments1<const String&> DecodeType;
    explicit ShouldDecodeSourceDataOfMIMEType(const String& mimeType)
        : CoreIPC::Arguments1<const String&>(mimeType)
    {
    }
};

struct DecideDestinationWithSuggestedFilename : CoreIPC::Arguments1<const String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DecideDestinationWithSuggestedFilename"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments3<String&, bool&, WebKit::SandboxExtension::Handle&> Reply;
    typedef CoreIPC::Arguments1<const String&> DecodeType;
    explicit DecideDestinationWithSuggestedFilename(const String& filename)
        : CoreIPC::Arguments1<const String&>(filename)
    {
    }
};

struct DidCreateDestination : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidCreateDestination"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit DidCreateDestination(const WTF::String& path)
        : CoreIPC::Arguments1<const WTF::String&>(path)
    {
    }
};

struct DidFinish : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidFinish"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct DidFail : CoreIPC::Arguments2<const WebCore::ResourceError&, const CoreIPC::DataReference&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidFail"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WebCore::ResourceError&, const CoreIPC::DataReference&> DecodeType;
    DidFail(const WebCore::ResourceError& error, const CoreIPC::DataReference& resumeData)
        : CoreIPC::Arguments2<const WebCore::ResourceError&, const CoreIPC::DataReference&>(error, resumeData)
    {
    }
};

struct DidCancel : CoreIPC::Arguments1<const CoreIPC::DataReference&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidCancel"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const CoreIPC::DataReference&> DecodeType;
    explicit DidCancel(const CoreIPC::DataReference& resumeData)
        : CoreIPC::Arguments1<const CoreIPC::DataReference&>(resumeData)
    {
    }
};

} // namespace DownloadProxy
} // namespace Messages

#endif // DownloadProxyMessages_h
