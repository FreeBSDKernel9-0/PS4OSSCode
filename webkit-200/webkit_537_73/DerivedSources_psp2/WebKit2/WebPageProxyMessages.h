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

#ifndef WebPageProxyMessages_h
#define WebPageProxyMessages_h

#include "Arguments.h"
#include "MessageEncoder.h"
#include "SandboxExtension.h"
#include "ShareableBitmap.h"
#include "SharedMemory.h"
#include "StringReference.h"
#include "WebContextMenuItemData.h"
#include "WebHitTestResult.h"
#include "WebPopupItem.h"
#include <WebCore/FloatRect.h>
#include <WebCore/IntRect.h>
#include <WebCore/KeyboardEvent.h>
#include <WebCore/TextCheckerClient.h>
#include <utility>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace CoreIPC {
    class Connection;
    class DataReference;
}

namespace WTF {
    class String;
}

namespace WebCore {
    class Cursor;
    class ProtectionSpace;
    struct GrammarDetail;
    struct WindowFeatures;
    class Color;
    class TextCheckingRequestData;
    class IntSize;
    class ResourceResponse;
    class DragData;
    struct ViewportAttributes;
    class ResourceRequest;
    class FloatRect;
    class IntRect;
    class IntPoint;
    struct DragSession;
    class ResourceError;
    class AuthenticationChallenge;
    struct FileChooserSettings;
}

namespace WebKit {
    struct PlatformPopupMenuData;
    class PlatformCertificateInfo;
    class QtNetworkRequestData;
    struct EditorState;
    struct WebPageCreationParameters;
    struct DictionaryPopupInfo;
    class InjectedBundleUserMessageEncoder;
    struct AttributedString;
}

namespace Messages {
namespace WebPageProxy {

static inline CoreIPC::StringReference messageReceiverName()
{
    return CoreIPC::StringReference("WebPageProxy");
}

#if PLATFORM(MANX)
struct CreateNewPage : CoreIPC::Arguments4<const WebCore::ResourceRequest&, const WebCore::WindowFeatures&, uint32_t, int32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CreateNewPage"); }
    static const bool isSync = true;

    struct DelayedReply : public ThreadSafeRefCounted<DelayedReply> {
        DelayedReply(PassRefPtr<CoreIPC::Connection>, PassOwnPtr<CoreIPC::MessageEncoder>);
        ~DelayedReply();

        bool send(uint64_t newPageID, const WebKit::WebPageCreationParameters& newPageParameters);

    private:
        RefPtr<CoreIPC::Connection> m_connection;
        OwnPtr<CoreIPC::MessageEncoder> m_encoder;
    };

    typedef CoreIPC::Arguments2<uint64_t&, WebKit::WebPageCreationParameters&> Reply;
    typedef CoreIPC::Arguments4<const WebCore::ResourceRequest&, const WebCore::WindowFeatures&, uint32_t, int32_t> DecodeType;
    CreateNewPage(const WebCore::ResourceRequest& request, const WebCore::WindowFeatures& windowFeatures, uint32_t modifiers, int32_t mouseButton)
        : CoreIPC::Arguments4<const WebCore::ResourceRequest&, const WebCore::WindowFeatures&, uint32_t, int32_t>(request, windowFeatures, modifiers, mouseButton)
    {
    }
};
#endif

#if !PLATFORM(MANX)
struct CreateNewPage : CoreIPC::Arguments4<const WebCore::ResourceRequest&, const WebCore::WindowFeatures&, uint32_t, int32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CreateNewPage"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments2<uint64_t&, WebKit::WebPageCreationParameters&> Reply;
    typedef CoreIPC::Arguments4<const WebCore::ResourceRequest&, const WebCore::WindowFeatures&, uint32_t, int32_t> DecodeType;
    CreateNewPage(const WebCore::ResourceRequest& request, const WebCore::WindowFeatures& windowFeatures, uint32_t modifiers, int32_t mouseButton)
        : CoreIPC::Arguments4<const WebCore::ResourceRequest&, const WebCore::WindowFeatures&, uint32_t, int32_t>(request, windowFeatures, modifiers, mouseButton)
    {
    }
};
#endif

struct ShowPage : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ShowPage"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct ClosePage : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ClosePage"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit ClosePage(bool stopResponsivenessTimer)
        : CoreIPC::Arguments1<bool>(stopResponsivenessTimer)
    {
    }
};

#if PLATFORM(MANX)
struct RunJavaScriptAlert : CoreIPC::Arguments2<uint64_t, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RunJavaScriptAlert"); }
    static const bool isSync = true;

    struct DelayedReply : public ThreadSafeRefCounted<DelayedReply> {
        DelayedReply(PassRefPtr<CoreIPC::Connection>, PassOwnPtr<CoreIPC::MessageEncoder>);
        ~DelayedReply();

        bool send();

    private:
        RefPtr<CoreIPC::Connection> m_connection;
        OwnPtr<CoreIPC::MessageEncoder> m_encoder;
    };

    typedef CoreIPC::Arguments0 Reply;
    typedef CoreIPC::Arguments2<uint64_t, const WTF::String&> DecodeType;
    RunJavaScriptAlert(uint64_t frameID, const WTF::String& message)
        : CoreIPC::Arguments2<uint64_t, const WTF::String&>(frameID, message)
    {
    }
};
#endif

#if PLATFORM(MANX)
struct RunJavaScriptConfirm : CoreIPC::Arguments2<uint64_t, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RunJavaScriptConfirm"); }
    static const bool isSync = true;

    struct DelayedReply : public ThreadSafeRefCounted<DelayedReply> {
        DelayedReply(PassRefPtr<CoreIPC::Connection>, PassOwnPtr<CoreIPC::MessageEncoder>);
        ~DelayedReply();

        bool send(bool confirmResult);

    private:
        RefPtr<CoreIPC::Connection> m_connection;
        OwnPtr<CoreIPC::MessageEncoder> m_encoder;
    };

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments2<uint64_t, const WTF::String&> DecodeType;
    RunJavaScriptConfirm(uint64_t frameID, const WTF::String& message)
        : CoreIPC::Arguments2<uint64_t, const WTF::String&>(frameID, message)
    {
    }
};
#endif

#if PLATFORM(MANX)
struct RunJavaScriptPrompt : CoreIPC::Arguments3<uint64_t, const WTF::String&, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RunJavaScriptPrompt"); }
    static const bool isSync = true;

    struct DelayedReply : public ThreadSafeRefCounted<DelayedReply> {
        DelayedReply(PassRefPtr<CoreIPC::Connection>, PassOwnPtr<CoreIPC::MessageEncoder>);
        ~DelayedReply();

        bool send(const WTF::String& promptResult);

    private:
        RefPtr<CoreIPC::Connection> m_connection;
        OwnPtr<CoreIPC::MessageEncoder> m_encoder;
    };

    typedef CoreIPC::Arguments1<WTF::String&> Reply;
    typedef CoreIPC::Arguments3<uint64_t, const WTF::String&, const WTF::String&> DecodeType;
    RunJavaScriptPrompt(uint64_t frameID, const WTF::String& message, const WTF::String& defaultValue)
        : CoreIPC::Arguments3<uint64_t, const WTF::String&, const WTF::String&>(frameID, message, defaultValue)
    {
    }
};
#endif

#if !PLATFORM(MANX)
struct RunJavaScriptAlert : CoreIPC::Arguments2<uint64_t, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RunJavaScriptAlert"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments0 Reply;
    typedef CoreIPC::Arguments2<uint64_t, const WTF::String&> DecodeType;
    RunJavaScriptAlert(uint64_t frameID, const WTF::String& message)
        : CoreIPC::Arguments2<uint64_t, const WTF::String&>(frameID, message)
    {
    }
};
#endif

#if !PLATFORM(MANX)
struct RunJavaScriptConfirm : CoreIPC::Arguments2<uint64_t, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RunJavaScriptConfirm"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments2<uint64_t, const WTF::String&> DecodeType;
    RunJavaScriptConfirm(uint64_t frameID, const WTF::String& message)
        : CoreIPC::Arguments2<uint64_t, const WTF::String&>(frameID, message)
    {
    }
};
#endif

#if !PLATFORM(MANX)
struct RunJavaScriptPrompt : CoreIPC::Arguments3<uint64_t, const WTF::String&, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RunJavaScriptPrompt"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<WTF::String&> Reply;
    typedef CoreIPC::Arguments3<uint64_t, const WTF::String&, const WTF::String&> DecodeType;
    RunJavaScriptPrompt(uint64_t frameID, const WTF::String& message, const WTF::String& defaultValue)
        : CoreIPC::Arguments3<uint64_t, const WTF::String&, const WTF::String&>(frameID, message, defaultValue)
    {
    }
};
#endif

struct ShouldInterruptJavaScript : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ShouldInterruptJavaScript"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments0 DecodeType;
};

