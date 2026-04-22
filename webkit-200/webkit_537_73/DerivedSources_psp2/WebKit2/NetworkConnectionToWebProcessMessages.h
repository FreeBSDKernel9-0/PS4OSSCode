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

#ifndef NetworkConnectionToWebProcessMessages_h
#define NetworkConnectionToWebProcessMessages_h

#if ENABLE(NETWORK_PROCESS)

#include "Arguments.h"
#include "MessageEncoder.h"
#include "StringReference.h"
#include <WebCore/Cookie.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>

namespace CoreIPC {
    class Connection;
    class DataReference;
}

namespace WTF {
    class String;
}

namespace WebCore {
    class ResourceRequest;
    class ResourceResponse;
    class KURL;
    class ResourceError;
}

namespace WebKit {
    class BlobRegistrationData;
    class NetworkResourceLoadParameters;
}

namespace Messages {
namespace NetworkConnectionToWebProcess {

static inline CoreIPC::StringReference messageReceiverName()
{
    return CoreIPC::StringReference("NetworkConnectionToWebProcess");
}

struct ScheduleResourceLoad : CoreIPC::Arguments1<const WebKit::NetworkResourceLoadParameters&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ScheduleResourceLoad"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebKit::NetworkResourceLoadParameters&> DecodeType;
    explicit ScheduleResourceLoad(const WebKit::NetworkResourceLoadParameters& resourceLoadParameters)
        : CoreIPC::Arguments1<const WebKit::NetworkResourceLoadParameters&>(resourceLoadParameters)
    {
    }
};

struct PerformSynchronousLoad : CoreIPC::Arguments1<const WebKit::NetworkResourceLoadParameters&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("PerformSynchronousLoad"); }
    static const bool isSync = true;

    struct DelayedReply : public ThreadSafeRefCounted<DelayedReply> {
        DelayedReply(PassRefPtr<CoreIPC::Connection>, PassOwnPtr<CoreIPC::MessageEncoder>);
        ~DelayedReply();

        bool send(const WebCore::ResourceError& error, const WebCore::ResourceResponse& response, const CoreIPC::DataReference& data);

    private:
        RefPtr<CoreIPC::Connection> m_connection;
        OwnPtr<CoreIPC::MessageEncoder> m_encoder;
    };

    typedef CoreIPC::Arguments3<WebCore::ResourceError&, WebCore::ResourceResponse&, CoreIPC::DataReference&> Reply;
    typedef CoreIPC::Arguments1<const WebKit::NetworkResourceLoadParameters&> DecodeType;
    explicit PerformSynchronousLoad(const WebKit::NetworkResourceLoadParameters& resourceLoadParameters)
        : CoreIPC::Arguments1<const WebKit::NetworkResourceLoadParameters&>(resourceLoadParameters)
    {
    }
};

struct RemoveLoadIdentifier : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RemoveLoadIdentifier"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit RemoveLoadIdentifier(uint64_t resourceLoadIdentifier)
        : CoreIPC::Arguments1<uint64_t>(resourceLoadIdentifier)
    {
    }
};

struct ServePendingRequests : CoreIPC::Arguments1<uint32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ServePendingRequests"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint32_t> DecodeType;
    explicit ServePendingRequests(uint32_t resourceLoadPriority)
        : CoreIPC::Arguments1<uint32_t>(resourceLoadPriority)
    {
    }
};

struct SetSerialLoadingEnabled : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetSerialLoadingEnabled"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments0 Reply;
    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetSerialLoadingEnabled(bool enabled)
        : CoreIPC::Arguments1<bool>(enabled)
    {
    }
};

struct StartDownload : CoreIPC::Arguments3<bool, uint64_t, const WebCore::ResourceRequest&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("StartDownload"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<bool, uint64_t, const WebCore::ResourceRequest&> DecodeType;
    StartDownload(bool privateBrowsingEnabled, uint64_t downloadID, const WebCore::ResourceRequest& request)
        : CoreIPC::Arguments3<bool, uint64_t, const WebCore::ResourceRequest&>(privateBrowsingEnabled, downloadID, request)
    {
    }
};

struct ConvertMainResourceLoadToDownload : CoreIPC::Arguments4<uint64_t, uint64_t, const WebCore::ResourceRequest&, const WebCore::ResourceResponse&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ConvertMainResourceLoadToDownload"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments4<uint64_t, uint64_t, const WebCore::ResourceRequest&, const WebCore::ResourceResponse&> DecodeType;
    ConvertMainResourceLoadToDownload(uint64_t mainResourceLoadIdentifier, uint64_t downloadID, const WebCore::ResourceRequest& request, const WebCore::ResourceResponse& response)
        : CoreIPC::Arguments4<uint64_t, uint64_t, const WebCore::ResourceRequest&, const WebCore::ResourceResponse&>(mainResourceLoadIdentifier, downloadID, request, response)
    {
    }
};

