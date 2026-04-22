/*
 * Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies)
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
#include "JSTextInputController.h"
#include "TextInputController.h"
#include <JavaScriptCore/JSRetainPtr.h>
#include <wtf/GetPtr.h>

namespace WTR {

TextInputController* toTextInputController(JSContextRef context, JSValueRef value)
{
    if (!context || !value || !JSTextInputController::textInputControllerClass() || !JSValueIsObjectOfClass(context, value, JSTextInputController::textInputControllerClass()))
        return 0;
    return static_cast<TextInputController*>(JSWrapper::unwrap(context, value));
}

JSClassRef JSTextInputController::textInputControllerClass()
{
    static JSClassRef jsClass;
    if (!jsClass) {
        JSClassDefinition definition = kJSClassDefinitionEmpty;
        definition.className = "TextInputController";
        definition.parentClass = 0;
        definition.staticValues = staticValues();
        definition.staticFunctions = staticFunctions();
        definition.initialize = initialize;
        definition.finalize = finalize;
        jsClass = JSClassCreate(&definition);
    }
    return jsClass;
}

const JSStaticFunction* JSTextInputController::staticFunctions()
{
    static const JSStaticFunction functions[] = {
        { "setMarkedText", setMarkedText, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "hasMarkedText", hasMarkedText, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "unmarkText", unmarkText, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "insertText", insertText, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { 0, 0, 0 }
    };
    return functions;
}

const JSStaticValue* JSTextInputController::staticValues()
{
    return 0;
}

// Functions

JSValueRef JSTextInputController::setMarkedText(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TextInputController* impl = toTextInputController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> string = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    double from = argumentCount > 1 ? JSValueToNumber(context, arguments[1], 0) : 0;
    double length = argumentCount > 2 ? JSValueToNumber(context, arguments[2], 0) : 0;
    impl->setMarkedText(string.get(), from, length);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTextInputController::hasMarkedText(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TextInputController* impl = toTextInputController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->hasMarkedText());
}

JSValueRef JSTextInputController::unmarkText(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TextInputController* impl = toTextInputController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->unmarkText();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTextInputController::insertText(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TextInputController* impl = toTextInputController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> string = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    impl->insertText(string.get());

    return JSValueMakeUndefined(context);
}

} // namespace WTR