struct MouseDidMoveOverElement : CoreIPC::Arguments3<const WebKit::WebHitTestResult::Data&, uint32_t, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("MouseDidMoveOverElement"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<WebKit::WebHitTestResult::Data&, uint32_t&> DecodeType;
    MouseDidMoveOverElement(const WebKit::WebHitTestResult::Data& hitTestResultData, uint32_t modifiers, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments3<const WebKit::WebHitTestResult::Data&, uint32_t, const WebKit::InjectedBundleUserMessageEncoder&>(hitTestResultData, modifiers, userData)
    {
    }
};

struct UnavailablePluginButtonClicked : CoreIPC::Arguments6<uint32_t, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("UnavailablePluginButtonClicked"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments6<uint32_t, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&> DecodeType;
    UnavailablePluginButtonClicked(uint32_t pluginUnavailabilityReason, const WTF::String& mimeType, const WTF::String& pluginURLString, const WTF::String& pluginspageAttributeURLString, const WTF::String& frameURLString, const WTF::String& pageURLString)
        : CoreIPC::Arguments6<uint32_t, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&>(pluginUnavailabilityReason, mimeType, pluginURLString, pluginspageAttributeURLString, frameURLString, pageURLString)
    {
    }
};

struct DidChangeViewportProperties : CoreIPC::Arguments1<const WebCore::ViewportAttributes&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidChangeViewportProperties"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebCore::ViewportAttributes&> DecodeType;
    explicit DidChangeViewportProperties(const WebCore::ViewportAttributes& attributes)
        : CoreIPC::Arguments1<const WebCore::ViewportAttributes&>(attributes)
    {
    }
};

struct DidReceiveEvent : CoreIPC::Arguments2<uint32_t, bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidReceiveEvent"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint32_t, bool> DecodeType;
    DidReceiveEvent(uint32_t type, bool handled)
        : CoreIPC::Arguments2<uint32_t, bool>(type, handled)
    {
    }
};

struct StopResponsivenessTimer : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("StopResponsivenessTimer"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct SetCursor : CoreIPC::Arguments1<const WebCore::Cursor&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetCursor"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebCore::Cursor&> DecodeType;
    explicit SetCursor(const WebCore::Cursor& cursor)
        : CoreIPC::Arguments1<const WebCore::Cursor&>(cursor)
    {
    }
};

struct SetCursorHiddenUntilMouseMoves : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetCursorHiddenUntilMouseMoves"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetCursorHiddenUntilMouseMoves(bool hiddenUntilMouseMoves)
        : CoreIPC::Arguments1<bool>(hiddenUntilMouseMoves)
    {
    }
};

struct SetStatusText : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetStatusText"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit SetStatusText(const WTF::String& statusText)
        : CoreIPC::Arguments1<const WTF::String&>(statusText)
    {
    }
};

struct SetToolTip : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetToolTip"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit SetToolTip(const WTF::String& toolTip)
        : CoreIPC::Arguments1<const WTF::String&>(toolTip)
    {
    }
};

struct SetFocus : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetFocus"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetFocus(bool focused)
        : CoreIPC::Arguments1<bool>(focused)
    {
    }
};

struct TakeFocus : CoreIPC::Arguments1<uint32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("TakeFocus"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint32_t> DecodeType;
    explicit TakeFocus(uint32_t direction)
        : CoreIPC::Arguments1<uint32_t>(direction)
    {
    }
};

struct FocusedFrameChanged : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("FocusedFrameChanged"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit FocusedFrameChanged(uint64_t frameID)
        : CoreIPC::Arguments1<uint64_t>(frameID)
    {
    }
};

struct FrameSetLargestFrameChanged : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("FrameSetLargestFrameChanged"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit FrameSetLargestFrameChanged(uint64_t frameID)
        : CoreIPC::Arguments1<uint64_t>(frameID)
    {
    }
};

struct SetRenderTreeSize : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetRenderTreeSize"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit SetRenderTreeSize(uint64_t treeSize)
        : CoreIPC::Arguments1<uint64_t>(treeSize)
    {
    }
};

struct SetToolbarsAreVisible : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetToolbarsAreVisible"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetToolbarsAreVisible(bool toolbarsAreVisible)
        : CoreIPC::Arguments1<bool>(toolbarsAreVisible)
    {
    }
};

struct GetToolbarsAreVisible : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetToolbarsAreVisible"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments0 DecodeType;
};

struct SetMenuBarIsVisible : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetMenuBarIsVisible"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetMenuBarIsVisible(bool menuBarIsVisible)
        : CoreIPC::Arguments1<bool>(menuBarIsVisible)
    {
    }
};

struct GetMenuBarIsVisible : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetMenuBarIsVisible"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments0 DecodeType;
};

struct SetStatusBarIsVisible : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetStatusBarIsVisible"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetStatusBarIsVisible(bool statusBarIsVisible)
        : CoreIPC::Arguments1<bool>(statusBarIsVisible)
    {
    }
};

struct GetStatusBarIsVisible : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetStatusBarIsVisible"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments0 DecodeType;
};

struct SetIsResizable : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetIsResizable"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetIsResizable(bool isResizable)
        : CoreIPC::Arguments1<bool>(isResizable)
    {
    }
};

struct GetIsResizable : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetIsResizable"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments0 DecodeType;
};

struct SetWindowFrame : CoreIPC::Arguments1<const WebCore::FloatRect&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetWindowFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebCore::FloatRect&> DecodeType;
    explicit SetWindowFrame(const WebCore::FloatRect& windowFrame)
        : CoreIPC::Arguments1<const WebCore::FloatRect&>(windowFrame)
    {
    }
};

struct GetWindowFrame : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetWindowFrame"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<WebCore::FloatRect&> Reply;
    typedef CoreIPC::Arguments0 DecodeType;
};

struct ScreenToWindow : CoreIPC::Arguments1<const WebCore::IntPoint&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ScreenToWindow"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<WebCore::IntPoint&> Reply;
    typedef CoreIPC::Arguments1<const WebCore::IntPoint&> DecodeType;
    explicit ScreenToWindow(const WebCore::IntPoint& screenPoint)
        : CoreIPC::Arguments1<const WebCore::IntPoint&>(screenPoint)
    {
    }
};

struct WindowToScreen : CoreIPC::Arguments1<const WebCore::IntRect&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("WindowToScreen"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<WebCore::IntRect&> Reply;
    typedef CoreIPC::Arguments1<const WebCore::IntRect&> DecodeType;
    explicit WindowToScreen(const WebCore::IntRect& rect)
        : CoreIPC::Arguments1<const WebCore::IntRect&>(rect)
    {
    }
};

struct RunBeforeUnloadConfirmPanel : CoreIPC::Arguments2<const WTF::String&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RunBeforeUnloadConfirmPanel"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments2<const WTF::String&, uint64_t> DecodeType;
    RunBeforeUnloadConfirmPanel(const WTF::String& message, uint64_t frameID)
        : CoreIPC::Arguments2<const WTF::String&, uint64_t>(message, frameID)
    {
    }
};

struct PageDidScroll : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("PageDidScroll"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct RunOpenPanel : CoreIPC::Arguments2<uint64_t, const WebCore::FileChooserSettings&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RunOpenPanel"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, const WebCore::FileChooserSettings&> DecodeType;
    RunOpenPanel(uint64_t frameID, const WebCore::FileChooserSettings& parameters)
        : CoreIPC::Arguments2<uint64_t, const WebCore::FileChooserSettings&>(frameID, parameters)
    {
    }
};

struct PrintFrame : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("PrintFrame"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments0 Reply;
    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit PrintFrame(uint64_t frameID)
        : CoreIPC::Arguments1<uint64_t>(frameID)
    {
    }
};

struct RunModal : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RunModal"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct NotifyScrollerThumbIsVisibleInRect : CoreIPC::Arguments1<const WebCore::IntRect&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("NotifyScrollerThumbIsVisibleInRect"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebCore::IntRect&> DecodeType;
    explicit NotifyScrollerThumbIsVisibleInRect(const WebCore::IntRect& scrollerThumb)
        : CoreIPC::Arguments1<const WebCore::IntRect&>(scrollerThumb)
    {
    }
};

struct RecommendedScrollbarStyleDidChange : CoreIPC::Arguments1<int32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RecommendedScrollbarStyleDidChange"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<int32_t> DecodeType;
    explicit RecommendedScrollbarStyleDidChange(int32_t newStyle)
        : CoreIPC::Arguments1<int32_t>(newStyle)
    {
    }
};

struct DidChangeScrollbarsForMainFrame : CoreIPC::Arguments2<bool, bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidChangeScrollbarsForMainFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<bool, bool> DecodeType;
    DidChangeScrollbarsForMainFrame(bool hasHorizontalScrollbar, bool hasVerticalScrollbar)
        : CoreIPC::Arguments2<bool, bool>(hasHorizontalScrollbar, hasVerticalScrollbar)
    {
    }
};

struct DidChangeScrollOffsetPinningForMainFrame : CoreIPC::Arguments4<bool, bool, bool, bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidChangeScrollOffsetPinningForMainFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments4<bool, bool, bool, bool> DecodeType;
    DidChangeScrollOffsetPinningForMainFrame(bool pinnedToLeftSide, bool pinnedToRightSide, bool pinnedToTopSide, bool pinnedToBottomSide)
        : CoreIPC::Arguments4<bool, bool, bool, bool>(pinnedToLeftSide, pinnedToRightSide, pinnedToTopSide, pinnedToBottomSide)
    {
    }
};

struct DidChangePageCount : CoreIPC::Arguments1<const unsigned&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidChangePageCount"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const unsigned&> DecodeType;
    explicit DidChangePageCount(const unsigned& pageCount)
        : CoreIPC::Arguments1<const unsigned&>(pageCount)
    {
    }
};

struct DidFailToInitializePlugin : CoreIPC::Arguments3<const WTF::String&, const WTF::String&, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidFailToInitializePlugin"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<const WTF::String&, const WTF::String&, const WTF::String&> DecodeType;
    DidFailToInitializePlugin(const WTF::String& mimeType, const WTF::String& frameURLString, const WTF::String& pageURLString)
        : CoreIPC::Arguments3<const WTF::String&, const WTF::String&, const WTF::String&>(mimeType, frameURLString, pageURLString)
    {
    }
};

