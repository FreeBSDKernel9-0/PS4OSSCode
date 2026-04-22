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

#include "NetworkProcess.h"

#include "ArgumentCoders.h"
#include "HandleMessage.h"
#include "MessageDecoder.h"
#include "NetworkProcessCreationParameters.h"
#include "NetworkProcessMessages.h"
#include "PlatformCertificateInfo.h"
#include "WebCoreArgumentCoders.h"
#include <WebCore/ResourceRequest.h>
#include <wtf/text/WTFString.h>

namespace WebKit {

void NetworkProcess::didReceiveNetworkProcessMessage(CoreIPC::Connection*, CoreIPC::MessageDecoder& decoder)
{
    if (decoder.messageName() == Messages::NetworkProcess::InitializeNetworkProcess::name()) {
        CoreIPC::handleMessage<Messages::NetworkProcess::InitializeNetworkProcess>(decoder, this, &NetworkProcess::initializeNetworkProcess);
        return;
    }
    if (decoder.messageName() == Messages::NetworkProcess::CreateNetworkConnectionToWebProcess::name()) {
        CoreIPC::handleMessage<Messages::NetworkProcess::CreateNetworkConnectionToWebProcess>(decoder, this, &NetworkProcess::createNetworkConnectionToWebProcess);
        return;
    }
    if (decoder.messageName() == Messages::NetworkProcess::EnsurePrivateBrowsingSession::name()) {
        CoreIPC::handleMessage<Messages::NetworkProcess::EnsurePrivateBrowsingSession>(decoder, this, &NetworkProcess::ensurePrivateBrowsingSession);
        return;
    }
    if (decoder.messageName() == Messages::NetworkProcess::DestroyPrivateBrowsingSession::name()) {
        CoreIPC::handleMessage<Messages::NetworkProcess::DestroyPrivateBrowsingSession>(decoder, this, &NetworkProcess::destroyPrivateBrowsingSession);
        return;
    }
    if (decoder.messageName() == Messages::NetworkProcess::DownloadRequest::name()) {
        CoreIPC::handleMessage<Messages::NetworkProcess::DownloadRequest>(decoder, this, &NetworkProcess::downloadRequest);
        return;
    }
    if (decoder.messageName() == Messages::NetworkProcess::CancelDownload::name()) {
        CoreIPC::handleMessage<Messages::NetworkProcess::CancelDownload>(decoder, this, &NetworkProcess::cancelDownload);
        return;
    }
#if PLATFORM(MAC)
    if (decoder.messageName() == Messages::NetworkProcess::SetProcessSuppressionEnabled::name()) {
        CoreIPC::handleMessage<Messages::NetworkProcess::SetProcessSuppressionEnabled>(decoder, this, &NetworkProcess::setProcessSuppressionEnabled);
        return;
    }
#endif
    if (decoder.messageName() == Messages::NetworkProcess::AllowSpecificHTTPSCertificateForHost::name()) {
        CoreIPC::handleMessage<Messages::NetworkProcess::AllowSpecificHTTPSCertificateForHost>(decoder, this, &NetworkProcess::allowSpecificHTTPSCertificateForHost);
        return;
    }
    if (decoder.messageName() == Messages::NetworkProcess::GetNetworkProcessStatistics::name()) {
        CoreIPC::handleMessage<Messages::NetworkProcess::GetNetworkProcessStatistics>(decoder, this, &NetworkProcess::getNetworkProcessStatistics);
        return;
    }
    if (decoder.messageName() == Messages::NetworkProcess::ClearCacheForAllOrigins::name()) {
        CoreIPC::handleMessage<Messages::NetworkProcess::ClearCacheForAllOrigins>(decoder, this, &NetworkProcess::clearCacheForAllOrigins);
        return;
    }
    ASSERT_NOT_REACHED();
}

} // namespace WebKit

#endif // ENABLE(NETWORK_PROCESS)
