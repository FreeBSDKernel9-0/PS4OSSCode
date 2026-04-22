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

#include "config.h"

#include "WebProcessProxy.h"

#include "ArgumentCoders.h"
#if ENABLE(PLUGIN_PROCESS) || ENABLE(NETWORK_PROCESS) || ENABLE(SHARED_WORKER_PROCESS)
#include "Attachment.h"
#endif
#include "DataReference.h"
#include "HandleMessage.h"
#include "MessageDecoder.h"
#if ENABLE(NETSCAPE_PLUGIN_API)
#include "WebCoreArgumentCoders.h"
#endif
#include "WebNavigationDataStore.h"
#include "WebProcessProxyMessages.h"
#if ENABLE(NETSCAPE_PLUGIN_API)
#include <WebCore/PluginData.h>
#endif
#if ENABLE(NETSCAPE_PLUGIN_API) && !ENABLE(PLUGIN_PROCESS) || ENABLE(NETSCAPE_PLUGIN_API)
#include <wtf/Vector.h>
#endif
#include <wtf/text/WTFString.h>

namespace Messages {

namespace WebProcessProxy {

#if ENABLE(PLUGIN_PROCESS)

GetPluginProcessConnection::DelayedReply::DelayedReply(PassRefPtr<CoreIPC::Connection> connection, PassOwnPtr<CoreIPC::MessageEncoder> encoder)
    : m_connection(connection)
    , m_encoder(encoder)
{
}

GetPluginProcessConnection::DelayedReply::~DelayedReply()
{
    ASSERT(!m_connection);
}

bool GetPluginProcessConnection::DelayedReply::send(const CoreIPC::Attachment& connectionHandle, bool supportsAsynchronousInitialization)
{
    ASSERT(m_encoder);
    *m_encoder << connectionHandle;
    *m_encoder << supportsAsynchronousInitialization;
    bool result = m_connection->sendSyncReply(m_encoder.release());
    m_connection = nullptr;
    return result;
}

#endif

#if ENABLE(NETWORK_PROCESS)

GetNetworkProcessConnection::DelayedReply::DelayedReply(PassRefPtr<CoreIPC::Connection> connection, PassOwnPtr<CoreIPC::MessageEncoder> encoder)
    : m_connection(connection)
    , m_encoder(encoder)
{
}

GetNetworkProcessConnection::DelayedReply::~DelayedReply()
{
    ASSERT(!m_connection);
}

bool GetNetworkProcessConnection::DelayedReply::send(const CoreIPC::Attachment& connectionHandle)
{
    ASSERT(m_encoder);
    *m_encoder << connectionHandle;
    bool result = m_connection->sendSyncReply(m_encoder.release());
    m_connection = nullptr;
    return result;
}

#endif

#if ENABLE(SHARED_WORKER_PROCESS)

GetSharedWorkerProcessConnection::DelayedReply::DelayedReply(PassRefPtr<CoreIPC::Connection> connection, PassOwnPtr<CoreIPC::MessageEncoder> encoder)
    : m_connection(connection)
    , m_encoder(encoder)
{
}

GetSharedWorkerProcessConnection::DelayedReply::~DelayedReply()
{
    ASSERT(!m_connection);
}

bool GetSharedWorkerProcessConnection::DelayedReply::send(const CoreIPC::Attachment& connectionHandle)
{
    ASSERT(m_encoder);
    *m_encoder << connectionHandle;
    bool result = m_connection->sendSyncReply(m_encoder.release());
    m_connection = nullptr;
    return result;
}

#endif

} // namespace WebProcessProxy

} // namespace Messages

