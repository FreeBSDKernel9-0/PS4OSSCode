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

#ifndef WebPageMessages_h
#define WebPageMessages_h

#include "Arguments.h"
#include "MessageEncoder.h"
#include "SandboxExtension.h"
#include "SharedMemory.h"
#include "StringReference.h"
#include <WebCore/DictationAlternative.h>
#include <WebCore/Editor.h>
#include <WebCore/KeyboardEvent.h>
#include <WebCore/TextCheckerClient.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace CoreIPC {
    class DataReference;
}

namespace WTF {
    class String;
}

namespace WebCore {
    class Color;
    class IntPoint;
    class DragData;
    class ResourceRequest;
    class FloatRect;
    class FloatPoint;
    class IntRect;
    class IntSize;
}

namespace WebKit {
    class WebContextUserMessageEncoder;
    struct PrintInfo;
    class SessionState;
    struct WebPreferencesStore;
    class WebMouseEvent;
    class WebContextMenuItemData;
    struct EditorState;
    class QtNetworkReplyData;
    class WebWheelEvent;
    class WebKeyboardEvent;
    class WebTouchEvent;
    struct AttributedString;
}

namespace Messages {
namespace WebPage {

static inline CoreIPC::StringReference messageReceiverName()
{
    return CoreIPC::StringReference("WebPage");
}

struct SetActive : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetActive"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetActive(bool active)
        : CoreIPC::Arguments1<bool>(active)
    {
    }
};

struct SetFocused : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetFocused"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetFocused(bool focused)
        : CoreIPC::Arguments1<bool>(focused)
    {
    }
};

struct SetInitialFocus : CoreIPC::Arguments3<bool, bool, const WebKit::WebKeyboardEvent&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetInitialFocus"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<bool, bool, const WebKit::WebKeyboardEvent&> DecodeType;
    SetInitialFocus(bool forward, bool isKeyboardEventValid, const WebKit::WebKeyboardEvent& event)
        : CoreIPC::Arguments3<bool, bool, const WebKit::WebKeyboardEvent&>(forward, isKeyboardEventValid, event)
    {
    }
};

struct SetIsInWindow : CoreIPC::Arguments2<bool, bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetIsInWindow"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<bool, bool> DecodeType;
    SetIsInWindow(bool isInWindow, bool wantsDidUpdateViewInWindowState)
        : CoreIPC::Arguments2<bool, bool>(isInWindow, wantsDidUpdateViewInWindowState)
    {
    }
};

struct SetDrawsBackground : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetDrawsBackground"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetDrawsBackground(bool drawsBackground)
        : CoreIPC::Arguments1<bool>(drawsBackground)
    {
    }
};

struct SetDrawsTransparentBackground : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetDrawsTransparentBackground"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetDrawsTransparentBackground(bool drawsTransparentBackground)
        : CoreIPC::Arguments1<bool>(drawsTransparentBackground)
    {
    }
};

struct SetUnderlayColor : CoreIPC::Arguments1<const WebCore::Color&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetUnderlayColor"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebCore::Color&> DecodeType;
    explicit SetUnderlayColor(const WebCore::Color& color)
        : CoreIPC::Arguments1<const WebCore::Color&>(color)
    {
    }
};

struct ViewWillStartLiveResize : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ViewWillStartLiveResize"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct ViewWillEndLiveResize : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ViewWillEndLiveResize"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct KeyEvent : CoreIPC::Arguments1<const WebKit::WebKeyboardEvent&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("KeyEvent"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebKit::WebKeyboardEvent&> DecodeType;
    explicit KeyEvent(const WebKit::WebKeyboardEvent& event)
        : CoreIPC::Arguments1<const WebKit::WebKeyboardEvent&>(event)
    {
    }
};

struct KeyEventSyncForTesting : CoreIPC::Arguments1<const WebKit::WebKeyboardEvent&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("KeyEventSyncForTesting"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments1<const WebKit::WebKeyboardEvent&> DecodeType;
    explicit KeyEventSyncForTesting(const WebKit::WebKeyboardEvent& event)
        : CoreIPC::Arguments1<const WebKit::WebKeyboardEvent&>(event)
    {
    }
};

#if PLATFORM(MANX)
struct KeyEventManx : CoreIPC::Arguments2<const WebKit::WebKeyboardEvent&, const int&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("KeyEventManx"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WebKit::WebKeyboardEvent&, const int&> DecodeType;
    KeyEventManx(const WebKit::WebKeyboardEvent& event, const int& caretOffset)
        : CoreIPC::Arguments2<const WebKit::WebKeyboardEvent&, const int&>(event, caretOffset)
    {
    }
};
#endif

struct MouseEvent : CoreIPC::Arguments1<const WebKit::WebMouseEvent&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("MouseEvent"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebKit::WebMouseEvent&> DecodeType;
    explicit MouseEvent(const WebKit::WebMouseEvent& event)
        : CoreIPC::Arguments1<const WebKit::WebMouseEvent&>(event)
    {
    }
};

struct MouseEventSyncForTesting : CoreIPC::Arguments1<const WebKit::WebMouseEvent&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("MouseEventSyncForTesting"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments1<const WebKit::WebMouseEvent&> DecodeType;
    explicit MouseEventSyncForTesting(const WebKit::WebMouseEvent& event)
        : CoreIPC::Arguments1<const WebKit::WebMouseEvent&>(event)
    {
    }
};

struct WheelEventSyncForTesting : CoreIPC::Arguments1<const WebKit::WebWheelEvent&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("WheelEventSyncForTesting"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments1<const WebKit::WebWheelEvent&> DecodeType;
    explicit WheelEventSyncForTesting(const WebKit::WebWheelEvent& event)
        : CoreIPC::Arguments1<const WebKit::WebWheelEvent&>(event)
    {
    }
};

#if ENABLE(TOUCH_EVENTS)
struct TouchEvent : CoreIPC::Arguments1<const WebKit::WebTouchEvent&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("TouchEvent"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebKit::WebTouchEvent&> DecodeType;
    explicit TouchEvent(const WebKit::WebTouchEvent& event)
        : CoreIPC::Arguments1<const WebKit::WebTouchEvent&>(event)
    {
    }
};
#endif

#if ENABLE(TOUCH_EVENTS)
struct TouchEventSyncForTesting : CoreIPC::Arguments1<const WebKit::WebTouchEvent&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("TouchEventSyncForTesting"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments1<const WebKit::WebTouchEvent&> DecodeType;
    explicit TouchEventSyncForTesting(const WebKit::WebTouchEvent& event)
        : CoreIPC::Arguments1<const WebKit::WebTouchEvent&>(event)
    {
    }
};
#endif

#if ENABLE(TOUCH_EVENTS) && PLATFORM(QT)
struct HighlightPotentialActivation : CoreIPC::Arguments2<const WebCore::IntPoint&, const WebCore::IntSize&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("HighlightPotentialActivation"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WebCore::IntPoint&, const WebCore::IntSize&> DecodeType;
    HighlightPotentialActivation(const WebCore::IntPoint& point, const WebCore::IntSize& area)
        : CoreIPC::Arguments2<const WebCore::IntPoint&, const WebCore::IntSize&>(point, area)
    {
    }
};
#endif

#if ENABLE(INPUT_TYPE_COLOR)
struct DidEndColorChooser : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidEndColorChooser"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if ENABLE(INPUT_TYPE_COLOR)
struct DidChooseColor : CoreIPC::Arguments1<const WebCore::Color&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidChooseColor"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebCore::Color&> DecodeType;
    explicit DidChooseColor(const WebCore::Color& color)
        : CoreIPC::Arguments1<const WebCore::Color&>(color)
    {
    }
};
#endif

