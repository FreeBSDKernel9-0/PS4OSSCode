/*
 * Copyright (C) 2010, 2011 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "config.h"
#include "EventSendingController.h"
#include "JSEventSendingController.h"
#include <JavaScriptCore/JSRetainPtr.h>
#include <wtf/GetPtr.h>

namespace WTR {

EventSendingController* toEventSendingController(JSContextRef context, JSValueRef value)
{
    if (!context || !value || !JSEventSendingController::eventSendingControllerClass() || !JSValueIsObjectOfClass(context, value, JSEventSendingController::eventSendingControllerClass()))
        return 0;
    return static_cast<EventSendingController*>(JSWrapper::unwrap(context, value));
}

JSClassRef JSEventSendingController::eventSendingControllerClass()
{
    static JSClassRef jsClass;
    if (!jsClass) {
        JSClassDefinition definition = kJSClassDefinitionEmpty;
        definition.className = "EventSendingController";
        definition.parentClass = 0;
        definition.staticValues = staticValues();
        definition.staticFunctions = staticFunctions();
        definition.initialize = initialize;
        definition.finalize = finalize;
        jsClass = JSClassCreate(&definition);
    }
    return jsClass;
}

const JSStaticFunction* JSEventSendingController::staticFunctions()
{
    static const JSStaticFunction functions[] = {
        { "mouseDown", mouseDown, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "mouseUp", mouseUp, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "mouseMoveTo", mouseMoveTo, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "mouseScrollBy", mouseScrollBy, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "continuousMouseScrollBy", continuousMouseScrollBy, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "contextClick", contextClick, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "scheduleAsynchronousClick", scheduleAsynchronousClick, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "leapForward", leapForward, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "keyDown", keyDown, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "scheduleAsynchronousKeyDown", scheduleAsynchronousKeyDown, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "textZoomIn", textZoomIn, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "textZoomOut", textZoomOut, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "zoomPageIn", zoomPageIn, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "zoomPageOut", zoomPageOut, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "scalePageBy", scalePageBy, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { 0, 0, 0 }
    };
    return functions;
}

const JSStaticValue* JSEventSendingController::staticValues()
{
    return 0;
}

// Functions

JSValueRef JSEventSendingController::mouseDown(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    EventSendingController* impl = toEventSendingController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double buttonNumber = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    JSValueRef modifierArray = argumentCount > 1 ? arguments[1] : JSValueMakeUndefined(context);
    impl->mouseDown(buttonNumber, modifierArray);

    return JSValueMakeUndefined(context);
}

JSValueRef JSEventSendingController::mouseUp(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    EventSendingController* impl = toEventSendingController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double buttonNumber = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    JSValueRef modifierArray = argumentCount > 1 ? arguments[1] : JSValueMakeUndefined(context);
    impl->mouseUp(buttonNumber, modifierArray);

    return JSValueMakeUndefined(context);
}

JSValueRef JSEventSendingController::mouseMoveTo(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    EventSendingController* impl = toEventSendingController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double x = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    double y = argumentCount > 1 ? JSValueToNumber(context, arguments[1], 0) : 0;
    impl->mouseMoveTo(x, y);

    return JSValueMakeUndefined(context);
}

JSValueRef JSEventSendingController::mouseScrollBy(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    EventSendingController* impl = toEventSendingController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double x = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    double y = argumentCount > 1 ? JSValueToNumber(context, arguments[1], 0) : 0;
    impl->mouseScrollBy(x, y);

    return JSValueMakeUndefined(context);
}

JSValueRef JSEventSendingController::continuousMouseScrollBy(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    EventSendingController* impl = toEventSendingController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double x = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    double y = argumentCount > 1 ? JSValueToNumber(context, arguments[1], 0) : 0;
    bool paged = argumentCount > 2 && JSValueToBoolean(context, arguments[2]);
    impl->continuousMouseScrollBy(x, y, paged);

    return JSValueMakeUndefined(context);
}

JSValueRef JSEventSendingController::contextClick(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    EventSendingController* impl = toEventSendingController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return impl->contextClick();
}

JSValueRef JSEventSendingController::scheduleAsynchronousClick(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    EventSendingController* impl = toEventSendingController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->scheduleAsynchronousClick();

    return JSValueMakeUndefined(context);
}

JSValueRef JSEventSendingController::leapForward(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    EventSendingController* impl = toEventSendingController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double milliseconds = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    impl->leapForward(milliseconds);

    return JSValueMakeUndefined(context);
}

JSValueRef JSEventSendingController::keyDown(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    EventSendingController* impl = toEventSendingController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> key = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    JSValueRef modifierArray = argumentCount > 1 ? arguments[1] : JSValueMakeUndefined(context);
    double location = argumentCount > 2 ? JSValueToNumber(context, arguments[2], 0) : 0;
    impl->keyDown(key.get(), modifierArray, location);

    return JSValueMakeUndefined(context);
}

JSValueRef JSEventSendingController::scheduleAsynchronousKeyDown(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    EventSendingController* impl = toEventSendingController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> key = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    impl->scheduleAsynchronousKeyDown(key.get());

    return JSValueMakeUndefined(context);
}

JSValueRef JSEventSendingController::textZoomIn(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    EventSendingController* impl = toEventSendingController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->textZoomIn();

    return JSValueMakeUndefined(context);
}

JSValueRef JSEventSendingController::textZoomOut(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    EventSendingController* impl = toEventSendingController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->textZoomOut();

    return JSValueMakeUndefined(context);
}

JSValueRef JSEventSendingController::zoomPageIn(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    EventSendingController* impl = toEventSendingController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->zoomPageIn();

    return JSValueMakeUndefined(context);
}

JSValueRef JSEventSendingController::zoomPageOut(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    EventSendingController* impl = toEventSendingController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->zoomPageOut();

    return JSValueMakeUndefined(context);
}

JSValueRef JSEventSendingController::scalePageBy(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    EventSendingController* impl = toEventSendingController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double scale = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    double x = argumentCount > 1 ? JSValueToNumber(context, arguments[1], 0) : 0;
    double y = argumentCount > 2 ? JSValueToNumber(context, arguments[2], 0) : 0;
    impl->scalePageBy(scale, x, y);

    return JSValueMakeUndefined(context);
}

} // namespace WTR

