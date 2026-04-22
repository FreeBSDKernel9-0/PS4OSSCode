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

#ifndef WebInspectorProxyMessages_h
#define WebInspectorProxyMessages_h

#if ENABLE(INSPECTOR)

#include "Arguments.h"
#include "MessageEncoder.h"
#include "StringReference.h"

namespace WTF {
    class String;
}

namespace WebKit {
    struct WebPageCreationParameters;
}

namespace Messages {
namespace WebInspectorProxy {

static inline CoreIPC::StringReference messageReceiverName()
{
    return CoreIPC::StringReference("WebInspectorProxy");
}

struct CreateInspectorPage : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CreateInspectorPage"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments2<uint64_t&, WebKit::WebPageCreationParameters&> Reply;
    typedef CoreIPC::Arguments0 DecodeType;
};

struct DidClose : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidClose"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct BringToFront : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("BringToFront"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct InspectedURLChanged : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("InspectedURLChanged"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit InspectedURLChanged(const WTF::String& urlString)
        : CoreIPC::Arguments1<const WTF::String&>(urlString)
    {
    }
};

struct Save : CoreIPC::Arguments3<const WTF::String&, const WTF::String&, bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("Save"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<const WTF::String&, const WTF::String&, bool> DecodeType;
    Save(const WTF::String& filename, const WTF::String& content, bool forceSaveAs)
        : CoreIPC::Arguments3<const WTF::String&, const WTF::String&, bool>(filename, content, forceSaveAs)
    {
    }
};

struct Append : CoreIPC::Arguments2<const WTF::String&, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("Append"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WTF::String&, const WTF::String&> DecodeType;
    Append(const WTF::String& filename, const WTF::String& content)
        : CoreIPC::Arguments2<const WTF::String&, const WTF::String&>(filename, content)
    {
    }
};

struct AttachBottom : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("AttachBottom"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct AttachRight : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("AttachRight"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct Detach : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("Detach"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct AttachAvailabilityChanged : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("AttachAvailabilityChanged"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit AttachAvailabilityChanged(bool available)
        : CoreIPC::Arguments1<bool>(available)
    {
    }
};

struct SetAttachedWindowHeight : CoreIPC::Arguments1<const unsigned&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetAttachedWindowHeight"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const unsigned&> DecodeType;
    explicit SetAttachedWindowHeight(const unsigned& height)
        : CoreIPC::Arguments1<const unsigned&>(height)
    {
    }
};

struct SetAttachedWindowWidth : CoreIPC::Arguments1<const unsigned&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetAttachedWindowWidth"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const unsigned&> DecodeType;
    explicit SetAttachedWindowWidth(const unsigned& width)
        : CoreIPC::Arguments1<const unsigned&>(width)
    {
    }
};

struct SetToolbarHeight : CoreIPC::Arguments1<const unsigned&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetToolbarHeight"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const unsigned&> DecodeType;
    explicit SetToolbarHeight(const unsigned& height)
        : CoreIPC::Arguments1<const unsigned&>(height)
    {
    }
};

#if ENABLE(INSPECTOR_SERVER)
struct SendMessageToRemoteFrontend : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SendMessageToRemoteFrontend"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit SendMessageToRemoteFrontend(const WTF::String& message)
        : CoreIPC::Arguments1<const WTF::String&>(message)
    {
    }
};
#endif

} // namespace WebInspectorProxy
} // namespace Messages

#endif // ENABLE(INSPECTOR)

#endif // WebInspectorProxyMessages_h