struct DidBlockInsecurePluginVersion : CoreIPC::Arguments5<const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidBlockInsecurePluginVersion"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments5<const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, bool> DecodeType;
    DidBlockInsecurePluginVersion(const WTF::String& mimeType, const WTF::String& pluginURLString, const WTF::String& frameURLString, const WTF::String& pageURLString, bool replacementObscured)
        : CoreIPC::Arguments5<const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, bool>(mimeType, pluginURLString, frameURLString, pageURLString, replacementObscured)
    {
    }
};

struct SetCanShortCircuitHorizontalWheelEvents : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetCanShortCircuitHorizontalWheelEvents"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetCanShortCircuitHorizontalWheelEvents(bool canShortCircuitHorizontalWheelEvents)
        : CoreIPC::Arguments1<bool>(canShortCircuitHorizontalWheelEvents)
    {
    }
};

#if PLATFORM(EFL)
struct HandleInputMethodKeydown : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("HandleInputMethodKeydown"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if USE(TILED_BACKING_STORE)
struct PageDidRequestScroll : CoreIPC::Arguments1<const WebCore::IntPoint&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("PageDidRequestScroll"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebCore::IntPoint&> DecodeType;
    explicit PageDidRequestScroll(const WebCore::IntPoint& point)
        : CoreIPC::Arguments1<const WebCore::IntPoint&>(point)
    {
    }
};
#endif

#if USE(TILED_BACKING_STORE)
struct PageTransitionViewportReady : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("PageTransitionViewportReady"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if PLATFORM(QT)
struct DidFindZoomableArea : CoreIPC::Arguments2<const WebCore::IntPoint&, const WebCore::IntRect&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidFindZoomableArea"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WebCore::IntPoint&, const WebCore::IntRect&> DecodeType;
    DidFindZoomableArea(const WebCore::IntPoint& target, const WebCore::IntRect& area)
        : CoreIPC::Arguments2<const WebCore::IntPoint&, const WebCore::IntRect&>(target, area)
    {
    }
};
#endif

#if PLATFORM(QT)
struct AuthenticationRequiredRequest : CoreIPC::Arguments3<const WTF::String&, const WTF::String&, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("AuthenticationRequiredRequest"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments2<WTF::String&, WTF::String&> Reply;
    typedef CoreIPC::Arguments3<const WTF::String&, const WTF::String&, const WTF::String&> DecodeType;
    AuthenticationRequiredRequest(const WTF::String& hostname, const WTF::String& realm, const WTF::String& prefilledUsername)
        : CoreIPC::Arguments3<const WTF::String&, const WTF::String&, const WTF::String&>(hostname, realm, prefilledUsername)
    {
    }
};
#endif

#if PLATFORM(QT)
struct CertificateVerificationRequest : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CertificateVerificationRequest"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit CertificateVerificationRequest(const WTF::String& hostname)
        : CoreIPC::Arguments1<const WTF::String&>(hostname)
    {
    }
};
#endif

#if PLATFORM(QT)
struct ProxyAuthenticationRequiredRequest : CoreIPC::Arguments3<const WTF::String&, uint16_t, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ProxyAuthenticationRequiredRequest"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments2<WTF::String&, WTF::String&> Reply;
    typedef CoreIPC::Arguments3<const WTF::String&, uint16_t, const WTF::String&> DecodeType;
    ProxyAuthenticationRequiredRequest(const WTF::String& hostname, uint16_t port, const WTF::String& prefilledUsername)
        : CoreIPC::Arguments3<const WTF::String&, uint16_t, const WTF::String&>(hostname, port, prefilledUsername)
    {
    }
};
#endif

#if PLATFORM(QT) || PLATFORM(EFL)
struct DidChangeContentsSize : CoreIPC::Arguments1<const WebCore::IntSize&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidChangeContentsSize"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebCore::IntSize&> DecodeType;
    explicit DidChangeContentsSize(const WebCore::IntSize& newSize)
        : CoreIPC::Arguments1<const WebCore::IntSize&>(newSize)
    {
    }
};
#endif

#if PLATFORM(MANX)
struct AuthenticationRequiredRequest : CoreIPC::Arguments5<uint64_t, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("AuthenticationRequiredRequest"); }
    static const bool isSync = true;

    struct DelayedReply : public ThreadSafeRefCounted<DelayedReply> {
        DelayedReply(PassRefPtr<CoreIPC::Connection>, PassOwnPtr<CoreIPC::MessageEncoder>);
        ~DelayedReply();

        bool send(bool returnValue, const WTF::String& username, const WTF::String& password);

    private:
        RefPtr<CoreIPC::Connection> m_connection;
        OwnPtr<CoreIPC::MessageEncoder> m_encoder;
    };

    typedef CoreIPC::Arguments3<bool&, WTF::String&, WTF::String&> Reply;
    typedef CoreIPC::Arguments5<uint64_t, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&> DecodeType;
    AuthenticationRequiredRequest(uint64_t frameID, const WTF::String& hostname, const WTF::String& realm, const WTF::String& prefilledUsername, const WTF::String& prefilledPassword)
        : CoreIPC::Arguments5<uint64_t, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&>(frameID, hostname, realm, prefilledUsername, prefilledPassword)
    {
    }
};
#endif

#if PLATFORM(MANX)
struct CertificateVerificationRequest : CoreIPC::Arguments4<uint64_t, uint32_t, const WTF::String&, const Vector<CString>&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CertificateVerificationRequest"); }
    static const bool isSync = true;

    struct DelayedReply : public ThreadSafeRefCounted<DelayedReply> {
        DelayedReply(PassRefPtr<CoreIPC::Connection>, PassOwnPtr<CoreIPC::MessageEncoder>);
        ~DelayedReply();

        bool send(bool ignoreErrors);

    private:
        RefPtr<CoreIPC::Connection> m_connection;
        OwnPtr<CoreIPC::MessageEncoder> m_encoder;
    };

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments4<uint64_t, uint32_t, const WTF::String&, const Vector<CString>&> DecodeType;
    CertificateVerificationRequest(uint64_t frameID, uint32_t error, const WTF::String& url, const Vector<CString>& certificates)
        : CoreIPC::Arguments4<uint64_t, uint32_t, const WTF::String&, const Vector<CString>&>(frameID, error, url, certificates)
    {
    }
};
#endif

#if ENABLE(TOUCH_EVENTS)
struct NeedTouchEvents : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("NeedTouchEvents"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit NeedTouchEvents(bool needTouchEvents)
        : CoreIPC::Arguments1<bool>(needTouchEvents)
    {
    }
};
#endif

#if ENABLE(INPUT_TYPE_COLOR)
struct ShowColorChooser : CoreIPC::Arguments2<const WebCore::Color&, const WebCore::IntRect&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ShowColorChooser"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WebCore::Color&, const WebCore::IntRect&> DecodeType;
    ShowColorChooser(const WebCore::Color& initialColor, const WebCore::IntRect& elementRect)
        : CoreIPC::Arguments2<const WebCore::Color&, const WebCore::IntRect&>(initialColor, elementRect)
    {
    }
};
#endif

#if ENABLE(INPUT_TYPE_COLOR)
struct SetColorChooserColor : CoreIPC::Arguments1<const WebCore::Color&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetColorChooserColor"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebCore::Color&> DecodeType;
    explicit SetColorChooserColor(const WebCore::Color& color)
        : CoreIPC::Arguments1<const WebCore::Color&>(color)
    {
    }
};
#endif

