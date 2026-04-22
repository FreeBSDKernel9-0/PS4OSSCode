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

#ifndef WebProcessProxyMessages_h
#define WebProcessProxyMessages_h

#include "Arguments.h"
#include "MessageEncoder.h"
#include "StringReference.h"
#include <WebCore/PluginData.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace CoreIPC {
    class Connection;
    class DataReference;
    class Attachment;
}

namespace WTF {
    class String;
}

namespace WebKit {
    struct WebNavigationDataStore;
}

namespace Messages {
namespace WebProcessProxy {

static inline CoreIPC::StringReference messageReceiverName()
{
    return CoreIPC::StringReference("WebProcessProxy");
}

struct DidNavigateWithNavigationData : CoreIPC::Arguments3<uint64_t, const WebKit::WebNavigationDataStore&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidNavigateWithNavigationData"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<uint64_t, const WebKit::WebNavigationDataStore&, uint64_t> DecodeType;
    DidNavigateWithNavigationData(uint64_t pageID, const WebKit::WebNavigationDataStore& store, uint64_t frameID)
        : CoreIPC::Arguments3<uint64_t, const WebKit::WebNavigationDataStore&, uint64_t>(pageID, store, frameID)
    {
    }
};

struct DidPerformClientRedirect : CoreIPC::Arguments4<uint64_t, const WTF::String&, const WTF::String&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidPerformClientRedirect"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments4<uint64_t, const WTF::String&, const WTF::String&, uint64_t> DecodeType;
    DidPerformClientRedirect(uint64_t pageID, const WTF::String& sourceURLString, const WTF::String& destinationURLString, uint64_t frameID)
        : CoreIPC::Arguments4<uint64_t, const WTF::String&, const WTF::String&, uint64_t>(pageID, sourceURLString, destinationURLString, frameID)
    {
    }
};

struct DidPerformServerRedirect : CoreIPC::Arguments4<uint64_t, const WTF::String&, const WTF::String&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidPerformServerRedirect"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments4<uint64_t, const WTF::String&, const WTF::String&, uint64_t> DecodeType;
    DidPerformServerRedirect(uint64_t pageID, const WTF::String& sourceURLString, const WTF::String& destinationURLString, uint64_t frameID)
        : CoreIPC::Arguments4<uint64_t, const WTF::String&, const WTF::String&, uint64_t>(pageID, sourceURLString, destinationURLString, frameID)
    {
    }
};

struct DidUpdateHistoryTitle : CoreIPC::Arguments4<uint64_t, const WTF::String&, const WTF::String&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidUpdateHistoryTitle"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments4<uint64_t, const WTF::String&, const WTF::String&, uint64_t> DecodeType;
    DidUpdateHistoryTitle(uint64_t pageID, const WTF::String& title, const WTF::String& url, uint64_t frameID)
        : CoreIPC::Arguments4<uint64_t, const WTF::String&, const WTF::String&, uint64_t>(pageID, title, url, frameID)
    {
    }
};

struct AddBackForwardItem : CoreIPC::Arguments5<uint64_t, const WTF::String&, const WTF::String&, const WTF::String&, const CoreIPC::DataReference&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("AddBackForwardItem"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments5<uint64_t, const WTF::String&, const WTF::String&, const WTF::String&, const CoreIPC::DataReference&> DecodeType;
    AddBackForwardItem(uint64_t itemID, const WTF::String& originalURL, const WTF::String& url, const WTF::String& title, const CoreIPC::DataReference& backForwardData)
        : CoreIPC::Arguments5<uint64_t, const WTF::String&, const WTF::String&, const WTF::String&, const CoreIPC::DataReference&>(itemID, originalURL, url, title, backForwardData)
    {
    }
};

struct DidDestroyFrame : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidDestroyFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit DidDestroyFrame(uint64_t frameID)
        : CoreIPC::Arguments1<uint64_t>(frameID)
    {
    }
};

struct ShouldTerminate : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ShouldTerminate"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments0 DecodeType;
};