#if ENABLE(CONTEXT_MENUS)
struct ContextMenuHidden : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ContextMenuHidden"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

struct ScrollBy : CoreIPC::Arguments2<uint32_t, uint32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ScrollBy"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint32_t, uint32_t> DecodeType;
    ScrollBy(uint32_t scrollDirection, uint32_t scrollGranularity)
        : CoreIPC::Arguments2<uint32_t, uint32_t>(scrollDirection, scrollGranularity)
    {
    }
};

struct CenterSelectionInVisibleArea : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CenterSelectionInVisibleArea"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct GoBack : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GoBack"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit GoBack(uint64_t backForwardItemID)
        : CoreIPC::Arguments1<uint64_t>(backForwardItemID)
    {
    }
};

struct GoForward : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GoForward"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit GoForward(uint64_t backForwardItemID)
        : CoreIPC::Arguments1<uint64_t>(backForwardItemID)
    {
    }
};

struct GoToBackForwardItem : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GoToBackForwardItem"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit GoToBackForwardItem(uint64_t backForwardItemID)
        : CoreIPC::Arguments1<uint64_t>(backForwardItemID)
    {
    }
};

struct TryRestoreScrollPosition : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("TryRestoreScrollPosition"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct LoadURL : CoreIPC::Arguments3<const WTF::String&, const WebKit::SandboxExtension::Handle&, const WebKit::WebContextUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("LoadURL"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<WTF::String&, WebKit::SandboxExtension::Handle&> DecodeType;
    LoadURL(const WTF::String& url, const WebKit::SandboxExtension::Handle& sandboxExtensionHandle, const WebKit::WebContextUserMessageEncoder& userData)
        : CoreIPC::Arguments3<const WTF::String&, const WebKit::SandboxExtension::Handle&, const WebKit::WebContextUserMessageEncoder&>(url, sandboxExtensionHandle, userData)
    {
    }
};

struct LoadURLRequest : CoreIPC::Arguments3<const WebCore::ResourceRequest&, const WebKit::SandboxExtension::Handle&, const WebKit::WebContextUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("LoadURLRequest"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<WebCore::ResourceRequest&, WebKit::SandboxExtension::Handle&> DecodeType;
    LoadURLRequest(const WebCore::ResourceRequest& request, const WebKit::SandboxExtension::Handle& sandboxExtensionHandle, const WebKit::WebContextUserMessageEncoder& userData)
        : CoreIPC::Arguments3<const WebCore::ResourceRequest&, const WebKit::SandboxExtension::Handle&, const WebKit::WebContextUserMessageEncoder&>(request, sandboxExtensionHandle, userData)
    {
    }
};

struct LoadData : CoreIPC::Arguments5<const CoreIPC::DataReference&, const WTF::String&, const WTF::String&, const WTF::String&, const WebKit::WebContextUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("LoadData"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments4<CoreIPC::DataReference&, WTF::String&, WTF::String&, WTF::String&> DecodeType;
    LoadData(const CoreIPC::DataReference& data, const WTF::String& MIMEType, const WTF::String& encoding, const WTF::String& baseURL, const WebKit::WebContextUserMessageEncoder& userData)
        : CoreIPC::Arguments5<const CoreIPC::DataReference&, const WTF::String&, const WTF::String&, const WTF::String&, const WebKit::WebContextUserMessageEncoder&>(data, MIMEType, encoding, baseURL, userData)
    {
    }
};

struct LoadHTMLString : CoreIPC::Arguments3<const WTF::String&, const WTF::String&, const WebKit::WebContextUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("LoadHTMLString"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<WTF::String&, WTF::String&> DecodeType;
    LoadHTMLString(const WTF::String& htmlString, const WTF::String& baseURL, const WebKit::WebContextUserMessageEncoder& userData)
        : CoreIPC::Arguments3<const WTF::String&, const WTF::String&, const WebKit::WebContextUserMessageEncoder&>(htmlString, baseURL, userData)
    {
    }
};

struct LoadAlternateHTMLString : CoreIPC::Arguments4<const WTF::String&, const WTF::String&, const WTF::String&, const WebKit::WebContextUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("LoadAlternateHTMLString"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<WTF::String&, WTF::String&, WTF::String&> DecodeType;
    LoadAlternateHTMLString(const WTF::String& htmlString, const WTF::String& baseURL, const WTF::String& unreachableURL, const WebKit::WebContextUserMessageEncoder& userData)
        : CoreIPC::Arguments4<const WTF::String&, const WTF::String&, const WTF::String&, const WebKit::WebContextUserMessageEncoder&>(htmlString, baseURL, unreachableURL, userData)
    {
    }
};

struct LoadPlainTextString : CoreIPC::Arguments2<const WTF::String&, const WebKit::WebContextUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("LoadPlainTextString"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<WTF::String&> DecodeType;
    LoadPlainTextString(const WTF::String& string, const WebKit::WebContextUserMessageEncoder& userData)
        : CoreIPC::Arguments2<const WTF::String&, const WebKit::WebContextUserMessageEncoder&>(string, userData)
    {
    }
};

struct LoadWebArchiveData : CoreIPC::Arguments2<const CoreIPC::DataReference&, const WebKit::WebContextUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("LoadWebArchiveData"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<CoreIPC::DataReference&> DecodeType;
    LoadWebArchiveData(const CoreIPC::DataReference& webArchiveData, const WebKit::WebContextUserMessageEncoder& userData)
        : CoreIPC::Arguments2<const CoreIPC::DataReference&, const WebKit::WebContextUserMessageEncoder&>(webArchiveData, userData)
    {
    }
};

struct LinkClicked : CoreIPC::Arguments2<const WTF::String&, const WebKit::WebMouseEvent&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("LinkClicked"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WTF::String&, const WebKit::WebMouseEvent&> DecodeType;
    LinkClicked(const WTF::String& url, const WebKit::WebMouseEvent& event)
        : CoreIPC::Arguments2<const WTF::String&, const WebKit::WebMouseEvent&>(url, event)
    {
    }
};

struct Reload : CoreIPC::Arguments2<bool, const WebKit::SandboxExtension::Handle&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("Reload"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<bool, const WebKit::SandboxExtension::Handle&> DecodeType;
    Reload(bool reloadFromOrigin, const WebKit::SandboxExtension::Handle& sandboxExtensionHandle)
        : CoreIPC::Arguments2<bool, const WebKit::SandboxExtension::Handle&>(reloadFromOrigin, sandboxExtensionHandle)
    {
    }
};

struct StopLoading : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("StopLoading"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

#if PLATFORM(QT)
struct ApplicationSchemeReply : CoreIPC::Arguments1<const WebKit::QtNetworkReplyData&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ApplicationSchemeReply"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebKit::QtNetworkReplyData&> DecodeType;
    explicit ApplicationSchemeReply(const WebKit::QtNetworkReplyData& reply)
        : CoreIPC::Arguments1<const WebKit::QtNetworkReplyData&>(reply)
    {
    }
};
#endif

#if PLATFORM(QT)
struct RegisterApplicationScheme : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RegisterApplicationScheme"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit RegisterApplicationScheme(const WTF::String& scheme)
        : CoreIPC::Arguments1<const WTF::String&>(scheme)
    {
    }
};
#endif

