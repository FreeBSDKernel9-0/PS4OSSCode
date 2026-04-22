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

#if ENABLE(MANX_HTMLTILE)

#include "WebTileManagerProxy.h"

#include "ArgumentCoders.h"
#include "HandleMessage.h"
#include "MessageDecoder.h"
#include "WebTileManagerProxyMessages.h"
#include <wtf/text/WTFString.h>

namespace WebKit {

void WebTileManagerProxy::didReceiveMessage(CoreIPC::Connection* connection, CoreIPC::MessageDecoder& decoder)
{
    if (decoder.messageName() == Messages::WebTileManagerProxy::DestroyWebTile::name()) {
        CoreIPC::handleMessage<Messages::WebTileManagerProxy::DestroyWebTile>(decoder, this, &WebTileManagerProxy::destroyWebTile);
        return;
    }
    if (decoder.messageName() == Messages::WebTileManagerProxy::PauseWebTile::name()) {
        CoreIPC::handleMessage<Messages::WebTileManagerProxy::PauseWebTile>(decoder, this, &WebTileManagerProxy::pauseWebTile);
        return;
    }
    if (decoder.messageName() == Messages::WebTileManagerProxy::ResumeWebTile::name()) {
        CoreIPC::handleMessage<Messages::WebTileManagerProxy::ResumeWebTile>(decoder, this, &WebTileManagerProxy::resumeWebTile);
        return;
    }
    if (decoder.messageName() == Messages::WebTileManagerProxy::SendWebTileEvent::name()) {
        CoreIPC::handleMessage<Messages::WebTileManagerProxy::SendWebTileEvent>(decoder, this, &WebTileManagerProxy::sendWebTileEvent);
        return;
    }
    if (decoder.messageName() == Messages::WebTileManagerProxy::RunJavaScriptInWebTile::name()) {
        CoreIPC::handleMessage<Messages::WebTileManagerProxy::RunJavaScriptInWebTile>(decoder, this, &WebTileManagerProxy::runJavaScriptInWebTile);
        return;
    }
    if (decoder.messageName() == Messages::WebTileManagerProxy::DidChangeWebTileURL::name()) {
        CoreIPC::handleMessage<Messages::WebTileManagerProxy::DidChangeWebTileURL>(decoder, this, &WebTileManagerProxy::didChangeWebTileURL);
        return;
    }
    if (decoder.messageName() == Messages::WebTileManagerProxy::DidUpdateWebTile::name()) {
        CoreIPC::handleMessage<Messages::WebTileManagerProxy::DidUpdateWebTile>(decoder, this, &WebTileManagerProxy::didUpdateWebTile);
        return;
    }
    UNUSED_PARAM(connection);
    ASSERT_NOT_REACHED();
}

void WebTileManagerProxy::didReceiveSyncMessage(CoreIPC::Connection* connection, CoreIPC::MessageDecoder& decoder, OwnPtr<CoreIPC::MessageEncoder>& replyEncoder)
{
    if (decoder.messageName() == Messages::WebTileManagerProxy::CreateWebTile::name()) {
        CoreIPC::handleMessage<Messages::WebTileManagerProxy::CreateWebTile>(decoder, *replyEncoder, this, &WebTileManagerProxy::createWebTile);
        return;
    }
    UNUSED_PARAM(connection);
    ASSERT_NOT_REACHED();
}

} // namespace WebKit

#endif // ENABLE(MANX_HTMLTILE)