struct EnableSuddenTermination : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("EnableSuddenTermination"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct DisableSuddenTermination : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DisableSuddenTermination"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

#if ENABLE(NETSCAPE_PLUGIN_API)
struct GetPlugins : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetPlugins"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments2<Vector<WebCore::PluginInfo>&, Vector<WebCore::PluginInfo>&> Reply;
    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit GetPlugins(bool refresh)
        : CoreIPC::Arguments1<bool>(refresh)
    {
    }
};
#endif

#if ENABLE(PLUGIN_PROCESS)
struct GetPluginProcessConnection : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetPluginProcessConnection"); }
    static const bool isSync = true;

    struct DelayedReply : public ThreadSafeRefCounted<DelayedReply> {
        DelayedReply(PassRefPtr<CoreIPC::Connection>, PassOwnPtr<CoreIPC::MessageEncoder>);
        ~DelayedReply();

        bool send(const CoreIPC::Attachment& connectionHandle, bool supportsAsynchronousInitialization);

    private:
        RefPtr<CoreIPC::Connection> m_connection;
        OwnPtr<CoreIPC::MessageEncoder> m_encoder;
    };

    typedef CoreIPC::Arguments2<CoreIPC::Attachment&, bool&> Reply;
    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit GetPluginProcessConnection(uint64_t pluginProcessToken)
        : CoreIPC::Arguments1<uint64_t>(pluginProcessToken)
    {
    }
};
#endif

#if ENABLE(NETSCAPE_PLUGIN_API) && !ENABLE(PLUGIN_PROCESS)
struct DidGetSitesWithPluginData : CoreIPC::Arguments2<const Vector<WTF::String>&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidGetSitesWithPluginData"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const Vector<WTF::String>&, uint64_t> DecodeType;
    DidGetSitesWithPluginData(const Vector<WTF::String>& sites, uint64_t callbackID)
        : CoreIPC::Arguments2<const Vector<WTF::String>&, uint64_t>(sites, callbackID)
    {
    }
};
#endif

#if ENABLE(NETSCAPE_PLUGIN_API) && !ENABLE(PLUGIN_PROCESS)
struct DidClearPluginSiteData : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidClearPluginSiteData"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit DidClearPluginSiteData(uint64_t callbackID)
        : CoreIPC::Arguments1<uint64_t>(callbackID)
    {
    }
};
#endif

#if ENABLE(NETWORK_PROCESS)
struct GetNetworkProcessConnection : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetNetworkProcessConnection"); }
    static const bool isSync = true;

    struct DelayedReply : public ThreadSafeRefCounted<DelayedReply> {
        DelayedReply(PassRefPtr<CoreIPC::Connection>, PassOwnPtr<CoreIPC::MessageEncoder>);
        ~DelayedReply();

        bool send(const CoreIPC::Attachment& connectionHandle);

    private:
        RefPtr<CoreIPC::Connection> m_connection;
        OwnPtr<CoreIPC::MessageEncoder> m_encoder;
    };

    typedef CoreIPC::Arguments1<CoreIPC::Attachment&> Reply;
    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if ENABLE(SHARED_WORKER_PROCESS)
struct GetSharedWorkerProcessConnection : CoreIPC::Arguments2<const WTF::String&, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetSharedWorkerProcessConnection"); }
    static const bool isSync = true;

    struct DelayedReply : public ThreadSafeRefCounted<DelayedReply> {
        DelayedReply(PassRefPtr<CoreIPC::Connection>, PassOwnPtr<CoreIPC::MessageEncoder>);
        ~DelayedReply();

        bool send(const CoreIPC::Attachment& connectionHandle);

    private:
        RefPtr<CoreIPC::Connection> m_connection;
        OwnPtr<CoreIPC::MessageEncoder> m_encoder;
    };

    typedef CoreIPC::Arguments1<CoreIPC::Attachment&> Reply;
    typedef CoreIPC::Arguments2<const WTF::String&, const WTF::String&> DecodeType;
    GetSharedWorkerProcessConnection(const WTF::String& url, const WTF::String& name)
        : CoreIPC::Arguments2<const WTF::String&, const WTF::String&>(url, name)
    {
    }
};
#endif

} // namespace WebProcessProxy
} // namespace Messages

#endif // WebProcessProxyMessages_h