struct StopLoadingFrame : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("StopLoadingFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit StopLoadingFrame(uint64_t frameID)
        : CoreIPC::Arguments1<uint64_t>(frameID)
    {
    }
};

struct RestoreSession : CoreIPC::Arguments1<const WebKit::SessionState&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RestoreSession"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebKit::SessionState&> DecodeType;
    explicit RestoreSession(const WebKit::SessionState& state)
        : CoreIPC::Arguments1<const WebKit::SessionState&>(state)
    {
    }
};

struct RestoreSessionAndNavigateToCurrentItem : CoreIPC::Arguments1<const WebKit::SessionState&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RestoreSessionAndNavigateToCurrentItem"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebKit::SessionState&> DecodeType;
    explicit RestoreSessionAndNavigateToCurrentItem(const WebKit::SessionState& state)
        : CoreIPC::Arguments1<const WebKit::SessionState&>(state)
    {
    }
};

struct DidRemoveBackForwardItem : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidRemoveBackForwardItem"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit DidRemoveBackForwardItem(uint64_t backForwardItemID)
        : CoreIPC::Arguments1<uint64_t>(backForwardItemID)
    {
    }
};

struct SetWillGoToBackForwardItemCallbackEnabled : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetWillGoToBackForwardItemCallbackEnabled"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetWillGoToBackForwardItemCallbackEnabled(bool willGoToBackForwardItemEnabled)
        : CoreIPC::Arguments1<bool>(willGoToBackForwardItemEnabled)
    {
    }
};

struct DidReceivePolicyDecision : CoreIPC::Arguments4<uint64_t, uint64_t, uint32_t, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidReceivePolicyDecision"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments4<uint64_t, uint64_t, uint32_t, uint64_t> DecodeType;
    DidReceivePolicyDecision(uint64_t frameID, uint64_t listenerID, uint32_t policyAction, uint64_t downloadID)
        : CoreIPC::Arguments4<uint64_t, uint64_t, uint32_t, uint64_t>(frameID, listenerID, policyAction, downloadID)
    {
    }
};

struct ClearSelection : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ClearSelection"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

#if PLATFORM(MANX)
struct ClearSelectionWithoutBlur : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ClearSelectionWithoutBlur"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

struct GetContentsAsString : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetContentsAsString"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit GetContentsAsString(uint64_t callbackID)
        : CoreIPC::Arguments1<uint64_t>(callbackID)
    {
    }
};

#if ENABLE(MHTML)
struct GetContentsAsMHTMLData : CoreIPC::Arguments2<uint64_t, bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetContentsAsMHTMLData"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, bool> DecodeType;
    GetContentsAsMHTMLData(uint64_t callbackID, bool useBinaryEncoding)
        : CoreIPC::Arguments2<uint64_t, bool>(callbackID, useBinaryEncoding)
    {
    }
};
#endif

struct GetMainResourceDataOfFrame : CoreIPC::Arguments2<uint64_t, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetMainResourceDataOfFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, uint64_t> DecodeType;
    GetMainResourceDataOfFrame(uint64_t frameID, uint64_t callbackID)
        : CoreIPC::Arguments2<uint64_t, uint64_t>(frameID, callbackID)
    {
    }
};

struct GetResourceDataFromFrame : CoreIPC::Arguments3<uint64_t, const WTF::String&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetResourceDataFromFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<uint64_t, const WTF::String&, uint64_t> DecodeType;
    GetResourceDataFromFrame(uint64_t frameID, const WTF::String& resourceURL, uint64_t callbackID)
        : CoreIPC::Arguments3<uint64_t, const WTF::String&, uint64_t>(frameID, resourceURL, callbackID)
    {
    }
};

struct GetRenderTreeExternalRepresentation : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetRenderTreeExternalRepresentation"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit GetRenderTreeExternalRepresentation(uint64_t callbackID)
        : CoreIPC::Arguments1<uint64_t>(callbackID)
    {
    }
};

struct GetSelectionOrContentsAsString : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetSelectionOrContentsAsString"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit GetSelectionOrContentsAsString(uint64_t callbackID)
        : CoreIPC::Arguments1<uint64_t>(callbackID)
    {
    }
};

struct GetSelectionAsWebArchiveData : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetSelectionAsWebArchiveData"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit GetSelectionAsWebArchiveData(uint64_t callbackID)
        : CoreIPC::Arguments1<uint64_t>(callbackID)
    {
    }
};

struct GetSourceForFrame : CoreIPC::Arguments2<uint64_t, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetSourceForFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, uint64_t> DecodeType;
    GetSourceForFrame(uint64_t frameID, uint64_t callbackID)
        : CoreIPC::Arguments2<uint64_t, uint64_t>(frameID, callbackID)
    {
    }
};

struct GetWebArchiveOfFrame : CoreIPC::Arguments2<uint64_t, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetWebArchiveOfFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, uint64_t> DecodeType;
    GetWebArchiveOfFrame(uint64_t frameID, uint64_t callbackID)
        : CoreIPC::Arguments2<uint64_t, uint64_t>(frameID, callbackID)
    {
    }
};

struct RunJavaScriptInMainFrame : CoreIPC::Arguments2<const WTF::String&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RunJavaScriptInMainFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WTF::String&, uint64_t> DecodeType;
    RunJavaScriptInMainFrame(const WTF::String& script, uint64_t callbackID)
        : CoreIPC::Arguments2<const WTF::String&, uint64_t>(script, callbackID)
    {
    }
};

#if PLATFORM(MANX)
struct RunJavaScriptInMainFrameWithStringCallback : CoreIPC::Arguments2<const WTF::String&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RunJavaScriptInMainFrameWithStringCallback"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WTF::String&, uint64_t> DecodeType;
    RunJavaScriptInMainFrameWithStringCallback(const WTF::String& script, uint64_t callbackID)
        : CoreIPC::Arguments2<const WTF::String&, uint64_t>(script, callbackID)
    {
    }
};
#endif

struct ForceRepaint : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ForceRepaint"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit ForceRepaint(uint64_t callbackID)
        : CoreIPC::Arguments1<uint64_t>(callbackID)
    {
    }
};

#if PLATFORM(MAC)
struct PerformDictionaryLookupAtLocation : CoreIPC::Arguments1<const WebCore::FloatPoint&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("PerformDictionaryLookupAtLocation"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebCore::FloatPoint&> DecodeType;
    explicit PerformDictionaryLookupAtLocation(const WebCore::FloatPoint& point)
        : CoreIPC::Arguments1<const WebCore::FloatPoint&>(point)
    {
    }
};
#endif

struct PreferencesDidChange : CoreIPC::Arguments1<const WebKit::WebPreferencesStore&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("PreferencesDidChange"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebKit::WebPreferencesStore&> DecodeType;
    explicit PreferencesDidChange(const WebKit::WebPreferencesStore& store)
        : CoreIPC::Arguments1<const WebKit::WebPreferencesStore&>(store)
    {
    }
};

struct SetUserAgent : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetUserAgent"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit SetUserAgent(const WTF::String& userAgent)
        : CoreIPC::Arguments1<const WTF::String&>(userAgent)
    {
    }
};

struct SetCustomTextEncodingName : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetCustomTextEncodingName"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit SetCustomTextEncodingName(const WTF::String& encodingName)
        : CoreIPC::Arguments1<const WTF::String&>(encodingName)
    {
    }
};