#if ENABLE(INPUT_TYPE_COLOR)
struct EndColorChooser : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("EndColorChooser"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

struct DecidePolicyForResponseSync : CoreIPC::Arguments5<uint64_t, const WebCore::ResourceResponse&, const WebCore::ResourceRequest&, uint64_t, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DecidePolicyForResponseSync"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments3<bool&, uint64_t&, uint64_t&> Reply;
    typedef CoreIPC::Arguments4<uint64_t&, WebCore::ResourceResponse&, WebCore::ResourceRequest&, uint64_t&> DecodeType;
    DecidePolicyForResponseSync(uint64_t frameID, const WebCore::ResourceResponse& response, const WebCore::ResourceRequest& request, uint64_t listenerID, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments5<uint64_t, const WebCore::ResourceResponse&, const WebCore::ResourceRequest&, uint64_t, const WebKit::InjectedBundleUserMessageEncoder&>(frameID, response, request, listenerID, userData)
    {
    }
};

struct DecidePolicyForNavigationAction : CoreIPC::Arguments7<uint64_t, uint32_t, uint32_t, int32_t, const WebCore::ResourceRequest&, uint64_t, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DecidePolicyForNavigationAction"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments3<bool&, uint64_t&, uint64_t&> Reply;
    typedef CoreIPC::Arguments6<uint64_t&, uint32_t&, uint32_t&, int32_t&, WebCore::ResourceRequest&, uint64_t&> DecodeType;
    DecidePolicyForNavigationAction(uint64_t frameID, uint32_t navigationType, uint32_t modifiers, int32_t mouseButton, const WebCore::ResourceRequest& request, uint64_t listenerID, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments7<uint64_t, uint32_t, uint32_t, int32_t, const WebCore::ResourceRequest&, uint64_t, const WebKit::InjectedBundleUserMessageEncoder&>(frameID, navigationType, modifiers, mouseButton, request, listenerID, userData)
    {
    }
};

struct DecidePolicyForNewWindowAction : CoreIPC::Arguments8<uint64_t, uint32_t, uint32_t, int32_t, const WebCore::ResourceRequest&, const WTF::String&, uint64_t, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DecidePolicyForNewWindowAction"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments7<uint64_t&, uint32_t&, uint32_t&, int32_t&, WebCore::ResourceRequest&, WTF::String&, uint64_t&> DecodeType;
    DecidePolicyForNewWindowAction(uint64_t frameID, uint32_t navigationType, uint32_t modifiers, int32_t mouseButton, const WebCore::ResourceRequest& request, const WTF::String& frameName, uint64_t listenerID, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments8<uint64_t, uint32_t, uint32_t, int32_t, const WebCore::ResourceRequest&, const WTF::String&, uint64_t, const WebKit::InjectedBundleUserMessageEncoder&>(frameID, navigationType, modifiers, mouseButton, request, frameName, listenerID, userData)
    {
    }
};

struct UnableToImplementPolicy : CoreIPC::Arguments3<uint64_t, const WebCore::ResourceError&, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("UnableToImplementPolicy"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t&, WebCore::ResourceError&> DecodeType;
    UnableToImplementPolicy(uint64_t frameID, const WebCore::ResourceError& error, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments3<uint64_t, const WebCore::ResourceError&, const WebKit::InjectedBundleUserMessageEncoder&>(frameID, error, userData)
    {
    }
};

struct DidChangeProgress : CoreIPC::Arguments1<double> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidChangeProgress"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<double> DecodeType;
    explicit DidChangeProgress(double value)
        : CoreIPC::Arguments1<double>(value)
    {
    }
};

struct DidFinishProgress : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidFinishProgress"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct DidStartProgress : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidStartProgress"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct DidCreateMainFrame : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidCreateMainFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit DidCreateMainFrame(uint64_t frameID)
        : CoreIPC::Arguments1<uint64_t>(frameID)
    {
    }
};

struct DidCreateSubframe : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidCreateSubframe"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit DidCreateSubframe(uint64_t frameID)
        : CoreIPC::Arguments1<uint64_t>(frameID)
    {
    }
};

struct DidCommitLoadForFrame : CoreIPC::Arguments6<uint64_t, const WTF::String&, bool, uint32_t, const WebKit::PlatformCertificateInfo&, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidCommitLoadForFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments5<uint64_t&, WTF::String&, bool&, uint32_t&, WebKit::PlatformCertificateInfo&> DecodeType;
    DidCommitLoadForFrame(uint64_t frameID, const WTF::String& mimeType, bool hasCustomRepresentation, uint32_t loadType, const WebKit::PlatformCertificateInfo& certificateInfo, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments6<uint64_t, const WTF::String&, bool, uint32_t, const WebKit::PlatformCertificateInfo&, const WebKit::InjectedBundleUserMessageEncoder&>(frameID, mimeType, hasCustomRepresentation, loadType, certificateInfo, userData)
    {
    }
};

struct DidFailLoadForFrame : CoreIPC::Arguments3<uint64_t, const WebCore::ResourceError&, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidFailLoadForFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t&, WebCore::ResourceError&> DecodeType;
    DidFailLoadForFrame(uint64_t frameID, const WebCore::ResourceError& error, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments3<uint64_t, const WebCore::ResourceError&, const WebKit::InjectedBundleUserMessageEncoder&>(frameID, error, userData)
    {
    }
};

struct DidFailProvisionalLoadForFrame : CoreIPC::Arguments3<uint64_t, const WebCore::ResourceError&, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidFailProvisionalLoadForFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t&, WebCore::ResourceError&> DecodeType;
    DidFailProvisionalLoadForFrame(uint64_t frameID, const WebCore::ResourceError& error, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments3<uint64_t, const WebCore::ResourceError&, const WebKit::InjectedBundleUserMessageEncoder&>(frameID, error, userData)
    {
    }
};

struct DidFinishDocumentLoadForFrame : CoreIPC::Arguments2<uint64_t, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidFinishDocumentLoadForFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t&> DecodeType;
    DidFinishDocumentLoadForFrame(uint64_t frameID, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments2<uint64_t, const WebKit::InjectedBundleUserMessageEncoder&>(frameID, userData)
    {
    }
};

struct DidFinishLoadForFrame : CoreIPC::Arguments2<uint64_t, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidFinishLoadForFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t&> DecodeType;
    DidFinishLoadForFrame(uint64_t frameID, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments2<uint64_t, const WebKit::InjectedBundleUserMessageEncoder&>(frameID, userData)
    {
    }
};

struct DidFirstLayoutForFrame : CoreIPC::Arguments2<uint64_t, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidFirstLayoutForFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t&> DecodeType;
    DidFirstLayoutForFrame(uint64_t frameID, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments2<uint64_t, const WebKit::InjectedBundleUserMessageEncoder&>(frameID, userData)
    {
    }
};

struct DidFirstVisuallyNonEmptyLayoutForFrame : CoreIPC::Arguments2<uint64_t, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidFirstVisuallyNonEmptyLayoutForFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t&> DecodeType;
    DidFirstVisuallyNonEmptyLayoutForFrame(uint64_t frameID, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments2<uint64_t, const WebKit::InjectedBundleUserMessageEncoder&>(frameID, userData)
    {
    }
};

struct DidNewFirstVisuallyNonEmptyLayout : CoreIPC::Arguments1<const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidNewFirstVisuallyNonEmptyLayout"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
    explicit DidNewFirstVisuallyNonEmptyLayout(const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments1<const WebKit::InjectedBundleUserMessageEncoder&>(userData)
    {
    }
};

struct DidLayout : CoreIPC::Arguments2<uint32_t, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidLayout"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint32_t&> DecodeType;
    DidLayout(uint32_t type, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments2<uint32_t, const WebKit::InjectedBundleUserMessageEncoder&>(type, userData)
    {
    }
};

struct DidReceiveServerRedirectForProvisionalLoadForFrame : CoreIPC::Arguments3<uint64_t, const WTF::String&, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidReceiveServerRedirectForProvisionalLoadForFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t&, WTF::String&> DecodeType;
    DidReceiveServerRedirectForProvisionalLoadForFrame(uint64_t frameID, const WTF::String& url, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments3<uint64_t, const WTF::String&, const WebKit::InjectedBundleUserMessageEncoder&>(frameID, url, userData)
    {
    }
};

struct DidRemoveFrameFromHierarchy : CoreIPC::Arguments2<uint64_t, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidRemoveFrameFromHierarchy"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t&> DecodeType;
    DidRemoveFrameFromHierarchy(uint64_t frameID, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments2<uint64_t, const WebKit::InjectedBundleUserMessageEncoder&>(frameID, userData)
    {
    }
};

struct DidStartProvisionalLoadForFrame : CoreIPC::Arguments4<uint64_t, const WTF::String&, const WTF::String&, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidStartProvisionalLoadForFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<uint64_t&, WTF::String&, WTF::String&> DecodeType;
    DidStartProvisionalLoadForFrame(uint64_t frameID, const WTF::String& url, const WTF::String& unreachableURL, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments4<uint64_t, const WTF::String&, const WTF::String&, const WebKit::InjectedBundleUserMessageEncoder&>(frameID, url, unreachableURL, userData)
    {
    }
};

struct DidReceiveTitleForFrame : CoreIPC::Arguments3<uint64_t, const WTF::String&, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidReceiveTitleForFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t&, WTF::String&> DecodeType;
    DidReceiveTitleForFrame(uint64_t frameID, const WTF::String& title, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments3<uint64_t, const WTF::String&, const WebKit::InjectedBundleUserMessageEncoder&>(frameID, title, userData)
    {
    }
};

struct DidDisplayInsecureContentForFrame : CoreIPC::Arguments2<uint64_t, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidDisplayInsecureContentForFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t&> DecodeType;
    DidDisplayInsecureContentForFrame(uint64_t frameID, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments2<uint64_t, const WebKit::InjectedBundleUserMessageEncoder&>(frameID, userData)
    {
    }
};

struct DidRunInsecureContentForFrame : CoreIPC::Arguments2<uint64_t, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidRunInsecureContentForFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t&> DecodeType;
    DidRunInsecureContentForFrame(uint64_t frameID, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments2<uint64_t, const WebKit::InjectedBundleUserMessageEncoder&>(frameID, userData)
    {
    }
};

struct DidDetectXSSForFrame : CoreIPC::Arguments2<uint64_t, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidDetectXSSForFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t&> DecodeType;
    DidDetectXSSForFrame(uint64_t frameID, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments2<uint64_t, const WebKit::InjectedBundleUserMessageEncoder&>(frameID, userData)
    {
    }
};

struct DidSameDocumentNavigationForFrame : CoreIPC::Arguments4<uint64_t, uint32_t, const WTF::String&, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidSameDocumentNavigationForFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<uint64_t&, uint32_t&, WTF::String&> DecodeType;
    DidSameDocumentNavigationForFrame(uint64_t frameID, uint32_t type, const WTF::String& url, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments4<uint64_t, uint32_t, const WTF::String&, const WebKit::InjectedBundleUserMessageEncoder&>(frameID, type, url, userData)
    {
    }
};

struct FrameDidBecomeFrameSet : CoreIPC::Arguments2<uint64_t, bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("FrameDidBecomeFrameSet"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, bool> DecodeType;
    FrameDidBecomeFrameSet(uint64_t frameID, bool value)
        : CoreIPC::Arguments2<uint64_t, bool>(frameID, value)
    {
    }
};

