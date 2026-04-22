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

#ifndef CoordinatedLayerTreeHostProxyManxMessages_h
#define CoordinatedLayerTreeHostProxyManxMessages_h

#if USE(COORDINATED_GRAPHICS) && ENABLE(MANX_AC_PROCESS)

#include "Arguments.h"
#include "MessageEncoder.h"
#include "StringReference.h"

namespace WebCore {
    class Color;
    class CoordinatedGraphicsState;
    class IntSize;
}

namespace Messages {
namespace CoordinatedLayerTreeHostProxyManx {

static inline CoreIPC::StringReference messageReceiverName()
{
    return CoreIPC::StringReference("CoordinatedLayerTreeHostProxyManx");
}

struct CommitCoordinatedGraphicsState : CoreIPC::Arguments1<const WebCore::CoordinatedGraphicsState&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CommitCoordinatedGraphicsState"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebCore::CoordinatedGraphicsState&> DecodeType;
    explicit CommitCoordinatedGraphicsState(const WebCore::CoordinatedGraphicsState& state)
        : CoreIPC::Arguments1<const WebCore::CoordinatedGraphicsState&>(state)
    {
    }
};

struct SetBackgroundColor : CoreIPC::Arguments1<const WebCore::Color&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetBackgroundColor"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebCore::Color&> DecodeType;
    explicit SetBackgroundColor(const WebCore::Color& color)
        : CoreIPC::Arguments1<const WebCore::Color&>(color)
    {
    }
};

struct SizeDidChange : CoreIPC::Arguments1<const WebCore::IntSize&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SizeDidChange"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebCore::IntSize&> DecodeType;
    explicit SizeDidChange(const WebCore::IntSize& newSize)
        : CoreIPC::Arguments1<const WebCore::IntSize&>(newSize)
    {
    }
};

struct SetVisible : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetVisible"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetVisible(bool isVisible)
        : CoreIPC::Arguments1<bool>(isVisible)
    {
    }
};

struct SetActive : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetActive"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetActive(bool isActive)
        : CoreIPC::Arguments1<bool>(isActive)
    {
    }
};

} // namespace CoordinatedLayerTreeHostProxyManx
} // namespace Messages

#endif // USE(COORDINATED_GRAPHICS) && ENABLE(MANX_AC_PROCESS)

#endif // CoordinatedLayerTreeHostProxyManxMessages_h
