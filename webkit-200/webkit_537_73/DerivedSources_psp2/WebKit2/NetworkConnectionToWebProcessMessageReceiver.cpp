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

#if ENABLE(NETWORK_PROCESS)

#include "NetworkConnectionToWebProcess.h"

#include "ArgumentCoders.h"
#include "BlobRegistrationData.h"
#include "DataReference.h"
#include "HandleMessage.h"
#include "MessageDecoder.h"
#include "NetworkConnectionToWebProcessMessages.h"
#include "NetworkResourceLoadParameters.h"
#include "WebCoreArgumentCoders.h"
#include <WebCore/Cookie.h>
#include <WebCore/KURL.h>
#include <WebCore/ResourceError.h>
#include <WebCore/ResourceRequest.h>
#include <WebCore/ResourceResponse.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace Messages {

namespace NetworkConnectionToWebProcess {

PerformSynchronousLoad::DelayedReply::DelayedReply(PassRefPtr<CoreIPC::Connection> connection, PassOwnPtr<CoreIPC::MessageEncoder> encoder)
    : m_connection(connection)
    , m_encoder(encoder)
{
}

PerformSynchronousLoad::DelayedReply::~DelayedReply()
{
    ASSERT(!m_connection);
}

bool PerformSynchronousLoad::DelayedReply::send(const WebCore::ResourceError& error, const WebCore::ResourceResponse& response, const CoreIPC::DataReference& data)
{
    ASSERT(m_encoder);
    *m_encoder << error;
    *m_encoder << response;
    *m_encoder << data;
    bool result = m_connection->sendSyncReply(m_encoder.release());
    m_connection = nullptr;
    return result;
}

} // namespace NetworkConnectionToWebProcess

} // namespace Messages

namespace WebKit {

void NetworkConnectionToWebProcess::didReceiveNetworkConnectionToWebProcessMessage(CoreIPC::Connection*, CoreIPC::MessageDecoder& decoder)
{
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::ScheduleResourceLoad::name()) {
        CoreIPC::handleMessage<Messages::NetworkConnectionToWebProcess::ScheduleResourceLoad>(decoder, this, &NetworkConnectionToWebProcess::scheduleResourceLoad);
        return;
    }
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::RemoveLoadIdentifier::name()) {
        CoreIPC::handleMessage<Messages::NetworkConnectionToWebProcess::RemoveLoadIdentifier>(decoder, this, &NetworkConnectionToWebProcess::removeLoadIdentifier);
        return;
    }
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::ServePendingRequests::name()) {
        CoreIPC::handleMessage<Messages::NetworkConnectionToWebProcess::ServePendingRequests>(decoder, this, &NetworkConnectionToWebProcess::servePendingRequests);
        return;
    }
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::StartDownload::name()) {
        CoreIPC::handleMessage<Messages::NetworkConnectionToWebProcess::StartDownload>(decoder, this, &NetworkConnectionToWebProcess::startDownload);
        return;
    }
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::ConvertMainResourceLoadToDownload::name()) {
        CoreIPC::handleMessage<Messages::NetworkConnectionToWebProcess::ConvertMainResourceLoadToDownload>(decoder, this, &NetworkConnectionToWebProcess::convertMainResourceLoadToDownload);
        return;
    }
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::SetCookiesFromDOM::name()) {
        CoreIPC::handleMessage<Messages::NetworkConnectionToWebProcess::SetCookiesFromDOM>(decoder, this, &NetworkConnectionToWebProcess::setCookiesFromDOM);
        return;
    }
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::DeleteCookie::name()) {
        CoreIPC::handleMessage<Messages::NetworkConnectionToWebProcess::DeleteCookie>(decoder, this, &NetworkConnectionToWebProcess::deleteCookie);
        return;
    }
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::RegisterBlobURL::name()) {
        CoreIPC::handleMessage<Messages::NetworkConnectionToWebProcess::RegisterBlobURL>(decoder, this, &NetworkConnectionToWebProcess::registerBlobURL);
        return;
    }
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::RegisterBlobURLFromURL::name()) {
        CoreIPC::handleMessage<Messages::NetworkConnectionToWebProcess::RegisterBlobURLFromURL>(decoder, this, &NetworkConnectionToWebProcess::registerBlobURLFromURL);
        return;
    }
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::UnregisterBlobURL::name()) {
        CoreIPC::handleMessage<Messages::NetworkConnectionToWebProcess::UnregisterBlobURL>(decoder, this, &NetworkConnectionToWebProcess::unregisterBlobURL);
        return;
    }
    ASSERT_NOT_REACHED();
}

void NetworkConnectionToWebProcess::didReceiveSyncNetworkConnectionToWebProcessMessage(CoreIPC::Connection* connection, CoreIPC::MessageDecoder& decoder, OwnPtr<CoreIPC::MessageEncoder>& replyEncoder)
{
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::PerformSynchronousLoad::name()) {
        CoreIPC::handleMessageDelayed<Messages::NetworkConnectionToWebProcess::PerformSynchronousLoad>(connection, decoder, replyEncoder, this, &NetworkConnectionToWebProcess::performSynchronousLoad);
        return;
    }
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::SetSerialLoadingEnabled::name()) {
        CoreIPC::handleMessage<Messages::NetworkConnectionToWebProcess::SetSerialLoadingEnabled>(decoder, *replyEncoder, this, &NetworkConnectionToWebProcess::setSerialLoadingEnabled);
        return;
    }
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::CookiesForDOM::name()) {
        CoreIPC::handleMessage<Messages::NetworkConnectionToWebProcess::CookiesForDOM>(decoder, *replyEncoder, this, &NetworkConnectionToWebProcess::cookiesForDOM);
        return;
    }
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::CookiesEnabled::name()) {
        CoreIPC::handleMessage<Messages::NetworkConnectionToWebProcess::CookiesEnabled>(decoder, *replyEncoder, this, &NetworkConnectionToWebProcess::cookiesEnabled);
        return;
    }
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::CookieRequestHeaderFieldValue::name()) {
        CoreIPC::handleMessage<Messages::NetworkConnectionToWebProcess::CookieRequestHeaderFieldValue>(decoder, *replyEncoder, this, &NetworkConnectionToWebProcess::cookieRequestHeaderFieldValue);
        return;
    }
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::GetRawCookies::name()) {
        CoreIPC::handleMessage<Messages::NetworkConnectionToWebProcess::GetRawCookies>(decoder, *replyEncoder, this, &NetworkConnectionToWebProcess::getRawCookies);
        return;
    }
    ASSERT_NOT_REACHED();
}

} // namespace WebKit

#endif // ENABLE(NETWORK_PROCESS)
