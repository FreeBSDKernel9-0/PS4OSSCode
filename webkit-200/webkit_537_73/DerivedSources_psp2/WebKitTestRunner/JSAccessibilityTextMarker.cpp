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
#include "AccessibilityTextMarker.h"
#include "JSAccessibilityTextMarker.h"
#include <JavaScriptCore/JSRetainPtr.h>
#include <wtf/GetPtr.h>

namespace WTR {

AccessibilityTextMarker* toAccessibilityTextMarker(JSContextRef context, JSValueRef value)
{
    if (!context || !value || !JSAccessibilityTextMarker::accessibilityTextMarkerClass() || !JSValueIsObjectOfClass(context, value, JSAccessibilityTextMarker::accessibilityTextMarkerClass()))
        return 0;
    return static_cast<AccessibilityTextMarker*>(JSWrapper::unwrap(context, value));
}

JSClassRef JSAccessibilityTextMarker::accessibilityTextMarkerClass()
{
    static JSClassRef jsClass;
    if (!jsClass) {
        JSClassDefinition definition = kJSClassDefinitionEmpty;
        definition.className = "AccessibilityTextMarker";
        definition.parentClass = 0;
        definition.staticValues = staticValues();
        definition.staticFunctions = staticFunctions();
        definition.initialize = initialize;
        definition.finalize = finalize;
        jsClass = JSClassCreate(&definition);
    }
    return jsClass;
}

const JSStaticFunction* JSAccessibilityTextMarker::staticFunctions()
{
    static const JSStaticFunction functions[] = {
        { "isEqual", isEqual, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { 0, 0, 0 }
    };
    return functions;
}

const JSStaticValue* JSAccessibilityTextMarker::staticValues()
{
    return 0;
}

// Functions

JSValueRef JSAccessibilityTextMarker::isEqual(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityTextMarker* impl = toAccessibilityTextMarker(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    AccessibilityTextMarker* otherMarker = argumentCount > 0 ? toAccessibilityTextMarker(context, arguments[0]) : 0;
    return JSValueMakeBoolean(context, impl->isEqual(otherMarker));
}

} // namespace WTR