#if PLATFORM(QT)
struct ResolveApplicationSchemeRequest : CoreIPC::Arguments1<const WebKit::QtNetworkRequestData&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ResolveApplicationSchemeRequest"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebKit::QtNetworkRequestData&> DecodeType;
    explicit ResolveApplicationSchemeRequest(const WebKit::QtNetworkRequestData& request)
        : CoreIPC::Arguments1<const WebKit::QtNetworkRequestData&>(request)
    {
    }
};
#endif

struct DidFinishLoadingDataForCustomRepresentation : CoreIPC::Arguments2<const WTF::String&, const CoreIPC::DataReference&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidFinishLoadingDataForCustomRepresentation"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WTF::String&, const CoreIPC::DataReference&> DecodeType;
    DidFinishLoadingDataForCustomRepresentation(const WTF::String& suggestedFilename, const CoreIPC::DataReference& data)
        : CoreIPC::Arguments2<const WTF::String&, const CoreIPC::DataReference&>(suggestedFilename, data)
    {
    }
};

struct WillSubmitForm : CoreIPC::Arguments5<uint64_t, uint64_t, const WTF::Vector<std::pair<WTF::String, WTF::String>>&, uint64_t, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("WillSubmitForm"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments4<uint64_t&, uint64_t&, WTF::Vector<std::pair<WTF::String, WTF::String>>&, uint64_t&> DecodeType;
    WillSubmitForm(uint64_t frameID, uint64_t sourceFrameID, const WTF::Vector<std::pair<WTF::String, WTF::String>>& textFieldValues, uint64_t listenerID, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments5<uint64_t, uint64_t, const WTF::Vector<std::pair<WTF::String, WTF::String>>&, uint64_t, const WebKit::InjectedBundleUserMessageEncoder&>(frameID, sourceFrameID, textFieldValues, listenerID, userData)
    {
    }
};

struct VoidCallback : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("VoidCallback"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit VoidCallback(uint64_t callbackID)
        : CoreIPC::Arguments1<uint64_t>(callbackID)
    {
    }
};

struct DataCallback : CoreIPC::Arguments2<const CoreIPC::DataReference&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DataCallback"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const CoreIPC::DataReference&, uint64_t> DecodeType;
    DataCallback(const CoreIPC::DataReference& resultData, uint64_t callbackID)
        : CoreIPC::Arguments2<const CoreIPC::DataReference&, uint64_t>(resultData, callbackID)
    {
    }
};

struct ImageCallback : CoreIPC::Arguments2<const WebKit::ShareableBitmap::Handle&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ImageCallback"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WebKit::ShareableBitmap::Handle&, uint64_t> DecodeType;
    ImageCallback(const WebKit::ShareableBitmap::Handle& bitmapHandle, uint64_t callbackID)
        : CoreIPC::Arguments2<const WebKit::ShareableBitmap::Handle&, uint64_t>(bitmapHandle, callbackID)
    {
    }
};

struct StringCallback : CoreIPC::Arguments2<const WTF::String&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("StringCallback"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WTF::String&, uint64_t> DecodeType;
    StringCallback(const WTF::String& resultString, uint64_t callbackID)
        : CoreIPC::Arguments2<const WTF::String&, uint64_t>(resultString, callbackID)
    {
    }
};

struct ScriptValueCallback : CoreIPC::Arguments2<const CoreIPC::DataReference&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ScriptValueCallback"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const CoreIPC::DataReference&, uint64_t> DecodeType;
    ScriptValueCallback(const CoreIPC::DataReference& resultData, uint64_t callbackID)
        : CoreIPC::Arguments2<const CoreIPC::DataReference&, uint64_t>(resultData, callbackID)
    {
    }
};

struct ComputedPagesCallback : CoreIPC::Arguments3<const Vector<WebCore::IntRect>&, double, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ComputedPagesCallback"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<const Vector<WebCore::IntRect>&, double, uint64_t> DecodeType;
    ComputedPagesCallback(const Vector<WebCore::IntRect>& pageRects, double totalScaleFactorForPrinting, uint64_t callbackID)
        : CoreIPC::Arguments3<const Vector<WebCore::IntRect>&, double, uint64_t>(pageRects, totalScaleFactorForPrinting, callbackID)
    {
    }
};

struct ValidateCommandCallback : CoreIPC::Arguments4<const WTF::String&, bool, int32_t, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ValidateCommandCallback"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments4<const WTF::String&, bool, int32_t, uint64_t> DecodeType;
    ValidateCommandCallback(const WTF::String& command, bool isEnabled, int32_t state, uint64_t callbackID)
        : CoreIPC::Arguments4<const WTF::String&, bool, int32_t, uint64_t>(command, isEnabled, state, callbackID)
    {
    }
};

#if PLATFORM(GTK)
struct PrintFinishedCallback : CoreIPC::Arguments2<const WebCore::ResourceError&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("PrintFinishedCallback"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WebCore::ResourceError&, uint64_t> DecodeType;
    PrintFinishedCallback(const WebCore::ResourceError& error, uint64_t callbackID)
        : CoreIPC::Arguments2<const WebCore::ResourceError&, uint64_t>(error, callbackID)
    {
    }
};
#endif

struct PageScaleFactorDidChange : CoreIPC::Arguments1<double> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("PageScaleFactorDidChange"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<double> DecodeType;
    explicit PageScaleFactorDidChange(double scaleFactor)
        : CoreIPC::Arguments1<double>(scaleFactor)
    {
    }
};

struct PageZoomFactorDidChange : CoreIPC::Arguments1<double> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("PageZoomFactorDidChange"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<double> DecodeType;
    explicit PageZoomFactorDidChange(double zoomFactor)
        : CoreIPC::Arguments1<double>(zoomFactor)
    {
    }
};

#if PLATFORM(GTK)
struct GetEditorCommandsForKeyEvent : CoreIPC::Arguments1<const AtomicString&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetEditorCommandsForKeyEvent"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<Vector<WTF::String>&> Reply;
    typedef CoreIPC::Arguments1<const AtomicString&> DecodeType;
    explicit GetEditorCommandsForKeyEvent(const AtomicString& eventType)
        : CoreIPC::Arguments1<const AtomicString&>(eventType)
    {
    }
};
#endif

#if PLATFORM(GTK)
struct BindAccessibilityTree : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("BindAccessibilityTree"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit BindAccessibilityTree(const WTF::String& plugID)
        : CoreIPC::Arguments1<const WTF::String&>(plugID)
    {
    }
};
#endif

#if PLATFORM(GTK)
struct SetInputMethodState : CoreIPC::Arguments1<bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetInputMethodState"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<bool> DecodeType;
    explicit SetInputMethodState(bool enabled)
        : CoreIPC::Arguments1<bool>(enabled)
    {
    }
};
#endif

struct BackForwardAddItem : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("BackForwardAddItem"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit BackForwardAddItem(uint64_t itemID)
        : CoreIPC::Arguments1<uint64_t>(itemID)
    {
    }
};

struct BackForwardGoToItem : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("BackForwardGoToItem"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<WebKit::SandboxExtension::Handle&> Reply;
    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit BackForwardGoToItem(uint64_t itemID)
        : CoreIPC::Arguments1<uint64_t>(itemID)
    {
    }
};

struct BackForwardItemAtIndex : CoreIPC::Arguments1<int32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("BackForwardItemAtIndex"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<uint64_t&> Reply;
    typedef CoreIPC::Arguments1<int32_t> DecodeType;
    explicit BackForwardItemAtIndex(int32_t itemIndex)
        : CoreIPC::Arguments1<int32_t>(itemIndex)
    {
    }
};

struct BackForwardBackListCount : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("BackForwardBackListCount"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<int32_t&> Reply;
    typedef CoreIPC::Arguments0 DecodeType;
};

struct BackForwardForwardListCount : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("BackForwardForwardListCount"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<int32_t&> Reply;
    typedef CoreIPC::Arguments0 DecodeType;
};

struct BackForwardClear : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("BackForwardClear"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct ShouldGoToBackForwardListItem : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ShouldGoToBackForwardListItem"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit ShouldGoToBackForwardListItem(uint64_t itemID)
        : CoreIPC::Arguments1<uint64_t>(itemID)
    {
    }
};

struct WillGoToBackForwardListItem : CoreIPC::Arguments2<uint64_t, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("WillGoToBackForwardListItem"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t&> DecodeType;
    WillGoToBackForwardListItem(uint64_t itemID, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments2<uint64_t, const WebKit::InjectedBundleUserMessageEncoder&>(itemID, userData)
    {
    }
};

struct RegisterEditCommandForUndo : CoreIPC::Arguments2<uint64_t, uint32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RegisterEditCommandForUndo"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, uint32_t> DecodeType;
    RegisterEditCommandForUndo(uint64_t commandID, uint32_t editAction)
        : CoreIPC::Arguments2<uint64_t, uint32_t>(commandID, editAction)
    {
    }
};

struct ClearAllEditCommands : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ClearAllEditCommands"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct CanUndoRedo : CoreIPC::Arguments1<uint32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CanUndoRedo"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments1<uint32_t> DecodeType;
    explicit CanUndoRedo(uint32_t action)
        : CoreIPC::Arguments1<uint32_t>(action)
    {
    }
};

struct ExecuteUndoRedo : CoreIPC::Arguments1<uint32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ExecuteUndoRedo"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments1<uint32_t> DecodeType;
    explicit ExecuteUndoRedo(uint32_t action)
        : CoreIPC::Arguments1<uint32_t>(action)
    {
    }
};