struct SuspendActiveDOMObjectsAndAnimations : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SuspendActiveDOMObjectsAndAnimations"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct ResumeActiveDOMObjectsAndAnimations : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ResumeActiveDOMObjectsAndAnimations"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct Close : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("Close"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct TryClose : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("TryClose"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct ValidateCommand : CoreIPC::Arguments2<const WTF::String&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ValidateCommand"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WTF::String&, uint64_t> DecodeType;
    ValidateCommand(const WTF::String& name, uint64_t callbackID)
        : CoreIPC::Arguments2<const WTF::String&, uint64_t>(name, callbackID)
    {
    }
};

struct ExecuteEditCommand : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ExecuteEditCommand"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit ExecuteEditCommand(const WTF::String& name)
        : CoreIPC::Arguments1<const WTF::String&>(name)
    {
    }
};

struct DidRemoveEditCommand : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidRemoveEditCommand"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit DidRemoveEditCommand(uint64_t commandID)
        : CoreIPC::Arguments1<uint64_t>(commandID)
    {
    }
};

struct ReapplyEditCommand : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ReapplyEditCommand"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit ReapplyEditCommand(uint64_t commandID)
        : CoreIPC::Arguments1<uint64_t>(commandID)
    {
    }
};

struct UnapplyEditCommand : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("UnapplyEditCommand"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit UnapplyEditCommand(uint64_t commandID)
        : CoreIPC::Arguments1<uint64_t>(commandID)
    {
    }
};

struct SetPageAndTextZoomFactors : CoreIPC::Arguments2<double, double> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetPageAndTextZoomFactors"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<double, double> DecodeType;
    SetPageAndTextZoomFactors(double pageZoomFactor, double textZoomFactor)
        : CoreIPC::Arguments2<double, double>(pageZoomFactor, textZoomFactor)
    {
    }
};

struct SetPageZoomFactor : CoreIPC::Arguments1<double> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetPageZoomFactor"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<double> DecodeType;
    explicit SetPageZoomFactor(double zoomFactor)
        : CoreIPC::Arguments1<double>(zoomFactor)
    {
    }
};

struct SetTextZoomFactor : CoreIPC::Arguments1<double> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetTextZoomFactor"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<double> DecodeType;
    explicit SetTextZoomFactor(double zoomFactor)
        : CoreIPC::Arguments1<double>(zoomFactor)
    {
    }
};

struct WindowScreenDidChange : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("WindowScreenDidChange"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit WindowScreenDidChange(uint64_t displayID)
        : CoreIPC::Arguments1<uint64_t>(displayID)
    {
    }
};

struct ScalePage : CoreIPC::Arguments2<double, const WebCore::IntPoint&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ScalePage"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<double, const WebCore::IntPoint&> DecodeType;
    ScalePage(double scale, const WebCore::IntPoint& origin)
        : CoreIPC::Arguments2<double, const WebCore::IntPoint&>(scale, origin)
    {
    }
};

struct SetUseFixedLayout : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetUseFixedLayout"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetUseFixedLayout(bool fixed)
        : CoreIPC::Arguments1<bool>(fixed)
    {
    }
};

struct SetFixedLayoutSize : CoreIPC::Arguments1<const WebCore::IntSize&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetFixedLayoutSize"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebCore::IntSize&> DecodeType;
    explicit SetFixedLayoutSize(const WebCore::IntSize& size)
        : CoreIPC::Arguments1<const WebCore::IntSize&>(size)
    {
    }
};

struct ListenForLayoutMilestones : CoreIPC::Arguments1<uint32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ListenForLayoutMilestones"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint32_t> DecodeType;
    explicit ListenForLayoutMilestones(uint32_t milestones)
        : CoreIPC::Arguments1<uint32_t>(milestones)
    {
    }
};

struct SetSuppressScrollbarAnimations : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetSuppressScrollbarAnimations"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetSuppressScrollbarAnimations(bool suppressAnimations)
        : CoreIPC::Arguments1<bool>(suppressAnimations)
    {
    }
};

struct SetRubberBandsAtBottom : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetRubberBandsAtBottom"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetRubberBandsAtBottom(bool rubberBandsAtBottom)
        : CoreIPC::Arguments1<bool>(rubberBandsAtBottom)
    {
    }
};

struct SetRubberBandsAtTop : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetRubberBandsAtTop"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetRubberBandsAtTop(bool rubberBandsAtTop)
        : CoreIPC::Arguments1<bool>(rubberBandsAtTop)
    {
    }
};

struct SetPaginationMode : CoreIPC::Arguments1<uint32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetPaginationMode"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint32_t> DecodeType;
    explicit SetPaginationMode(uint32_t mode)
        : CoreIPC::Arguments1<uint32_t>(mode)
    {
    }
};

struct SetPaginationBehavesLikeColumns : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetPaginationBehavesLikeColumns"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetPaginationBehavesLikeColumns(bool behavesLikeColumns)
        : CoreIPC::Arguments1<bool>(behavesLikeColumns)
    {
    }
};

struct SetPageLength : CoreIPC::Arguments1<double> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetPageLength"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<double> DecodeType;
    explicit SetPageLength(double pageLength)
        : CoreIPC::Arguments1<double>(pageLength)
    {
    }
};

struct SetGapBetweenPages : CoreIPC::Arguments1<double> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetGapBetweenPages"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<double> DecodeType;
    explicit SetGapBetweenPages(double gap)
        : CoreIPC::Arguments1<double>(gap)
    {
    }
};

struct PostInjectedBundleMessage : CoreIPC::Arguments2<const WTF::String&, const WebKit::WebContextUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("PostInjectedBundleMessage"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<WTF::String&> DecodeType;
    PostInjectedBundleMessage(const WTF::String& messageName, const WebKit::WebContextUserMessageEncoder& messageBody)
        : CoreIPC::Arguments2<const WTF::String&, const WebKit::WebContextUserMessageEncoder&>(messageName, messageBody)
    {
    }
};

struct FindString : CoreIPC::Arguments3<const WTF::String&, uint32_t, const unsigned&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("FindString"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<const WTF::String&, uint32_t, const unsigned&> DecodeType;
    FindString(const WTF::String& string, uint32_t findOptions, const unsigned& maxMatchCount)
        : CoreIPC::Arguments3<const WTF::String&, uint32_t, const unsigned&>(string, findOptions, maxMatchCount)
    {
    }
};

struct FindStringMatches : CoreIPC::Arguments3<const WTF::String&, uint32_t, const unsigned&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("FindStringMatches"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<const WTF::String&, uint32_t, const unsigned&> DecodeType;
    FindStringMatches(const WTF::String& string, uint32_t findOptions, const unsigned& maxMatchCount)
        : CoreIPC::Arguments3<const WTF::String&, uint32_t, const unsigned&>(string, findOptions, maxMatchCount)
    {
    }
};

struct GetImageForFindMatch : CoreIPC::Arguments1<uint32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetImageForFindMatch"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint32_t> DecodeType;
    explicit GetImageForFindMatch(uint32_t matchIndex)
        : CoreIPC::Arguments1<uint32_t>(matchIndex)
    {
    }
};

struct SelectFindMatch : CoreIPC::Arguments1<uint32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SelectFindMatch"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint32_t> DecodeType;
    explicit SelectFindMatch(uint32_t matchIndex)
        : CoreIPC::Arguments1<uint32_t>(matchIndex)
    {
    }
};

struct HideFindUI : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("HideFindUI"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct CountStringMatches : CoreIPC::Arguments3<const WTF::String&, uint32_t, const unsigned&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CountStringMatches"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<const WTF::String&, uint32_t, const unsigned&> DecodeType;
    CountStringMatches(const WTF::String& string, uint32_t findOptions, const unsigned& maxMatchCount)
        : CoreIPC::Arguments3<const WTF::String&, uint32_t, const unsigned&>(string, findOptions, maxMatchCount)
    {
    }
};

