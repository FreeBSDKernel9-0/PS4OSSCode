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

#ifndef NetworkProcessMessages_h
#define NetworkProcessMessages_h

#if ENABLE(NETWORK_PROCESS)

#include "Arguments.h"
#include "MessageEncoder.h"
#include "StringReference.h"

namespace WTF {
    class String;
}

namespace WebCore {
    class ResourceRequest;
}

namespace WebKit {
    class PlatformCertificateInfo;
    struct NetworkProcessCreationParameters;
}

namespace Messages {
namespace NetworkProcess {

static inline CoreIPC::StringReference messageReceiverName()
{
    return CoreIPC::StringReference("NetworkProcess");
}

struct InitializeNetworkProcess : CoreIPC::Arguments1<const WebKit::NetworkProcessCreationParameters&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("InitializeNetworkProcess"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebKit::NetworkProcessCreationParameters&> DecodeType;
    explicit InitializeNetworkProcess(const WebKit::NetworkProcessCreationParameters& processCreationParameters)
        : CoreIPC::Arguments1<const WebKit::NetworkProcessCreationParameters&>(processCreationParameters)
    {
    }
};

struct CreateNetworkConnectionToWebProcess : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CreateNetworkConnectionToWebProcess"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct EnsurePrivateBrowsingSession : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("EnsurePrivateBrowsingSession"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct DestroyPrivateBrowsingSession : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DestroyPrivateBrowsingSession"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct DownloadRequest : CoreIPC::Arguments2<uint64_t, const WebCore::ResourceRequest&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DownloadRequest"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, const WebCore::ResourceRequest&> DecodeType;
    DownloadRequest(uint64_t downloadID, const WebCore::ResourceRequest& request)
        : CoreIPC::Arguments2<uint64_t, const WebCore::ResourceRequest&>(downloadID, request)
    {
    }
};

struct CancelDownload : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CancelDownload"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit CancelDownload(uint64_t downloadID)
        : CoreIPC::Arguments1<uint64_t>(downloadID)
    {
    }
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

struct AllowSpecificHTTPSCertificateForHost : CoreIPC::Arguments2<const WebKit::PlatformCertificateInfo&, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("AllowSpecificHTTPSCertificateForHost"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WebKit::PlatformCertificateInfo&, const WTF::String&> DecodeType;
    AllowSpecificHTTPSCertificateForHost(const WebKit::PlatformCertificateInfo& certificate, const WTF::String& host)
        : CoreIPC::Arguments2<const WebKit::PlatformCertificateInfo&, const WTF::String&>(certificate, host)
    {
    }
};

struct GetNetworkProcessStatistics : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetNetworkProcessStatistics"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit GetNetworkProcessStatistics(uint64_t callbackID)
        : CoreIPC::Arguments1<uint64_t>(callbackID)
    {
    }
};

struct ClearCacheForAllOrigins : CoreIPC::Arguments1<uint32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ClearCacheForAllOrigins"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint32_t> DecodeType;
    explicit ClearCacheForAllOrigins(uint32_t cachesToClear)
        : CoreIPC::Arguments1<uint32_t>(cachesToClear)
    {
    }
};

} // namespace NetworkProcess
} // namespace Messages

#endif // ENABLE(NETWORK_PROCESS)

#endif // NetworkProcessMessages_h