struct EditorStateChanged : CoreIPC::Arguments1<const WebKit::EditorState&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("EditorStateChanged"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebKit::EditorState&> DecodeType;
    explicit EditorStateChanged(const WebKit::EditorState& editorState)
        : CoreIPC::Arguments1<const WebKit::EditorState&>(editorState)
    {
    }
};

#if PLATFORM(QT)
struct WillSetInputMethodState : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("WillSetInputMethodState"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

struct DidCountStringMatches : CoreIPC::Arguments2<const WTF::String&, uint32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidCountStringMatches"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WTF::String&, uint32_t> DecodeType;
    DidCountStringMatches(const WTF::String& string, uint32_t matchCount)
        : CoreIPC::Arguments2<const WTF::String&, uint32_t>(string, matchCount)
    {
    }
};

struct SetFindIndicator : CoreIPC::Arguments6<const WebCore::FloatRect&, const Vector<WebCore::FloatRect>&, float, const WebKit::ShareableBitmap::Handle&, bool, bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetFindIndicator"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments6<const WebCore::FloatRect&, const Vector<WebCore::FloatRect>&, float, const WebKit::ShareableBitmap::Handle&, bool, bool> DecodeType;
    SetFindIndicator(const WebCore::FloatRect& selectionRect, const Vector<WebCore::FloatRect>& textRects, float contentImageScaleFactor, const WebKit::ShareableBitmap::Handle& contentImageHandle, bool fadeOut, bool animate)
        : CoreIPC::Arguments6<const WebCore::FloatRect&, const Vector<WebCore::FloatRect>&, float, const WebKit::ShareableBitmap::Handle&, bool, bool>(selectionRect, textRects, contentImageScaleFactor, contentImageHandle, fadeOut, animate)
    {
    }
};

struct DidFindString : CoreIPC::Arguments2<const WTF::String&, uint32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidFindString"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WTF::String&, uint32_t> DecodeType;
    DidFindString(const WTF::String& string, uint32_t matchCount)
        : CoreIPC::Arguments2<const WTF::String&, uint32_t>(string, matchCount)
    {
    }
};

struct DidFailToFindString : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidFailToFindString"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit DidFailToFindString(const WTF::String& string)
        : CoreIPC::Arguments1<const WTF::String&>(string)
    {
    }
};

struct DidFindStringMatches : CoreIPC::Arguments3<const WTF::String&, const Vector<Vector<WebCore::IntRect>>&, int32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidFindStringMatches"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<const WTF::String&, const Vector<Vector<WebCore::IntRect>>&, int32_t> DecodeType;
    DidFindStringMatches(const WTF::String& string, const Vector<Vector<WebCore::IntRect>>& matches, int32_t firstIndexAfterSelection)
        : CoreIPC::Arguments3<const WTF::String&, const Vector<Vector<WebCore::IntRect>>&, int32_t>(string, matches, firstIndexAfterSelection)
    {
    }
};

struct DidGetImageForFindMatch : CoreIPC::Arguments2<const WebKit::ShareableBitmap::Handle&, uint32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidGetImageForFindMatch"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WebKit::ShareableBitmap::Handle&, uint32_t> DecodeType;
    DidGetImageForFindMatch(const WebKit::ShareableBitmap::Handle& contentImageHandle, uint32_t matchIndex)
        : CoreIPC::Arguments2<const WebKit::ShareableBitmap::Handle&, uint32_t>(contentImageHandle, matchIndex)
    {
    }
};

struct ShowPopupMenu : CoreIPC::Arguments5<const WebCore::IntRect&, uint64_t, const Vector<WebKit::WebPopupItem>&, int32_t, const WebKit::PlatformPopupMenuData&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ShowPopupMenu"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments5<const WebCore::IntRect&, uint64_t, const Vector<WebKit::WebPopupItem>&, int32_t, const WebKit::PlatformPopupMenuData&> DecodeType;
    ShowPopupMenu(const WebCore::IntRect& rect, uint64_t textDirection, const Vector<WebKit::WebPopupItem>& items, int32_t selectedIndex, const WebKit::PlatformPopupMenuData& data)
        : CoreIPC::Arguments5<const WebCore::IntRect&, uint64_t, const Vector<WebKit::WebPopupItem>&, int32_t, const WebKit::PlatformPopupMenuData&>(rect, textDirection, items, selectedIndex, data)
    {
    }
};

struct HidePopupMenu : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("HidePopupMenu"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

#if ENABLE(CONTEXT_MENUS)
struct ShowContextMenu : CoreIPC::Arguments4<const WebCore::IntPoint&, const WebKit::WebHitTestResult::Data&, const Vector<WebKit::WebContextMenuItemData>&, const WebKit::InjectedBundleUserMessageEncoder&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ShowContextMenu"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<WebCore::IntPoint&, WebKit::WebHitTestResult::Data&, Vector<WebKit::WebContextMenuItemData>&> DecodeType;
    ShowContextMenu(const WebCore::IntPoint& menuLocation, const WebKit::WebHitTestResult::Data& hitTestResultData, const Vector<WebKit::WebContextMenuItemData>& items, const WebKit::InjectedBundleUserMessageEncoder& userData)
        : CoreIPC::Arguments4<const WebCore::IntPoint&, const WebKit::WebHitTestResult::Data&, const Vector<WebKit::WebContextMenuItemData>&, const WebKit::InjectedBundleUserMessageEncoder&>(menuLocation, hitTestResultData, items, userData)
    {
    }
};
#endif

struct CanAuthenticateAgainstProtectionSpaceInFrame : CoreIPC::Arguments2<uint64_t, const WebCore::ProtectionSpace&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CanAuthenticateAgainstProtectionSpaceInFrame"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments2<uint64_t, const WebCore::ProtectionSpace&> DecodeType;
    CanAuthenticateAgainstProtectionSpaceInFrame(uint64_t frameID, const WebCore::ProtectionSpace& protectionSpace)
        : CoreIPC::Arguments2<uint64_t, const WebCore::ProtectionSpace&>(frameID, protectionSpace)
    {
    }
};

struct DidReceiveAuthenticationChallenge : CoreIPC::Arguments3<uint64_t, const WebCore::AuthenticationChallenge&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidReceiveAuthenticationChallenge"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<uint64_t, const WebCore::AuthenticationChallenge&, uint64_t> DecodeType;
    DidReceiveAuthenticationChallenge(uint64_t frameID, const WebCore::AuthenticationChallenge& challenge, uint64_t challengeID)
        : CoreIPC::Arguments3<uint64_t, const WebCore::AuthenticationChallenge&, uint64_t>(frameID, challenge, challengeID)
    {
    }
};

struct ExceededDatabaseQuota : CoreIPC::Arguments8<uint64_t, const WTF::String&, const WTF::String&, const WTF::String&, uint64_t, uint64_t, uint64_t, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ExceededDatabaseQuota"); }
    static const bool isSync = true;

    struct DelayedReply : public ThreadSafeRefCounted<DelayedReply> {
        DelayedReply(PassRefPtr<CoreIPC::Connection>, PassOwnPtr<CoreIPC::MessageEncoder>);
        ~DelayedReply();

        bool send(uint64_t newQuota);

    private:
        RefPtr<CoreIPC::Connection> m_connection;
        OwnPtr<CoreIPC::MessageEncoder> m_encoder;
    };

    typedef CoreIPC::Arguments1<uint64_t&> Reply;
    typedef CoreIPC::Arguments8<uint64_t, const WTF::String&, const WTF::String&, const WTF::String&, uint64_t, uint64_t, uint64_t, uint64_t> DecodeType;
    ExceededDatabaseQuota(uint64_t frameID, const WTF::String& originIdentifier, const WTF::String& databaseName, const WTF::String& databaseDisplayName, uint64_t currentQuota, uint64_t currentOriginUsage, uint64_t currentDatabaseUsage, uint64_t expectedUsage)
        : CoreIPC::Arguments8<uint64_t, const WTF::String&, const WTF::String&, const WTF::String&, uint64_t, uint64_t, uint64_t, uint64_t>(frameID, originIdentifier, databaseName, databaseDisplayName, currentQuota, currentOriginUsage, currentDatabaseUsage, expectedUsage)
    {
    }
};

struct RequestGeolocationPermissionForFrame : CoreIPC::Arguments3<uint64_t, uint64_t, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RequestGeolocationPermissionForFrame"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<uint64_t, uint64_t, const WTF::String&> DecodeType;
    RequestGeolocationPermissionForFrame(uint64_t geolocationID, uint64_t frameID, const WTF::String& originIdentifier)
        : CoreIPC::Arguments3<uint64_t, uint64_t, const WTF::String&>(geolocationID, frameID, originIdentifier)
    {
    }
};

struct RequestNotificationPermission : CoreIPC::Arguments2<uint64_t, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RequestNotificationPermission"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, const WTF::String&> DecodeType;
    RequestNotificationPermission(uint64_t requestID, const WTF::String& originIdentifier)
        : CoreIPC::Arguments2<uint64_t, const WTF::String&>(requestID, originIdentifier)
    {
    }
};

struct ShowNotification : CoreIPC::Arguments8<const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ShowNotification"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments8<const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, uint64_t> DecodeType;
    ShowNotification(const WTF::String& title, const WTF::String& body, const WTF::String& iconURL, const WTF::String& tag, const WTF::String& lang, const WTF::String& dir, const WTF::String& originIdentifier, uint64_t notificationID)
        : CoreIPC::Arguments8<const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, uint64_t>(title, body, iconURL, tag, lang, dir, originIdentifier, notificationID)
    {
    }
};