#if (PLATFORM(QT) || PLATFORM(GTK)) && ENABLE(DRAG_SUPPORT)
struct PerformDragControllerAction : CoreIPC::Arguments2<uint64_t, const WebCore::DragData&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("PerformDragControllerAction"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, const WebCore::DragData&> DecodeType;
    PerformDragControllerAction(uint64_t action, const WebCore::DragData& dragData)
        : CoreIPC::Arguments2<uint64_t, const WebCore::DragData&>(action, dragData)
    {
    }
};
#endif

#if !PLATFORM(QT) && !PLATFORM(GTK) && ENABLE(DRAG_SUPPORT)
struct PerformDragControllerAction : CoreIPC::Arguments8<uint64_t, const WebCore::IntPoint&, const WebCore::IntPoint&, uint64_t, const WTF::String&, uint32_t, const WebKit::SandboxExtension::Handle&, const WebKit::SandboxExtension::HandleArray&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("PerformDragControllerAction"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments8<uint64_t, const WebCore::IntPoint&, const WebCore::IntPoint&, uint64_t, const WTF::String&, uint32_t, const WebKit::SandboxExtension::Handle&, const WebKit::SandboxExtension::HandleArray&> DecodeType;
    PerformDragControllerAction(uint64_t action, const WebCore::IntPoint& clientPosition, const WebCore::IntPoint& globalPosition, uint64_t draggingSourceOperationMask, const WTF::String& dragStorageName, uint32_t flags, const WebKit::SandboxExtension::Handle& sandboxExtensionHandle, const WebKit::SandboxExtension::HandleArray& sandboxExtensionsForUpload)
        : CoreIPC::Arguments8<uint64_t, const WebCore::IntPoint&, const WebCore::IntPoint&, uint64_t, const WTF::String&, uint32_t, const WebKit::SandboxExtension::Handle&, const WebKit::SandboxExtension::HandleArray&>(action, clientPosition, globalPosition, draggingSourceOperationMask, dragStorageName, flags, sandboxExtensionHandle, sandboxExtensionsForUpload)
    {
    }
};
#endif

#if ENABLE(DRAG_SUPPORT)
struct DragEnded : CoreIPC::Arguments3<const WebCore::IntPoint&, const WebCore::IntPoint&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DragEnded"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<const WebCore::IntPoint&, const WebCore::IntPoint&, uint64_t> DecodeType;
    DragEnded(const WebCore::IntPoint& clientPosition, const WebCore::IntPoint& globalPosition, uint64_t operation)
        : CoreIPC::Arguments3<const WebCore::IntPoint&, const WebCore::IntPoint&, uint64_t>(clientPosition, globalPosition, operation)
    {
    }
};
#endif

struct DidChangeSelectedIndexForActivePopupMenu : CoreIPC::Arguments1<int32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidChangeSelectedIndexForActivePopupMenu"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<int32_t> DecodeType;
    explicit DidChangeSelectedIndexForActivePopupMenu(int32_t newIndex)
        : CoreIPC::Arguments1<int32_t>(newIndex)
    {
    }
};

struct SetTextForActivePopupMenu : CoreIPC::Arguments1<int32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetTextForActivePopupMenu"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<int32_t> DecodeType;
    explicit SetTextForActivePopupMenu(int32_t index)
        : CoreIPC::Arguments1<int32_t>(index)
    {
    }
};

#if PLATFORM(GTK)
struct FailedToShowPopupMenu : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("FailedToShowPopupMenu"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if PLATFORM(QT)
struct HidePopupMenu : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("HidePopupMenu"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if PLATFORM(QT)
struct SelectedIndex : CoreIPC::Arguments1<int32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SelectedIndex"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<int32_t> DecodeType;
    explicit SelectedIndex(int32_t newIndex)
        : CoreIPC::Arguments1<int32_t>(newIndex)
    {
    }
};
#endif

#if ENABLE(CONTEXT_MENUS)
struct DidSelectItemFromActiveContextMenu : CoreIPC::Arguments1<const WebKit::WebContextMenuItemData&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidSelectItemFromActiveContextMenu"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebKit::WebContextMenuItemData&> DecodeType;
    explicit DidSelectItemFromActiveContextMenu(const WebKit::WebContextMenuItemData& menuItem)
        : CoreIPC::Arguments1<const WebKit::WebContextMenuItemData&>(menuItem)
    {
    }
};
#endif

struct DidChooseFilesForOpenPanel : CoreIPC::Arguments1<const Vector<WTF::String>&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidChooseFilesForOpenPanel"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const Vector<WTF::String>&> DecodeType;
    explicit DidChooseFilesForOpenPanel(const Vector<WTF::String>& fileURLs)
        : CoreIPC::Arguments1<const Vector<WTF::String>&>(fileURLs)
    {
    }
};

struct DidCancelForOpenPanel : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidCancelForOpenPanel"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

#if ENABLE(WEB_PROCESS_SANDBOX)
struct ExtendSandboxForFileFromOpenPanel : CoreIPC::Arguments1<const WebKit::SandboxExtension::Handle&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ExtendSandboxForFileFromOpenPanel"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebKit::SandboxExtension::Handle&> DecodeType;
    explicit ExtendSandboxForFileFromOpenPanel(const WebKit::SandboxExtension::Handle& sandboxExtensionHandle)
        : CoreIPC::Arguments1<const WebKit::SandboxExtension::Handle&>(sandboxExtensionHandle)
    {
    }
};
#endif

struct AdvanceToNextMisspelling : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("AdvanceToNextMisspelling"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit AdvanceToNextMisspelling(bool startBeforeSelection)
        : CoreIPC::Arguments1<bool>(startBeforeSelection)
    {
    }
};

struct ChangeSpellingToWord : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ChangeSpellingToWord"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit ChangeSpellingToWord(const WTF::String& word)
        : CoreIPC::Arguments1<const WTF::String&>(word)
    {
    }
};

struct DidFinishCheckingText : CoreIPC::Arguments2<uint64_t, const WTF::Vector<WebCore::TextCheckingResult>&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidFinishCheckingText"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, const WTF::Vector<WebCore::TextCheckingResult>&> DecodeType;
    DidFinishCheckingText(uint64_t requestID, const WTF::Vector<WebCore::TextCheckingResult>& result)
        : CoreIPC::Arguments2<uint64_t, const WTF::Vector<WebCore::TextCheckingResult>&>(requestID, result)
    {
    }
};

struct DidCancelCheckingText : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidCancelCheckingText"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit DidCancelCheckingText(uint64_t requestID)
        : CoreIPC::Arguments1<uint64_t>(requestID)
    {
    }
};

#if USE(APPKIT)
struct UppercaseWord : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("UppercaseWord"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if USE(APPKIT)
struct LowercaseWord : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("LowercaseWord"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if USE(APPKIT)
struct CapitalizeWord : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CapitalizeWord"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if PLATFORM(MAC)
struct SetSmartInsertDeleteEnabled : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetSmartInsertDeleteEnabled"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetSmartInsertDeleteEnabled(bool isSmartInsertDeleteEnabled)
        : CoreIPC::Arguments1<bool>(isSmartInsertDeleteEnabled)
    {
    }
};
#endif

#if ENABLE(GEOLOCATION)
struct DidReceiveGeolocationPermissionDecision : CoreIPC::Arguments2<uint64_t, bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidReceiveGeolocationPermissionDecision"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, bool> DecodeType;
    DidReceiveGeolocationPermissionDecision(uint64_t geolocationID, bool allowed)
        : CoreIPC::Arguments2<uint64_t, bool>(geolocationID, allowed)
    {
    }
};
#endif