struct CookiesForDOM : CoreIPC::Arguments3<bool, const WebCore::KURL&, const WebCore::KURL&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CookiesForDOM"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<WTF::String&> Reply;
    typedef CoreIPC::Arguments3<bool, const WebCore::KURL&, const WebCore::KURL&> DecodeType;
    CookiesForDOM(bool privateBrowsingEnabled, const WebCore::KURL& firstParty, const WebCore::KURL& url)
        : CoreIPC::Arguments3<bool, const WebCore::KURL&, const WebCore::KURL&>(privateBrowsingEnabled, firstParty, url)
    {
    }
};

struct SetCookiesFromDOM : CoreIPC::Arguments4<bool, const WebCore::KURL&, const WebCore::KURL&, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetCookiesFromDOM"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments4<bool, const WebCore::KURL&, const WebCore::KURL&, const WTF::String&> DecodeType;
    SetCookiesFromDOM(bool privateBrowsingEnabled, const WebCore::KURL& firstParty, const WebCore::KURL& url, const WTF::String& cookieString)
        : CoreIPC::Arguments4<bool, const WebCore::KURL&, const WebCore::KURL&, const WTF::String&>(privateBrowsingEnabled, firstParty, url, cookieString)
    {
    }
};

struct CookiesEnabled : CoreIPC::Arguments3<bool, const WebCore::KURL&, const WebCore::KURL&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CookiesEnabled"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments3<bool, const WebCore::KURL&, const WebCore::KURL&> DecodeType;
    CookiesEnabled(bool privateBrowsingEnabled, const WebCore::KURL& firstParty, const WebCore::KURL& url)
        : CoreIPC::Arguments3<bool, const WebCore::KURL&, const WebCore::KURL&>(privateBrowsingEnabled, firstParty, url)
    {
    }
};

struct CookieRequestHeaderFieldValue : CoreIPC::Arguments3<bool, const WebCore::KURL&, const WebCore::KURL&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CookieRequestHeaderFieldValue"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<WTF::String&> Reply;
    typedef CoreIPC::Arguments3<bool, const WebCore::KURL&, const WebCore::KURL&> DecodeType;
    CookieRequestHeaderFieldValue(bool privateBrowsingEnabled, const WebCore::KURL& firstParty, const WebCore::KURL& url)
        : CoreIPC::Arguments3<bool, const WebCore::KURL&, const WebCore::KURL&>(privateBrowsingEnabled, firstParty, url)
    {
    }
};

struct GetRawCookies : CoreIPC::Arguments3<bool, const WebCore::KURL&, const WebCore::KURL&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetRawCookies"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<WTF::Vector<WebCore::Cookie>&> Reply;
    typedef CoreIPC::Arguments3<bool, const WebCore::KURL&, const WebCore::KURL&> DecodeType;
    GetRawCookies(bool privateBrowsingEnabled, const WebCore::KURL& firstParty, const WebCore::KURL& url)
        : CoreIPC::Arguments3<bool, const WebCore::KURL&, const WebCore::KURL&>(privateBrowsingEnabled, firstParty, url)
    {
    }
};

struct DeleteCookie : CoreIPC::Arguments3<bool, const WebCore::KURL&, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DeleteCookie"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<bool, const WebCore::KURL&, const WTF::String&> DecodeType;
    DeleteCookie(bool privateBrowsingEnabled, const WebCore::KURL& url, const WTF::String& cookieName)
        : CoreIPC::Arguments3<bool, const WebCore::KURL&, const WTF::String&>(privateBrowsingEnabled, url, cookieName)
    {
    }
};

struct RegisterBlobURL : CoreIPC::Arguments2<const WebCore::KURL&, const WebKit::BlobRegistrationData&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RegisterBlobURL"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WebCore::KURL&, const WebKit::BlobRegistrationData&> DecodeType;
    RegisterBlobURL(const WebCore::KURL& url, const WebKit::BlobRegistrationData& data)
        : CoreIPC::Arguments2<const WebCore::KURL&, const WebKit::BlobRegistrationData&>(url, data)
    {
    }
};

struct RegisterBlobURLFromURL : CoreIPC::Arguments2<const WebCore::KURL&, const WebCore::KURL&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RegisterBlobURLFromURL"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WebCore::KURL&, const WebCore::KURL&> DecodeType;
    RegisterBlobURLFromURL(const WebCore::KURL& url, const WebCore::KURL& srcURL)
        : CoreIPC::Arguments2<const WebCore::KURL&, const WebCore::KURL&>(url, srcURL)
    {
    }
};

struct UnregisterBlobURL : CoreIPC::Arguments1<const WebCore::KURL&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("UnregisterBlobURL"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebCore::KURL&> DecodeType;
    explicit UnregisterBlobURL(const WebCore::KURL& url)
        : CoreIPC::Arguments1<const WebCore::KURL&>(url)
    {
    }
};

} // namespace NetworkConnectionToWebProcess
} // namespace Messages

#endif // ENABLE(NETWORK_PROCESS)

#endif // NetworkConnectionToWebProcessMessages_h