struct CancelNotification : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CancelNotification"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit CancelNotification(uint64_t notificationID)
        : CoreIPC::Arguments1<uint64_t>(notificationID)
    {
    }
};

struct ClearNotifications : CoreIPC::Arguments1<const Vector<uint64_t>&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ClearNotifications"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const Vector<uint64_t>&> DecodeType;
    explicit ClearNotifications(const Vector<uint64_t>& notificationIDs)
        : CoreIPC::Arguments1<const Vector<uint64_t>&>(notificationIDs)
    {
    }
};

struct DidDestroyNotification : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidDestroyNotification"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit DidDestroyNotification(uint64_t notificationID)
        : CoreIPC::Arguments1<uint64_t>(notificationID)
    {
    }
};

#if USE(UNIFIED_TEXT_CHECKING)
struct CheckTextOfParagraph : CoreIPC::Arguments2<const WTF::String&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CheckTextOfParagraph"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<Vector<WebCore::TextCheckingResult>&> Reply;
    typedef CoreIPC::Arguments2<const WTF::String&, uint64_t> DecodeType;
    CheckTextOfParagraph(const WTF::String& text, uint64_t checkingTypes)
        : CoreIPC::Arguments2<const WTF::String&, uint64_t>(text, checkingTypes)
    {
    }
};
#endif

struct CheckSpellingOfString : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CheckSpellingOfString"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments2<int32_t&, int32_t&> Reply;
    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit CheckSpellingOfString(const WTF::String& text)
        : CoreIPC::Arguments1<const WTF::String&>(text)
    {
    }
};

struct CheckGrammarOfString : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CheckGrammarOfString"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments3<Vector<WebCore::GrammarDetail>&, int32_t&, int32_t&> Reply;
    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit CheckGrammarOfString(const WTF::String& text)
        : CoreIPC::Arguments1<const WTF::String&>(text)
    {
    }
};

struct SpellingUIIsShowing : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SpellingUIIsShowing"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments0 DecodeType;
};

struct UpdateSpellingUIWithMisspelledWord : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("UpdateSpellingUIWithMisspelledWord"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit UpdateSpellingUIWithMisspelledWord(const WTF::String& misspelledWord)
        : CoreIPC::Arguments1<const WTF::String&>(misspelledWord)
    {
    }
};

struct UpdateSpellingUIWithGrammarString : CoreIPC::Arguments2<const WTF::String&, const WebCore::GrammarDetail&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("UpdateSpellingUIWithGrammarString"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WTF::String&, const WebCore::GrammarDetail&> DecodeType;
    UpdateSpellingUIWithGrammarString(const WTF::String& badGrammarPhrase, const WebCore::GrammarDetail& grammarDetail)
        : CoreIPC::Arguments2<const WTF::String&, const WebCore::GrammarDetail&>(badGrammarPhrase, grammarDetail)
    {
    }
};

struct GetGuessesForWord : CoreIPC::Arguments2<const WTF::String&, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetGuessesForWord"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<Vector<WTF::String>&> Reply;
    typedef CoreIPC::Arguments2<const WTF::String&, const WTF::String&> DecodeType;
    GetGuessesForWord(const WTF::String& word, const WTF::String& context)
        : CoreIPC::Arguments2<const WTF::String&, const WTF::String&>(word, context)
    {
    }
};

struct LearnWord : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("LearnWord"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit LearnWord(const WTF::String& word)
        : CoreIPC::Arguments1<const WTF::String&>(word)
    {
    }
};

struct IgnoreWord : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("IgnoreWord"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit IgnoreWord(const WTF::String& word)
        : CoreIPC::Arguments1<const WTF::String&>(word)
    {
    }
};

struct RequestCheckingOfString : CoreIPC::Arguments2<uint64_t, const WebCore::TextCheckingRequestData&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RequestCheckingOfString"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, const WebCore::TextCheckingRequestData&> DecodeType;
    RequestCheckingOfString(uint64_t requestID, const WebCore::TextCheckingRequestData& request)
        : CoreIPC::Arguments2<uint64_t, const WebCore::TextCheckingRequestData&>(requestID, request)
    {
    }
};

#if ENABLE(DRAG_SUPPORT)
struct DidPerformDragControllerAction : CoreIPC::Arguments1<const WebCore::DragSession&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidPerformDragControllerAction"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebCore::DragSession&> DecodeType;
    explicit DidPerformDragControllerAction(const WebCore::DragSession& dragSession)
        : CoreIPC::Arguments1<const WebCore::DragSession&>(dragSession)
    {
    }
};
#endif

#if PLATFORM(MAC) && ENABLE(DRAG_SUPPORT)
struct SetDragImage : CoreIPC::Arguments3<const WebCore::IntPoint&, const WebKit::ShareableBitmap::Handle&, bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetDragImage"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<const WebCore::IntPoint&, const WebKit::ShareableBitmap::Handle&, bool> DecodeType;
    SetDragImage(const WebCore::IntPoint& clientPosition, const WebKit::ShareableBitmap::Handle& dragImage, bool linkDrag)
        : CoreIPC::Arguments3<const WebCore::IntPoint&, const WebKit::ShareableBitmap::Handle&, bool>(clientPosition, dragImage, linkDrag)
    {
    }
};
#endif

#if PLATFORM(MAC) && ENABLE(DRAG_SUPPORT)
struct SetPromisedData : CoreIPC::Arguments10<const WTF::String&, const WebKit::SharedMemory::Handle&, uint64_t, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, const WebKit::SharedMemory::Handle&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetPromisedData"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments10<const WTF::String&, const WebKit::SharedMemory::Handle&, uint64_t, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, const WebKit::SharedMemory::Handle&, uint64_t> DecodeType;
    SetPromisedData(const WTF::String& pasteboardName, const WebKit::SharedMemory::Handle& imageHandle, uint64_t imageSize, const WTF::String& filename, const WTF::String& extension, const WTF::String& title, const WTF::String& url, const WTF::String& visibleURL, const WebKit::SharedMemory::Handle& archiveHandle, uint64_t archiveSize)
        : CoreIPC::Arguments10<const WTF::String&, const WebKit::SharedMemory::Handle&, uint64_t, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&, const WebKit::SharedMemory::Handle&, uint64_t>(pasteboardName, imageHandle, imageSize, filename, extension, title, url, visibleURL, archiveHandle, archiveSize)
    {
    }
};
#endif