struct DidReceiveNotificationPermissionDecision : CoreIPC::Arguments2<uint64_t, bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidReceiveNotificationPermissionDecision"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, bool> DecodeType;
    DidReceiveNotificationPermissionDecision(uint64_t notificationID, bool allowed)
        : CoreIPC::Arguments2<uint64_t, bool>(notificationID, allowed)
    {
    }
};

struct SetWindowResizerSize : CoreIPC::Arguments1<const WebCore::IntSize&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetWindowResizerSize"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebCore::IntSize&> DecodeType;
    explicit SetWindowResizerSize(const WebCore::IntSize& intersectsView)
        : CoreIPC::Arguments1<const WebCore::IntSize&>(intersectsView)
    {
    }
};

struct BeginPrinting : CoreIPC::Arguments2<uint64_t, const WebKit::PrintInfo&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("BeginPrinting"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, const WebKit::PrintInfo&> DecodeType;
    BeginPrinting(uint64_t frameID, const WebKit::PrintInfo& printInfo)
        : CoreIPC::Arguments2<uint64_t, const WebKit::PrintInfo&>(frameID, printInfo)
    {
    }
};

struct EndPrinting : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("EndPrinting"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct ComputePagesForPrinting : CoreIPC::Arguments3<uint64_t, const WebKit::PrintInfo&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ComputePagesForPrinting"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<uint64_t, const WebKit::PrintInfo&, uint64_t> DecodeType;
    ComputePagesForPrinting(uint64_t frameID, const WebKit::PrintInfo& printInfo, uint64_t callbackID)
        : CoreIPC::Arguments3<uint64_t, const WebKit::PrintInfo&, uint64_t>(frameID, printInfo, callbackID)
    {
    }
};

#if PLATFORM(MAC)
struct DrawRectToImage : CoreIPC::Arguments5<uint64_t, const WebKit::PrintInfo&, const WebCore::IntRect&, const WebCore::IntSize&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DrawRectToImage"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments5<uint64_t, const WebKit::PrintInfo&, const WebCore::IntRect&, const WebCore::IntSize&, uint64_t> DecodeType;
    DrawRectToImage(uint64_t frameID, const WebKit::PrintInfo& printInfo, const WebCore::IntRect& rect, const WebCore::IntSize& imageSize, uint64_t callbackID)
        : CoreIPC::Arguments5<uint64_t, const WebKit::PrintInfo&, const WebCore::IntRect&, const WebCore::IntSize&, uint64_t>(frameID, printInfo, rect, imageSize, callbackID)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct DrawPagesToPDF : CoreIPC::Arguments5<uint64_t, const WebKit::PrintInfo&, uint32_t, uint32_t, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DrawPagesToPDF"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments5<uint64_t, const WebKit::PrintInfo&, uint32_t, uint32_t, uint64_t> DecodeType;
    DrawPagesToPDF(uint64_t frameID, const WebKit::PrintInfo& printInfo, uint32_t first, uint32_t count, uint64_t callbackID)
        : CoreIPC::Arguments5<uint64_t, const WebKit::PrintInfo&, uint32_t, uint32_t, uint64_t>(frameID, printInfo, first, count, callbackID)
    {
    }
};
#endif

#if PLATFORM(GTK)
struct DrawPagesForPrinting : CoreIPC::Arguments3<uint64_t, const WebKit::PrintInfo&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DrawPagesForPrinting"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<uint64_t, const WebKit::PrintInfo&, uint64_t> DecodeType;
    DrawPagesForPrinting(uint64_t frameID, const WebKit::PrintInfo& printInfo, uint64_t callbackID)
        : CoreIPC::Arguments3<uint64_t, const WebKit::PrintInfo&, uint64_t>(frameID, printInfo, callbackID)
    {
    }
};
#endif

struct SetMediaVolume : CoreIPC::Arguments1<float> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetMediaVolume"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<float> DecodeType;
    explicit SetMediaVolume(float volume)
        : CoreIPC::Arguments1<float>(volume)
    {
    }
};

struct SetMayStartMediaWhenInWindow : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetMayStartMediaWhenInWindow"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetMayStartMediaWhenInWindow(bool mayStartMedia)
        : CoreIPC::Arguments1<bool>(mayStartMedia)
    {
    }
};

struct SetMemoryCacheMessagesEnabled : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetMemoryCacheMessagesEnabled"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetMemoryCacheMessagesEnabled(bool memoryCacheMessagesEnabled)
        : CoreIPC::Arguments1<bool>(memoryCacheMessagesEnabled)
    {
    }
};

struct Dummy : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("Dummy"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments0 DecodeType;
};

struct SetCanRunBeforeUnloadConfirmPanel : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetCanRunBeforeUnloadConfirmPanel"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetCanRunBeforeUnloadConfirmPanel(bool canRunBeforeUnloadConfirmPanel)
        : CoreIPC::Arguments1<bool>(canRunBeforeUnloadConfirmPanel)
    {
    }
};

struct SetCanRunModal : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetCanRunModal"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetCanRunModal(bool canRunModal)
        : CoreIPC::Arguments1<bool>(canRunModal)
    {
    }
};

#if PLATFORM(EFL)
struct SetThemePath : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetThemePath"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit SetThemePath(const WTF::String& themePath)
        : CoreIPC::Arguments1<const WTF::String&>(themePath)
    {
    }
};
#endif

#if USE(TILED_BACKING_STORE)
struct CommitPageTransitionViewport : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CommitPageTransitionViewport"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if PLATFORM(MANX)
struct SetComposition : CoreIPC::Arguments6<const WTF::String&, const WTF::Vector<WebCore::CompositionUnderline>&, uint64_t, uint64_t, uint64_t, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetComposition"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments6<const WTF::String&, const WTF::Vector<WebCore::CompositionUnderline>&, uint64_t, uint64_t, uint64_t, uint64_t> DecodeType;
    SetComposition(const WTF::String& text, const WTF::Vector<WebCore::CompositionUnderline>& underlines, uint64_t selectionStart, uint64_t selectionEnd, uint64_t replacementRangeStart, uint64_t replacementRangeEnd)
        : CoreIPC::Arguments6<const WTF::String&, const WTF::Vector<WebCore::CompositionUnderline>&, uint64_t, uint64_t, uint64_t, uint64_t>(text, underlines, selectionStart, selectionEnd, replacementRangeStart, replacementRangeEnd)
    {
    }
};
#endif

#if PLATFORM(MANX)
struct ConfirmComposition : CoreIPC::Arguments3<const WTF::String&, int64_t, int64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ConfirmComposition"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<const WTF::String&, int64_t, int64_t> DecodeType;
    ConfirmComposition(const WTF::String& text, int64_t selectionStart, int64_t selectionLength)
        : CoreIPC::Arguments3<const WTF::String&, int64_t, int64_t>(text, selectionStart, selectionLength)
    {
    }
};
#endif

#if PLATFORM(MANX)
struct CancelComposition : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CancelComposition"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if PLATFORM(MANX)
struct ExitComposition : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ExitComposition"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if PLATFORM(MANX)
struct SetValueToFocusedNode : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetValueToFocusedNode"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit SetValueToFocusedNode(const WTF::String& value)
        : CoreIPC::Arguments1<const WTF::String&>(value)
    {
    }
};
#endif

