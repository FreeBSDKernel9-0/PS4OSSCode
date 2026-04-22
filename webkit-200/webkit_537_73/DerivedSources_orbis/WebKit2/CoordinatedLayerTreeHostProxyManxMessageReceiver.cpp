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

#if USE(COORDINATED_GRAPHICS) && ENABLE(MANX_AC_PROCESS)

#include "CoordinatedLayerTreeHostProxyManx.h"

#include "CoordinatedLayerTreeHostProxyManxMessages.h"
#include "HandleMessage.h"
#include "MessageDecoder.h"
#include "WebCoreArgumentCoders.h"
#include <WebCore/Color.h>
#include <WebCore/CoordinatedGraphicsState.h>
#include <WebCore/IntSize.h>

namespace WebKit {

void CoordinatedLayerTreeHostProxyManx::didReceiveMessage(CoreIPC::Connection* connection, CoreIPC::MessageDecoder& decoder)
{
    if (decoder.messageName() == Messages::CoordinatedLayerTreeHostProxyManx::CommitCoordinatedGraphicsState::name()) {
        CoreIPC::handleMessage<Messages::CoordinatedLayerTreeHostProxyManx::CommitCoordinatedGraphicsState>(decoder, this, &CoordinatedLayerTreeHostProxyManx::commitCoordinatedGraphicsState);
        return;
    }
    if (decoder.messageName() == Messages::CoordinatedLayerTreeHostProxyManx::SetBackgroundColor::name()) {
        CoreIPC::handleMessage<Messages::CoordinatedLayerTreeHostProxyManx::SetBackgroundColor>(decoder, this, &CoordinatedLayerTreeHostProxyManx::setBackgroundColor);
        return;
    }
    if (decoder.messageName() == Messages::CoordinatedLayerTreeHostProxyManx::SizeDidChange::name()) {
        CoreIPC::handleMessage<Messages::CoordinatedLayerTreeHostProxyManx::SizeDidChange>(decoder, this, &CoordinatedLayerTreeHostProxyManx::sizeDidChange);
        return;
    }
    if (decoder.messageName() == Messages::CoordinatedLayerTreeHostProxyManx::SetVisible::name()) {
        CoreIPC::handleMessage<Messages::CoordinatedLayerTreeHostProxyManx::SetVisible>(decoder, this, &CoordinatedLayerTreeHostProxyManx::setVisible);
        return;
    }
    if (decoder.messageName() == Messages::CoordinatedLayerTreeHostProxyManx::SetActive::name()) {
        CoreIPC::handleMessage<Messages::CoordinatedLayerTreeHostProxyManx::SetActive>(decoder, this, &CoordinatedLayerTreeHostProxyManx::setActive);
        return;
    }
    UNUSED_PARAM(connection);
    ASSERT_NOT_REACHED();
}

} // namespace WebKit

#endif // USE(COORDINATED_GRAPHICS) && ENABLE(MANX_AC_PROCESS)
