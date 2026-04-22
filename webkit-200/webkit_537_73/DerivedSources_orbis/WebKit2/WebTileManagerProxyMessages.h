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

#ifndef WebTileManagerProxyMessages_h
#define WebTileManagerProxyMessages_h

#if ENABLE(MANX_HTMLTILE)

#include "Arguments.h"
#include "MessageEncoder.h"
#include "StringReference.h"

namespace WTF {
    class String;
}

namespace Messages {
namespace WebTileManagerProxy {

static inline CoreIPC::StringReference messageReceiverName()
{
    return CoreIPC::StringReference("WebTileManagerProxy");
}

struct CreateWebTile : CoreIPC::Arguments3<uint32_t, uint32_t, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CreateWebTile"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<uint64_t&> Reply;
    typedef CoreIPC::Arguments3<uint32_t, uint32_t, uint64_t> DecodeType;
    CreateWebTile(uint32_t width, uint32_t height, uint64_t pageID)
        : CoreIPC::Arguments3<uint32_t, uint32_t, uint64_t>(width, height, pageID)
    {
    }
};

struct DestroyWebTile : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DestroyWebTile"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit DestroyWebTile(uint64_t tileID)
        : CoreIPC::Arguments1<uint64_t>(tileID)
    {
    }
};

struct PauseWebTile : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("PauseWebTile"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit PauseWebTile(uint64_t tileID)
        : CoreIPC::Arguments1<uint64_t>(tileID)
    {
    }
};

struct ResumeWebTile : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ResumeWebTile"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit ResumeWebTile(uint64_t tileID)
        : CoreIPC::Arguments1<uint64_t>(tileID)
    {
    }
};

struct SendWebTileEvent : CoreIPC::Arguments2<uint64_t, uint32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SendWebTileEvent"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, uint32_t> DecodeType;
    SendWebTileEvent(uint64_t tileID, uint32_t type)
        : CoreIPC::Arguments2<uint64_t, uint32_t>(tileID, type)
    {
    }
};

struct RunJavaScriptInWebTile : CoreIPC::Arguments3<uint64_t, const WTF::String&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RunJavaScriptInWebTile"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<uint64_t, const WTF::String&, uint64_t> DecodeType;
    RunJavaScriptInWebTile(uint64_t tileID, const WTF::String& jsScript, uint64_t callbackID)
        : CoreIPC::Arguments3<uint64_t, const WTF::String&, uint64_t>(tileID, jsScript, callbackID)
    {
    }
};

struct DidChangeWebTileURL : CoreIPC::Arguments2<uint64_t, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidChangeWebTileURL"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, const WTF::String&> DecodeType;
    DidChangeWebTileURL(uint64_t tileID, const WTF::String& urlString)
        : CoreIPC::Arguments2<uint64_t, const WTF::String&>(tileID, urlString)
    {
    }
};

struct DidUpdateWebTile : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidUpdateWebTile"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit DidUpdateWebTile(uint64_t tileID)
        : CoreIPC::Arguments1<uint64_t>(tileID)
    {
    }
};

} // namespace WebTileManagerProxy
} // namespace Messages

#endif // ENABLE(MANX_HTMLTILE)

#endif // WebTileManagerProxyMessages_h