namespace WebKit {

void WebProcessProxy::didReceiveWebProcessProxyMessage(CoreIPC::Connection*, CoreIPC::MessageDecoder& decoder)
{
    if (decoder.messageName() == Messages::WebProcessProxy::DidNavigateWithNavigationData::name()) {
        CoreIPC::handleMessage<Messages::WebProcessProxy::DidNavigateWithNavigationData>(decoder, this, &WebProcessProxy::didNavigateWithNavigationData);
        return;
    }
    if (decoder.messageName() == Messages::WebProcessProxy::DidPerformClientRedirect::name()) {
        CoreIPC::handleMessage<Messages::WebProcessProxy::DidPerformClientRedirect>(decoder, this, &WebProcessProxy::didPerformClientRedirect);
        return;
    }
    if (decoder.messageName() == Messages::WebProcessProxy::DidPerformServerRedirect::name()) {
        CoreIPC::handleMessage<Messages::WebProcessProxy::DidPerformServerRedirect>(decoder, this, &WebProcessProxy::didPerformServerRedirect);
        return;
    }
    if (decoder.messageName() == Messages::WebProcessProxy::DidUpdateHistoryTitle::name()) {
        CoreIPC::handleMessage<Messages::WebProcessProxy::DidUpdateHistoryTitle>(decoder, this, &WebProcessProxy::didUpdateHistoryTitle);
        return;
    }
    if (decoder.messageName() == Messages::WebProcessProxy::AddBackForwardItem::name()) {
        CoreIPC::handleMessage<Messages::WebProcessProxy::AddBackForwardItem>(decoder, this, &WebProcessProxy::addBackForwardItem);
        return;
    }
    if (decoder.messageName() == Messages::WebProcessProxy::DidDestroyFrame::name()) {
        CoreIPC::handleMessage<Messages::WebProcessProxy::DidDestroyFrame>(decoder, this, &WebProcessProxy::didDestroyFrame);
        return;
    }
    if (decoder.messageName() == Messages::WebProcessProxy::EnableSuddenTermination::name()) {
        CoreIPC::handleMessage<Messages::WebProcessProxy::EnableSuddenTermination>(decoder, this, &WebProcessProxy::enableSuddenTermination);
        return;
    }
    if (decoder.messageName() == Messages::WebProcessProxy::DisableSuddenTermination::name()) {
        CoreIPC::handleMessage<Messages::WebProcessProxy::DisableSuddenTermination>(decoder, this, &WebProcessProxy::disableSuddenTermination);
        return;
    }
#if ENABLE(NETSCAPE_PLUGIN_API) && !ENABLE(PLUGIN_PROCESS)
    if (decoder.messageName() == Messages::WebProcessProxy::DidGetSitesWithPluginData::name()) {
        CoreIPC::handleMessage<Messages::WebProcessProxy::DidGetSitesWithPluginData>(decoder, this, &WebProcessProxy::didGetSitesWithPluginData);
        return;
    }
#endif
#if ENABLE(NETSCAPE_PLUGIN_API) && !ENABLE(PLUGIN_PROCESS)
    if (decoder.messageName() == Messages::WebProcessProxy::DidClearPluginSiteData::name()) {
        CoreIPC::handleMessage<Messages::WebProcessProxy::DidClearPluginSiteData>(decoder, this, &WebProcessProxy::didClearPluginSiteData);
        return;
    }
#endif
    ASSERT_NOT_REACHED();
}

void WebProcessProxy::didReceiveSyncWebProcessProxyMessage(CoreIPC::Connection* connection, CoreIPC::MessageDecoder& decoder, OwnPtr<CoreIPC::MessageEncoder>& replyEncoder)
{
    if (decoder.messageName() == Messages::WebProcessProxy::ShouldTerminate::name()) {
        CoreIPC::handleMessage<Messages::WebProcessProxy::ShouldTerminate>(decoder, *replyEncoder, this, &WebProcessProxy::shouldTerminate);
        return;
    }
#if ENABLE(NETSCAPE_PLUGIN_API)
    if (decoder.messageName() == Messages::WebProcessProxy::GetPlugins::name()) {
        CoreIPC::handleMessage<Messages::WebProcessProxy::GetPlugins>(decoder, *replyEncoder, this, &WebProcessProxy::getPlugins);
        return;
    }
#endif
#if ENABLE(PLUGIN_PROCESS)
    if (decoder.messageName() == Messages::WebProcessProxy::GetPluginProcessConnection::name()) {
        CoreIPC::handleMessageDelayed<Messages::WebProcessProxy::GetPluginProcessConnection>(connection, decoder, replyEncoder, this, &WebProcessProxy::getPluginProcessConnection);
        return;
    }
#endif
#if ENABLE(NETWORK_PROCESS)
    if (decoder.messageName() == Messages::WebProcessProxy::GetNetworkProcessConnection::name()) {
        CoreIPC::handleMessageDelayed<Messages::WebProcessProxy::GetNetworkProcessConnection>(connection, decoder, replyEncoder, this, &WebProcessProxy::getNetworkProcessConnection);
        return;
    }
#endif
#if ENABLE(SHARED_WORKER_PROCESS)
    if (decoder.messageName() == Messages::WebProcessProxy::GetSharedWorkerProcessConnection::name()) {
        CoreIPC::handleMessageDelayed<Messages::WebProcessProxy::GetSharedWorkerProcessConnection>(connection, decoder, replyEncoder, this, &WebProcessProxy::getSharedWorkerProcessConnection);
        return;
    }
#endif
    ASSERT_NOT_REACHED();
}

} // namespace WebKit
