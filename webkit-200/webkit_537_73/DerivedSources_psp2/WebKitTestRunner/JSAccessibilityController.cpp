/*
 * Copyright (C) 2011 Apple Inc. All rights reserved.
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
#include "AccessibilityController.h"
#include "AccessibilityUIElement.h"
#include "JSAccessibilityController.h"
#include "JSAccessibilityUIElement.h"
#include <JavaScriptCore/JSRetainPtr.h>
#include <wtf/GetPtr.h>

namespace WTR {

AccessibilityController* toAccessibilityController(JSContextRef context, JSValueRef value)
{
    if (!context || !value || !JSAccessibilityController::accessibilityControllerClass() || !JSValueIsObjectOfClass(context, value, JSAccessibilityController::accessibilityControllerClass()))
        return 0;
    return static_cast<AccessibilityController*>(JSWrapper::unwrap(context, value));
}

JSClassRef JSAccessibilityController::accessibilityControllerClass()
{
    static JSClassRef jsClass;
    if (!jsClass) {
        JSClassDefinition definition = kJSClassDefinitionEmpty;
        definition.className = "AccessibilityController";
        definition.parentClass = 0;
        definition.staticValues = staticValues();
        definition.staticFunctions = staticFunctions();
        definition.initialize = initialize;
        definition.finalize = finalize;
        jsClass = JSClassCreate(&definition);
    }
    return jsClass;
}

const JSStaticFunction* JSAccessibilityController::staticFunctions()
{
    static const JSStaticFunction functions[] = {
        { "elementAtPoint", elementAtPoint, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "accessibleElementById", accessibleElementById, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "addNotificationListener", addNotificationListener, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "removeNotificationListener", removeNotificationListener, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "logFocusEvents", logFocusEvents, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "logValueChangeEvents", logValueChangeEvents, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "logScrollingStartEvents", logScrollingStartEvents, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "logAccessibilityEvents", logAccessibilityEvents, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "resetToConsistentState", resetToConsistentState, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { 0, 0, 0 }
    };
    return functions;
}

const JSStaticValue* JSAccessibilityController::staticValues()
{
    static const JSStaticValue values[] = {
        { "rootElement", rootElement, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "focusedElement", focusedElement, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { 0, 0, 0, 0 }
    };
    return values;
}

// Functions

JSValueRef JSAccessibilityController::elementAtPoint(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityController* impl = toAccessibilityController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double x = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    double y = argumentCount > 1 ? JSValueToNumber(context, arguments[1], 0) : 0;
    return toJS(context, WTF::getPtr(impl->elementAtPoint(x, y)));
}

JSValueRef JSAccessibilityController::accessibleElementById(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityController* impl = toAccessibilityController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> id = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    return toJS(context, WTF::getPtr(impl->accessibleElementById(id.get())));
}

JSValueRef JSAccessibilityController::addNotificationListener(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityController* impl = toAccessibilityController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSValueRef functionCallback = argumentCount > 0 ? arguments[0] : JSValueMakeUndefined(context);
    return JSValueMakeBoolean(context, impl->addNotificationListener(functionCallback));
}

JSValueRef JSAccessibilityController::removeNotificationListener(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityController* impl = toAccessibilityController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->removeNotificationListener());
}

JSValueRef JSAccessibilityController::logFocusEvents(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityController* impl = toAccessibilityController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->logFocusEvents();

    return JSValueMakeUndefined(context);
}

JSValueRef JSAccessibilityController::logValueChangeEvents(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityController* impl = toAccessibilityController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->logValueChangeEvents();

    return JSValueMakeUndefined(context);
}

JSValueRef JSAccessibilityController::logScrollingStartEvents(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityController* impl = toAccessibilityController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->logScrollingStartEvents();

    return JSValueMakeUndefined(context);
}

JSValueRef JSAccessibilityController::logAccessibilityEvents(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityController* impl = toAccessibilityController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->logAccessibilityEvents();

    return JSValueMakeUndefined(context);
}

JSValueRef JSAccessibilityController::resetToConsistentState(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityController* impl = toAccessibilityController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->resetToConsistentState();

    return JSValueMakeUndefined(context);
}

// Attributes

JSValueRef JSAccessibilityController::rootElement(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityController* impl = toAccessibilityController(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return toJS(context, WTF::getPtr(impl->rootElement()));
}

JSValueRef JSAccessibilityController::focusedElement(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityController* impl = toAccessibilityController(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return toJS(context, WTF::getPtr(impl->focusedElement()));
}

} // namespace WTR

