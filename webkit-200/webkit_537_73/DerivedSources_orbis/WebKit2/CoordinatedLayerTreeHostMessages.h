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

#ifndef CoordinatedLayerTreeHostMessages_h
#define CoordinatedLayerTreeHostMessages_h

#if USE(COORDINATED_GRAPHICS)

#include "Arguments.h"
#include "MessageEncoder.h"
#include "StringReference.h"

namespace WebCore {
    class FloatRect;
    class FloatPoint;
    class IntSize;
}

namespace Messages {
namespace CoordinatedLayerTreeHost {

static inline CoreIPC::StringReference messageReceiverName()
{
    return CoreIPC::StringReference("CoordinatedLayerTreeHost");
}

struct SetVisibleContentsRect : CoreIPC::Arguments2<const WebCore::FloatRect&, const WebCore::FloatPoint&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetVisibleContentsRect"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WebCore::FloatRect&, const WebCore::FloatPoint&> DecodeType;
    SetVisibleContentsRect(const WebCore::FloatRect& visibleContentsRect, const WebCore::FloatPoint& trajectoryVectory)
        : CoreIPC::Arguments2<const WebCore::FloatRect&, const WebCore::FloatPoint&>(visibleContentsRect, trajectoryVectory)
    {
    }
};

struct RenderNextFrame : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RenderNextFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct PurgeBackingStores : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("PurgeBackingStores"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct CommitScrollOffset : CoreIPC::Arguments2<uint32_t, const WebCore::IntSize&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CommitScrollOffset"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint32_t, const WebCore::IntSize&> DecodeType;
    CommitScrollOffset(uint32_t layerID, const WebCore::IntSize& offset)
        : CoreIPC::Arguments2<uint32_t, const WebCore::IntSize&>(layerID, offset)
    {
    }
};

#if ENABLE(MANX_AC_PROCESS)
struct SetCanvasHandle : CoreIPC::Arguments1<uint32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetCanvasHandle"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint32_t> DecodeType;
    explicit SetCanvasHandle(uint32_t canvasHandle)
        : CoreIPC::Arguments1<uint32_t>(canvasHandle)
    {
    }
};
#endif

#if ENABLE(MANX_AC_PROCESS)
struct DidCreateProxy : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidCreateProxy"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

} // namespace CoordinatedLayerTreeHost
} // namespace Messages

#endif // USE(COORDINATED_GRAPHICS)

#endif // CoordinatedLayerTreeHostMessages_h
