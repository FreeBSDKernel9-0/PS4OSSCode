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

#ifndef WebInspectorMessages_h
#define WebInspectorMessages_h

#if ENABLE(INSPECTOR)

#include "Arguments.h"
#include "MessageEncoder.h"
#include "StringReference.h"

namespace WTF {
    class String;
}

namespace Messages {
namespace WebInspector {

static inline CoreIPC::StringReference messageReceiverName()
{
    return CoreIPC::StringReference("WebInspector");
}

struct Show : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("Show"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct Close : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("Close"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct AttachedBottom : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("AttachedBottom"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct AttachedRight : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("AttachedRight"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct Detached : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("Detached"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct DidSave : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidSave"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit DidSave(const WTF::String& url)
        : CoreIPC::Arguments1<const WTF::String&>(url)
    {
    }
};

struct DidAppend : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidAppend"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit DidAppend(const WTF::String& url)
        : CoreIPC::Arguments1<const WTF::String&>(url)
    {
    }
};

struct ShowConsole : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ShowConsole"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct ShowResources : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ShowResources"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct ShowMainResourceForFrame : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ShowMainResourceForFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit ShowMainResourceForFrame(uint64_t frameID)
        : CoreIPC::Arguments1<uint64_t>(frameID)
    {
    }
};

struct StartJavaScriptDebugging : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("StartJavaScriptDebugging"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct StopJavaScriptDebugging : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("StopJavaScriptDebugging"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct StartJavaScriptProfiling : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("StartJavaScriptProfiling"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct StopJavaScriptProfiling : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("StopJavaScriptProfiling"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct StartPageProfiling : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("StartPageProfiling"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct StopPageProfiling : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("StopPageProfiling"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

#if ENABLE(INSPECTOR_SERVER)
struct DispatchMessageFromRemoteFrontend : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DispatchMessageFromRemoteFrontend"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit DispatchMessageFromRemoteFrontend(const WTF::String& message)
        : CoreIPC::Arguments1<const WTF::String&>(message)
    {
    }
};
#endif

#if ENABLE(INSPECTOR_SERVER)
struct RemoteFrontendConnected : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RemoteFrontendConnected"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if ENABLE(INSPECTOR_SERVER)
struct RemoteFrontendDisconnected : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RemoteFrontendDisconnected"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

} // namespace WebInspector
} // namespace Messages

#endif // ENABLE(INSPECTOR)

#endif // WebInspectorMessages_h