#if (PLATFORM(QT) || PLATFORM(GTK)) && ENABLE(DRAG_SUPPORT)
struct StartDrag : CoreIPC::Arguments2<const WebCore::DragData&, const WebKit::ShareableBitmap::Handle&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("StartDrag"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WebCore::DragData&, const WebKit::ShareableBitmap::Handle&> DecodeType;
    StartDrag(const WebCore::DragData& dragData, const WebKit::ShareableBitmap::Handle& dragImage)
        : CoreIPC::Arguments2<const WebCore::DragData&, const WebKit::ShareableBitmap::Handle&>(dragData, dragImage)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct DidPerformDictionaryLookup : CoreIPC::Arguments2<const WebKit::AttributedString&, const WebKit::DictionaryPopupInfo&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidPerformDictionaryLookup"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WebKit::AttributedString&, const WebKit::DictionaryPopupInfo&> DecodeType;
    DidPerformDictionaryLookup(const WebKit::AttributedString& text, const WebKit::DictionaryPopupInfo& dictionaryPopupInfo)
        : CoreIPC::Arguments2<const WebKit::AttributedString&, const WebKit::DictionaryPopupInfo&>(text, dictionaryPopupInfo)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct InterpretQueuedKeyEvent : CoreIPC::Arguments1<const WebKit::EditorState&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("InterpretQueuedKeyEvent"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments2<bool&, Vector<WebCore::KeypressCommand>&> Reply;
    typedef CoreIPC::Arguments1<const WebKit::EditorState&> DecodeType;
    explicit InterpretQueuedKeyEvent(const WebKit::EditorState& state)
        : CoreIPC::Arguments1<const WebKit::EditorState&>(state)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct ExecuteSavedCommandBySelector : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ExecuteSavedCommandBySelector"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit ExecuteSavedCommandBySelector(const WTF::String& selector)
        : CoreIPC::Arguments1<const WTF::String&>(selector)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct RegisterWebProcessAccessibilityToken : CoreIPC::Arguments1<const CoreIPC::DataReference&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RegisterWebProcessAccessibilityToken"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const CoreIPC::DataReference&> DecodeType;
    explicit RegisterWebProcessAccessibilityToken(const CoreIPC::DataReference& data)
        : CoreIPC::Arguments1<const CoreIPC::DataReference&>(data)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct PluginFocusOrWindowFocusChanged : CoreIPC::Arguments2<uint64_t, bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("PluginFocusOrWindowFocusChanged"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, bool> DecodeType;
    PluginFocusOrWindowFocusChanged(uint64_t pluginComplexTextInputIdentifier, bool pluginHasFocusAndWindowHasFocus)
        : CoreIPC::Arguments2<uint64_t, bool>(pluginComplexTextInputIdentifier, pluginHasFocusAndWindowHasFocus)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct SetPluginComplexTextInputState : CoreIPC::Arguments2<uint64_t, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetPluginComplexTextInputState"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, uint64_t> DecodeType;
    SetPluginComplexTextInputState(uint64_t pluginComplexTextInputIdentifier, uint64_t complexTextInputState)
        : CoreIPC::Arguments2<uint64_t, uint64_t>(pluginComplexTextInputIdentifier, complexTextInputState)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct GetIsSpeaking : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetIsSpeaking"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if PLATFORM(MAC)
struct Speak : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("Speak"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit Speak(const WTF::String& string)
        : CoreIPC::Arguments1<const WTF::String&>(string)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct StopSpeaking : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("StopSpeaking"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if PLATFORM(MAC)
struct MakeFirstResponder : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("MakeFirstResponder"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if PLATFORM(MAC)
struct SearchWithSpotlight : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SearchWithSpotlight"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit SearchWithSpotlight(const WTF::String& string)
        : CoreIPC::Arguments1<const WTF::String&>(string)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct SearchTheWeb : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SearchTheWeb"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit SearchTheWeb(const WTF::String& string)
        : CoreIPC::Arguments1<const WTF::String&>(string)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct SubstitutionsPanelIsShowing : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SubstitutionsPanelIsShowing"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<bool&> Reply;
    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if PLATFORM(MAC)
struct ShowCorrectionPanel : CoreIPC::Arguments5<int32_t, const WebCore::FloatRect&, const String&, const String&, const Vector<String>&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ShowCorrectionPanel"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments5<int32_t, const WebCore::FloatRect&, const String&, const String&, const Vector<String>&> DecodeType;
    ShowCorrectionPanel(int32_t panelType, const WebCore::FloatRect& boundingBoxOfReplacedString, const String& replacedString, const String& replacementString, const Vector<String>& alternativeReplacementStrings)
        : CoreIPC::Arguments5<int32_t, const WebCore::FloatRect&, const String&, const String&, const Vector<String>&>(panelType, boundingBoxOfReplacedString, replacedString, replacementString, alternativeReplacementStrings)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct DismissCorrectionPanel : CoreIPC::Arguments1<int32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DismissCorrectionPanel"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<int32_t> DecodeType;
    explicit DismissCorrectionPanel(int32_t reason)
        : CoreIPC::Arguments1<int32_t>(reason)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct DismissCorrectionPanelSoon : CoreIPC::Arguments1<int32_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DismissCorrectionPanelSoon"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<String&> Reply;
    typedef CoreIPC::Arguments1<int32_t> DecodeType;
    explicit DismissCorrectionPanelSoon(int32_t reason)
        : CoreIPC::Arguments1<int32_t>(reason)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct RecordAutocorrectionResponse : CoreIPC::Arguments3<int32_t, const String&, const String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RecordAutocorrectionResponse"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<int32_t, const String&, const String&> DecodeType;
    RecordAutocorrectionResponse(int32_t responseType, const String& replacedString, const String& replacementString)
        : CoreIPC::Arguments3<int32_t, const String&, const String&>(responseType, replacedString, replacementString)
    {
    }
};
#endif

#if USE(DICTATION_ALTERNATIVES)
struct ShowDictationAlternativeUI : CoreIPC::Arguments2<const WebCore::FloatRect&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ShowDictationAlternativeUI"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WebCore::FloatRect&, uint64_t> DecodeType;
    ShowDictationAlternativeUI(const WebCore::FloatRect& boundingBoxOfDictatedText, uint64_t dictationContext)
        : CoreIPC::Arguments2<const WebCore::FloatRect&, uint64_t>(boundingBoxOfDictatedText, dictationContext)
    {
    }
};
#endif

#if USE(DICTATION_ALTERNATIVES)
struct RemoveDictationAlternatives : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RemoveDictationAlternatives"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit RemoveDictationAlternatives(uint64_t dictationContext)
        : CoreIPC::Arguments1<uint64_t>(dictationContext)
    {
    }
};
#endif

#if USE(DICTATION_ALTERNATIVES)
struct DictationAlternatives : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DictationAlternatives"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<Vector<String>&> Reply;
    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit DictationAlternatives(uint64_t dictationContext)
        : CoreIPC::Arguments1<uint64_t>(dictationContext)
    {
    }
};
#endif

#if PLUGIN_ARCHITECTURE(X11)
struct CreatePluginContainer : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CreatePluginContainer"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<uint64_t&> Reply;
    typedef CoreIPC::Arguments0 DecodeType;
};
#endif

#if PLUGIN_ARCHITECTURE(X11)
struct WindowedPluginGeometryDidChange : CoreIPC::Arguments3<const WebCore::IntRect&, const WebCore::IntRect&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("WindowedPluginGeometryDidChange"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<const WebCore::IntRect&, const WebCore::IntRect&, uint64_t> DecodeType;
    WindowedPluginGeometryDidChange(const WebCore::IntRect& frameRect, const WebCore::IntRect& clipRect, uint64_t windowID)
        : CoreIPC::Arguments3<const WebCore::IntRect&, const WebCore::IntRect&, uint64_t>(frameRect, clipRect, windowID)
    {
    }
};
#endif

#if ENABLE(MANX_CURSOR_NAVIGATION)
struct SetCursorPosition : CoreIPC::Arguments1<const WebCore::IntPoint&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetCursorPosition"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WebCore::IntPoint&> DecodeType;
    explicit SetCursorPosition(const WebCore::IntPoint& cursorPosition)
        : CoreIPC::Arguments1<const WebCore::IntPoint&>(cursorPosition)
    {
    }
};
#endif

struct SaveRecentSearches : CoreIPC::Arguments2<const WTF::String&, const Vector<String>&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SaveRecentSearches"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WTF::String&, const Vector<String>&> DecodeType;
    SaveRecentSearches(const WTF::String& name, const Vector<String>& searchItems)
        : CoreIPC::Arguments2<const WTF::String&, const Vector<String>&>(name, searchItems)
    {
    }
};

struct LoadRecentSearches : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("LoadRecentSearches"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<Vector<String>&> Reply;
    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit LoadRecentSearches(const WTF::String& name)
        : CoreIPC::Arguments1<const WTF::String&>(name)
    {
    }
};

#if USE(SOUP)
struct DidReceiveURIRequest : CoreIPC::Arguments2<const WTF::String&, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidReceiveURIRequest"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<const WTF::String&, uint64_t> DecodeType;
    DidReceiveURIRequest(const WTF::String& uriString, uint64_t requestID)
        : CoreIPC::Arguments2<const WTF::String&, uint64_t>(uriString, requestID)
    {
    }
};
#endif

struct SavePDFToFileInDownloadsFolder : CoreIPC::Arguments3<const WTF::String&, const WTF::String&, const CoreIPC::DataReference&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SavePDFToFileInDownloadsFolder"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<const WTF::String&, const WTF::String&, const CoreIPC::DataReference&> DecodeType;
    SavePDFToFileInDownloadsFolder(const WTF::String& suggestedFilename, const WTF::String& originatingURLString, const CoreIPC::DataReference& data)
        : CoreIPC::Arguments3<const WTF::String&, const WTF::String&, const CoreIPC::DataReference&>(suggestedFilename, originatingURLString, data)
    {
    }
};

#if PLATFORM(MAC)
struct SavePDFToTemporaryFolderAndOpenWithNativeApplication : CoreIPC::Arguments4<const WTF::String&, const WTF::String&, const CoreIPC::DataReference&, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SavePDFToTemporaryFolderAndOpenWithNativeApplication"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments4<const WTF::String&, const WTF::String&, const CoreIPC::DataReference&, const WTF::String&> DecodeType;
    SavePDFToTemporaryFolderAndOpenWithNativeApplication(const WTF::String& suggestedFilename, const WTF::String& originatingURLString, const CoreIPC::DataReference& data, const WTF::String& pdfUUID)
        : CoreIPC::Arguments4<const WTF::String&, const WTF::String&, const CoreIPC::DataReference&, const WTF::String&>(suggestedFilename, originatingURLString, data, pdfUUID)
    {
    }
};
#endif

#if PLATFORM(MAC)
struct OpenPDFFromTemporaryFolderWithNativeApplication : CoreIPC::Arguments1<const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("OpenPDFFromTemporaryFolderWithNativeApplication"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<const WTF::String&> DecodeType;
    explicit OpenPDFFromTemporaryFolderWithNativeApplication(const WTF::String& pdfUUID)
        : CoreIPC::Arguments1<const WTF::String&>(pdfUUID)
    {
    }
};
#endif

#if ENABLE(NETSCAPE_PLUGIN_API)
struct FindPlugin : CoreIPC::Arguments6<const WTF::String&, uint32_t, const WTF::String&, const WTF::String&, const WTF::String&, bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("FindPlugin"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments4<uint64_t&, WTF::String&, uint32_t&, WTF::String&> Reply;
    typedef CoreIPC::Arguments6<const WTF::String&, uint32_t, const WTF::String&, const WTF::String&, const WTF::String&, bool> DecodeType;
    FindPlugin(const WTF::String& mimeType, uint32_t processType, const WTF::String& urlString, const WTF::String& frameURLString, const WTF::String& pageURLString, bool allowOnlyApplicationPlugins)
        : CoreIPC::Arguments6<const WTF::String&, uint32_t, const WTF::String&, const WTF::String&, const WTF::String&, bool>(mimeType, processType, urlString, frameURLString, pageURLString, allowOnlyApplicationPlugins)
    {
    }
};
#endif

struct DidUpdateInWindowState : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidUpdateInWindowState"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

struct DidSaveToPageCache : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidSaveToPageCache"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

} // namespace WebPageProxy
} // namespace Messages

#endif // WebPageProxyMessages_h
