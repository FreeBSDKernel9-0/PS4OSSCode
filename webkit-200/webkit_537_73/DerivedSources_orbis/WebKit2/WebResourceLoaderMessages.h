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

#ifndef WebResourceLoaderMessages_h
#define WebResourceLoaderMessages_h

#include "Arguments.h"
#include "MessageEncoder.h"
#include "ShareableResource.h"
#include "StringReference.h"

namespace CoreIPC {
    class DataReference;
}

namespace WebCore {
    class ResourceRequest;
    class ResourceResponse;
    class ProtectionSpace;
    class ResourceError;
}

namespace WebKit {
    class PlatformCertificateInfo;
}

namespace Messages {
namespace WebResourceLoader {

static inline CoreIPC::StringReference messageReceiverName()
{
    return CoreIPC::StringReference("WebResourceLoader");
}

struct CancelResourceLoader : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CancelResourceLoader"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct WillSendRequest : CoreIPC::Arguments2<const WebCore::ResourceRequest&, const WebCore::ResourceResponse&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("WillSendRequest"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WebCore::ResourceRequest&, const WebCore::ResourceResponse&> DecodeType;
    WillSendRequest(const WebCore::ResourceRequest& request, const WebCore::ResourceResponse& redirectResponse)
        : CoreIPC::Arguments2<const WebCore::ResourceRequest&, const WebCore::ResourceResponse&>(request, redirectResponse)
    {
    }
};

struct DidSendData : CoreIPC::Arguments2<uint64_t, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidSendData"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, uint64_t> DecodeType;
    DidSendData(uint64_t bytesSent, uint64_t totalBytesToBeSent)
        : CoreIPC::Arguments2<uint64_t, uint64_t>(bytesSent, totalBytesToBeSent)
    {
    }
};

struct DidReceiveResponseWithCertificateInfo : CoreIPC::Arguments3<const WebCore::ResourceResponse&, const WebKit::PlatformCertificateInfo&, bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidReceiveResponseWithCertificateInfo"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<const WebCore::ResourceResponse&, const WebKit::PlatformCertificateInfo&, bool> DecodeType;
    DidReceiveResponseWithCertificateInfo(const WebCore::ResourceResponse& response, const WebKit::PlatformCertificateInfo& certificateInfo, bool needsContinueDidReceiveResponseMessage)
        : CoreIPC::Arguments3<const WebCore::ResourceResponse&, const WebKit::PlatformCertificateInfo&, bool>(response, certificateInfo, needsContinueDidReceiveResponseMessage)
    {
    }
};

struct DidReceiveData : CoreIPC::Arguments2<const CoreIPC::DataReference&, int64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidReceiveData"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const CoreIPC::DataReference&, int64_t> DecodeType;
    DidReceiveData(const CoreIPC::DataReference& data, int64_t encodedDataLength)
        : CoreIPC::Arguments2<const CoreIPC::DataReference&, int64_t>(data, encodedDataLength)
    {
    }
};

struct DidFinishResourceLoad : CoreIPC::Arguments1<double> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidFinishResourceLoad"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<double> DecodeType;
    explicit DidFinishResourceLoad(double finishTime)
        : CoreIPC::Arguments1<double>(finishTime)
    {
    }
};

struct DidFailResourceLoad : CoreIPC::Arguments1<const WebCore::ResourceError&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidFailResourceLoad"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebCore::ResourceError&> DecodeType;
    explicit DidFailResourceLoad(const WebCore::ResourceError& error)
        : CoreIPC::Arguments1<const WebCore::ResourceError&>(error)
    {
    }
};

struct CanAuthenticateAgainstProtectionSpace : CoreIPC::Arguments1<const WebCore::ProtectionSpace&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CanAuthenticateAgainstProtectionSpace"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebCore::ProtectionSpace&> DecodeType;
    explicit CanAuthenticateAgainstProtectionSpace(const WebCore::ProtectionSpace& protectionSpace)
        : CoreIPC::Arguments1<const WebCore::ProtectionSpace&>(protectionSpace)
    {
    }
};

struct DidReceiveResource : CoreIPC::Arguments2<const WebKit::ShareableResource::Handle&, double> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidReceiveResource"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WebKit::ShareableResource::Handle&, double> DecodeType;
    DidReceiveResource(const WebKit::ShareableResource::Handle& resource, double finishTime)
        : CoreIPC::Arguments2<const WebKit::ShareableResource::Handle&, double>(resource, finishTime)
    {
    }
};

} // namespace WebResourceLoader
} // namespace Messages

#endif // WebResourceLoaderMessages_h
