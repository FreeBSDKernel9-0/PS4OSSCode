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

#include "WebResourceLoader.h"

#include "DataReference.h"
#include "HandleMessage.h"
#include "MessageDecoder.h"
#include "PlatformCertificateInfo.h"
#include "ShareableResource.h"
#include "WebCoreArgumentCoders.h"
#include "WebResourceLoaderMessages.h"
#include <WebCore/ProtectionSpace.h>
#include <WebCore/ResourceError.h>
#include <WebCore/ResourceRequest.h>
#include <WebCore/ResourceResponse.h>

namespace WebKit {

void WebResourceLoader::didReceiveWebResourceLoaderMessage(CoreIPC::Connection*, CoreIPC::MessageDecoder& decoder)
{
    if (decoder.messageName() == Messages::WebResourceLoader::CancelResourceLoader::name()) {
        CoreIPC::handleMessage<Messages::WebResourceLoader::CancelResourceLoader>(decoder, this, &WebResourceLoader::cancelResourceLoader);
        return;
    }
    if (decoder.messageName() == Messages::WebResourceLoader::WillSendRequest::name()) {
        CoreIPC::handleMessage<Messages::WebResourceLoader::WillSendRequest>(decoder, this, &WebResourceLoader::willSendRequest);
        return;
    }
    if (decoder.messageName() == Messages::WebResourceLoader::DidSendData::name()) {
        CoreIPC::handleMessage<Messages::WebResourceLoader::DidSendData>(decoder, this, &WebResourceLoader::didSendData);
        return;
    }
    if (decoder.messageName() == Messages::WebResourceLoader::DidReceiveResponseWithCertificateInfo::name()) {
        CoreIPC::handleMessage<Messages::WebResourceLoader::DidReceiveResponseWithCertificateInfo>(decoder, this, &WebResourceLoader::didReceiveResponseWithCertificateInfo);
        return;
    }
    if (decoder.messageName() == Messages::WebResourceLoader::DidReceiveData::name()) {
        CoreIPC::handleMessage<Messages::WebResourceLoader::DidReceiveData>(decoder, this, &WebResourceLoader::didReceiveData);
        return;
    }
    if (decoder.messageName() == Messages::WebResourceLoader::DidFinishResourceLoad::name()) {
        CoreIPC::handleMessage<Messages::WebResourceLoader::DidFinishResourceLoad>(decoder, this, &WebResourceLoader::didFinishResourceLoad);
        return;
    }
    if (decoder.messageName() == Messages::WebResourceLoader::DidFailResourceLoad::name()) {
        CoreIPC::handleMessage<Messages::WebResourceLoader::DidFailResourceLoad>(decoder, this, &WebResourceLoader::didFailResourceLoad);
        return;
    }
    if (decoder.messageName() == Messages::WebResourceLoader::CanAuthenticateAgainstProtectionSpace::name()) {
        CoreIPC::handleMessage<Messages::WebResourceLoader::CanAuthenticateAgainstProtectionSpace>(decoder, this, &WebResourceLoader::canAuthenticateAgainstProtectionSpace);
        return;
    }
    if (decoder.messageName() == Messages::WebResourceLoader::DidReceiveResource::name()) {
        CoreIPC::handleMessage<Messages::WebResourceLoader::DidReceiveResource>(decoder, this, &WebResourceLoader::didReceiveResource);
        return;
    }
    ASSERT_NOT_REACHED();
}

} // namespace WebKit
