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

#ifndef WebTileManagerMessages_h
#define WebTileManagerMessages_h

#if ENABLE(MANX_HTMLTILE)

#include "Arguments.h"
#include "MessageEncoder.h"
#include "StringReference.h"

namespace WTF {
    class String;
}

namespace WebKit {
    class UpdateInfo;
}

namespace Messages {
namespace WebTileManager {

static inline CoreIPC::StringReference messageReceiverName()
{
    return CoreIPC::StringReference("WebTileManager");
}

struct TileUpdated : CoreIPC::Arguments2<uint64_t, const WebKit::UpdateInfo&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("TileUpdated"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, const WebKit::UpdateInfo&> DecodeType;
    TileUpdated(uint64_t tileID, const WebKit::UpdateInfo& updateInfo)
        : CoreIPC::Arguments2<uint64_t, const WebKit::UpdateInfo&>(tileID, updateInfo)
    {
    }
};

struct TileUnresponsive : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("TileUnresponsive"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit TileUnresponsive(uint64_t tileID)
        : CoreIPC::Arguments1<uint64_t>(tileID)
    {
    }
};

struct TileCrashed : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("TileCrashed"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit TileCrashed(uint64_t tileID)
        : CoreIPC::Arguments1<uint64_t>(tileID)
    {
    }
};

struct LoadCompleted : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("LoadCompleted"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit LoadCompleted(uint64_t tileID)
        : CoreIPC::Arguments1<uint64_t>(tileID)
    {
    }
};

struct LoadFailed : CoreIPC::Arguments2<uint64_t, uint32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("LoadFailed"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, uint32_t> DecodeType;
    LoadFailed(uint64_t tileID, uint32_t errorCode)
        : CoreIPC::Arguments2<uint64_t, uint32_t>(tileID, errorCode)
    {
    }
};

struct LocationChangeRequested : CoreIPC::Arguments2<uint64_t, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("LocationChangeRequested"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, const WTF::String&> DecodeType;
    LocationChangeRequested(uint64_t tileID, const WTF::String& urlString)
        : CoreIPC::Arguments2<uint64_t, const WTF::String&>(tileID, urlString)
    {
    }
};

struct RunJavaScriptResultCallback : CoreIPC::Arguments3<uint64_t, uint64_t, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RunJavaScriptResultCallback"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<uint64_t, uint64_t, const WTF::String&> DecodeType;
    RunJavaScriptResultCallback(uint64_t tileID, uint64_t callbackID, const WTF::String& result)
        : CoreIPC::Arguments3<uint64_t, uint64_t, const WTF::String&>(tileID, callbackID, result)
    {
    }
};

} // namespace WebTileManager
} // namespace Messages

#endif // ENABLE(MANX_HTMLTILE)

#endif // WebTileManagerMessages_h