#if PLATFORM(MANX)
struct SetCaretVisible : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetCaretVisible"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetCaretVisible(bool visible)
        : CoreIPC::Arguments1<bool>(visible)
    {
    }
};
#endif

#if PLATFORM(QT) || PLATFORM(GTK)
struct SetComposition : CoreIPC::Arguments6<const WTF::String&, const WTF::Vector<WebCore::CompositionUnderline>&, uint64_t, uint64_t, uint64_t, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetComposition"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments6<const WTF::String&, const WTF::Vector<WebCore::CompositionUnderline>&, uint64_t, uint64_t, uint64_t, uint64_t> DecodeType;
    SetComposition(const WTF::String& text, const WTF::Vector<WebCore::CompositionUnderline>& underlines, uint64_t selectionStart, uint64_t selectionEnd, uint64_t replacementRangeStart, uint64_t replacementRangeEnd)
        : CoreIPC::Arguments6<const WTF::String&, const WTF::Vector<WebCore::CompositionUnderline>&, uint64_t, uint64_t, uint64_t, uint64_t>(text, underlines, selectionStart, selectionEnd, replacementRangeStart, replacementRangeEnd)
    {
    }
};
#endif

#if PLATFORM(QT) || PLATFORM(GTK)
struct ConfirmComposition : CoreIPC::Arguments3<const WTF::String&, int64_t, int64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ConfirmComposition"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<const WTF::String&, int64_t, int64_t> DecodeType;
    ConfirmComposition(const WTF::String& text, int64_t selectionStart, int64_t selectionLength)
        : CoreIPC::Arguments3<const WTF::String&, int64_t, int64_t>(text, selectionStart, selectionLength)
    {
    }
};
#endif

#if PLATFORM(QT) || PLATFORM(GTK)
struct CancelComposition : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CancelComposition"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if PLATFORM(MAC)
struct SendComplexTextInputToPlugin : CoreIPC::Arguments2<uint64_t, const String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SendComplexTextInputToPlugin"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, const String&> DecodeType;
    SendComplexTextInputToPlugin(uint64_t pluginComplexTextInputIdentifier, const String& textInput)
        : CoreIPC::Arguments2<uint64_t, const String&>(pluginComplexTextInputIdentifier, textInput)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct SetWindowIsVisible : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetWindowIsVisible"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetWindowIsVisible(bool windowIsVisible)
        : CoreIPC::Arguments1<bool>(windowIsVisible)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct WindowAndViewFramesChanged : CoreIPC::Arguments4<const WebCore::FloatRect&, const WebCore::FloatRect&, const WebCore::FloatRect&, const WebCore::FloatPoint&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("WindowAndViewFramesChanged"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments4<const WebCore::FloatRect&, const WebCore::FloatRect&, const WebCore::FloatRect&, const WebCore::FloatPoint&> DecodeType;
    WindowAndViewFramesChanged(const WebCore::FloatRect& windowFrameInScreenCoordinates, const WebCore::FloatRect& windowFrameInUnflippedScreenCoordinates, const WebCore::FloatRect& viewFrameInWindowCoordinates, const WebCore::FloatPoint& accessibilityViewCoordinates)
        : CoreIPC::Arguments4<const WebCore::FloatRect&, const WebCore::FloatRect&, const WebCore::FloatRect&, const WebCore::FloatPoint&>(windowFrameInScreenCoordinates, windowFrameInUnflippedScreenCoordinates, viewFrameInWindowCoordinates, accessibilityViewCoordinates)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct ViewExposedRectChanged : CoreIPC::Arguments2<const WebCore::FloatRect&, bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ViewExposedRectChanged"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WebCore::FloatRect&, bool> DecodeType;
    ViewExposedRectChanged(const WebCore::FloatRect& exposedRect, bool clipsToExposedRect)
        : CoreIPC::Arguments2<const WebCore::FloatRect&, bool>(exposedRect, clipsToExposedRect)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct SetMainFrameIsScrollable : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetMainFrameIsScrollable"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetMainFrameIsScrollable(bool isScrollable)
        : CoreIPC::Arguments1<bool>(isScrollable)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct RegisterUIProcessAccessibilityTokens : CoreIPC::Arguments2<const CoreIPC::DataReference&, const CoreIPC::DataReference&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RegisterUIProcessAccessibilityTokens"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const CoreIPC::DataReference&, const CoreIPC::DataReference&> DecodeType;
    RegisterUIProcessAccessibilityTokens(const CoreIPC::DataReference& elemenToken, const CoreIPC::DataReference& windowToken)
        : CoreIPC::Arguments2<const CoreIPC::DataReference&, const CoreIPC::DataReference&>(elemenToken, windowToken)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct GetStringSelectionForPasteboard : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetStringSelectionForPasteboard"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<WTF::String&> Reply;
    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if PLATFORM(MAC)
struct GetDataSelectionForPasteboard : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetDataSelectionForPasteboard"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments2<WebKit::SharedMemory::Handle&, uint64_t&> Reply;
    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit GetDataSelectionForPasteboard(const WTF::String& pasteboardType)
        : CoreIPC::Arguments1<const WTF::String&>(pasteboardType)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct ReadSelectionFromPasteboard : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ReadSelectionFromPasteboard"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit ReadSelectionFromPasteboard(const WTF::String& pasteboardName)
        : CoreIPC::Arguments1<const WTF::String&>(pasteboardName)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct SetComposition : CoreIPC::Arguments6<const WTF::String&, const WTF::Vector<WebCore::CompositionUnderline>&, uint64_t, uint64_t, uint64_t, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetComposition"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<WebKit::EditorState&> Reply;
    typedef CoreIPC::Arguments6<const WTF::String&, const WTF::Vector<WebCore::CompositionUnderline>&, uint64_t, uint64_t, uint64_t, uint64_t> DecodeType;
    SetComposition(const WTF::String& text, const WTF::Vector<WebCore::CompositionUnderline>& underlines, uint64_t selectionStart, uint64_t selectionEnd, uint64_t replacementRangeStart, uint64_t replacementRangeEnd)
        : CoreIPC::Arguments6<const WTF::String&, const WTF::Vector<WebCore::CompositionUnderline>&, uint64_t, uint64_t, uint64_t, uint64_t>(text, underlines, selectionStart, selectionEnd, replacementRangeStart, replacementRangeEnd)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct ConfirmComposition : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ConfirmComposition"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<WebKit::EditorState&> Reply;
    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if PLATFORM(MAC)
struct CancelComposition : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CancelComposition"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<WebKit::EditorState&> Reply;
    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if PLATFORM(MAC)
struct InsertText : CoreIPC::Arguments3<const WTF::String&, uint64_t, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("InsertText"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments2<bool&, WebKit::EditorState&> Reply;
    typedef CoreIPC::Arguments3<const WTF::String&, uint64_t, uint64_t> DecodeType;
    InsertText(const WTF::String& text, uint64_t replacementRangeStart, uint64_t replacementRangeEnd)
        : CoreIPC::Arguments3<const WTF::String&, uint64_t, uint64_t>(text, replacementRangeStart, replacementRangeEnd)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct GetMarkedRange : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetMarkedRange"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments2<uint64_t&, uint64_t&> Reply;
    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if PLATFORM(MAC)
struct GetSelectedRange : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetSelectedRange"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments2<uint64_t&, uint64_t&> Reply;
    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if PLATFORM(MAC)
struct GetAttributedSubstringFromRange : CoreIPC::Arguments2<uint64_t, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetAttributedSubstringFromRange"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<WebKit::AttributedString&> Reply;
    typedef CoreIPC::Arguments2<uint64_t, uint64_t> DecodeType;
    GetAttributedSubstringFromRange(uint64_t location, uint64_t length)
        : CoreIPC::Arguments2<uint64_t, uint64_t>(location, length)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct CharacterIndexForPoint : CoreIPC::Arguments1<const WebCore::IntPoint&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CharacterIndexForPoint"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<uint64_t&> Reply;
    typedef CoreIPC::Arguments1<const WebCore::IntPoint&> DecodeType;
    explicit CharacterIndexForPoint(const WebCore::IntPoint& point)
        : CoreIPC::Arguments1<const WebCore::IntPoint&>(point)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct FirstRectForCharacterRange : CoreIPC::Arguments2<uint64_t, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("FirstRectForCharacterRange"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<WebCore::IntRect&> Reply;
    typedef CoreIPC::Arguments2<uint64_t, uint64_t> DecodeType;
    FirstRectForCharacterRange(uint64_t location, uint64_t length)
        : CoreIPC::Arguments2<uint64_t, uint64_t>(location, length)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct ExecuteKeypressCommands : CoreIPC::Arguments1<const Vector<WebCore::KeypressCommand>&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ExecuteKeypressCommands"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments2<bool&, WebKit::EditorState&> Reply;
    typedef CoreIPC::Arguments1<const Vector<WebCore::KeypressCommand>&> DecodeType;
    explicit ExecuteKeypressCommands(const Vector<WebCore::KeypressCommand>& savedCommands)
        : CoreIPC::Arguments1<const Vector<WebCore::KeypressCommand>&>(savedCommands)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct ShouldDelayWindowOrderingEvent : CoreIPC::Arguments1<const WebKit::WebMouseEvent&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ShouldDelayWindowOrderingEvent"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments1<const WebKit::WebMouseEvent&> DecodeType;
    explicit ShouldDelayWindowOrderingEvent(const WebKit::WebMouseEvent& event)
        : CoreIPC::Arguments1<const WebKit::WebMouseEvent&>(event)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct AcceptsFirstMouse : CoreIPC::Arguments2<const int&, const WebKit::WebMouseEvent&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("AcceptsFirstMouse"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments2<const int&, const WebKit::WebMouseEvent&> DecodeType;
    AcceptsFirstMouse(const int& eventNumber, const WebKit::WebMouseEvent& event)
        : CoreIPC::Arguments2<const int&, const WebKit::WebMouseEvent&>(eventNumber, event)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct InsertDictatedText : CoreIPC::Arguments4<const WTF::String&, uint64_t, uint64_t, const WTF::Vector<WebCore::DictationAlternative>&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("InsertDictatedText"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments2<bool&, WebKit::EditorState&> Reply;
    typedef CoreIPC::Arguments4<const WTF::String&, uint64_t, uint64_t, const WTF::Vector<WebCore::DictationAlternative>&> DecodeType;
    InsertDictatedText(const WTF::String& text, uint64_t replacementRangeStart, uint64_t replacementRangeEnd, const WTF::Vector<WebCore::DictationAlternative>& dictationAlternatives)
        : CoreIPC::Arguments4<const WTF::String&, uint64_t, uint64_t, const WTF::Vector<WebCore::DictationAlternative>&>(text, replacementRangeStart, replacementRangeEnd, dictationAlternatives)
    {
    }
};
#endif

struct SetMinimumLayoutSize : CoreIPC::Arguments1<const WebCore::IntSize&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetMinimumLayoutSize"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebCore::IntSize&> DecodeType;
    explicit SetMinimumLayoutSize(const WebCore::IntSize& minimumLayoutSize)
        : CoreIPC::Arguments1<const WebCore::IntSize&>(minimumLayoutSize)
    {
    }
};

struct SetAutoSizingShouldExpandToViewHeight : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetAutoSizingShouldExpandToViewHeight"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetAutoSizingShouldExpandToViewHeight(bool shouldExpand)
        : CoreIPC::Arguments1<bool>(shouldExpand)
    {
    }
};

#if PLATFORM(EFL)
struct ConfirmComposition : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ConfirmComposition"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit ConfirmComposition(const WTF::String& compositionString)
        : CoreIPC::Arguments1<const WTF::String&>(compositionString)
    {
    }
};
#endif

#if PLATFORM(EFL)
struct SetComposition : CoreIPC::Arguments3<const WTF::String&, const WTF::Vector<WebCore::CompositionUnderline>&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetComposition"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<const WTF::String&, const WTF::Vector<WebCore::CompositionUnderline>&, uint64_t> DecodeType;
    SetComposition(const WTF::String& compositionString, const WTF::Vector<WebCore::CompositionUnderline>& underlines, uint64_t cursorPosition)
        : CoreIPC::Arguments3<const WTF::String&, const WTF::Vector<WebCore::CompositionUnderline>&, uint64_t>(compositionString, underlines, cursorPosition)
    {
    }
};
#endif

#if PLATFORM(EFL)
struct CancelComposition : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CancelComposition"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if PLATFORM(QT)
struct FindZoomableAreaForPoint : CoreIPC::Arguments2<const WebCore::IntPoint&, const WebCore::IntSize&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("FindZoomableAreaForPoint"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WebCore::IntPoint&, const WebCore::IntSize&> DecodeType;
    FindZoomableAreaForPoint(const WebCore::IntPoint& point, const WebCore::IntSize& area)
        : CoreIPC::Arguments2<const WebCore::IntPoint&, const WebCore::IntSize&>(point, area)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct HandleAlternativeTextUIResult : CoreIPC::Arguments1<const String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("HandleAlternativeTextUIResult"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const String&> DecodeType;
    explicit HandleAlternativeTextUIResult(const String& result)
        : CoreIPC::Arguments1<const String&>(result)
    {
    }
};
#endif

#if ENABLE(PAGE_VISIBILITY_API) || ENABLE(HIDDEN_PAGE_DOM_TIMER_THROTTLING)
struct SetVisibilityState : CoreIPC::Arguments2<uint32_t, bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetVisibilityState"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint32_t, bool> DecodeType;
    SetVisibilityState(uint32_t visibilityState, bool isInitialState)
        : CoreIPC::Arguments2<uint32_t, bool>(visibilityState, isInitialState)
    {
    }
};
#endif

#if PLATFORM(GTK) && USE(TEXTURE_MAPPER_GL)
struct SetAcceleratedCompositingWindowId : CoreIPC::Arguments1<int64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetAcceleratedCompositingWindowId"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<int64_t> DecodeType;
    explicit SetAcceleratedCompositingWindowId(int64_t id)
        : CoreIPC::Arguments1<int64_t>(id)
    {
    }
};
#endif

struct SetMainFrameInViewSourceMode : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetMainFrameInViewSourceMode"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetMainFrameInViewSourceMode(bool inViewSourceMode)
        : CoreIPC::Arguments1<bool>(inViewSourceMode)
    {
    }
};

struct SetScrollPinningBehavior : CoreIPC::Arguments1<uint32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetScrollPinningBehavior"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint32_t> DecodeType;
    explicit SetScrollPinningBehavior(uint32_t pinning)
        : CoreIPC::Arguments1<uint32_t>(pinning)
    {
    }
};

} // namespace WebPage
} // namespace Messages

#endif // WebPageMessages_h
