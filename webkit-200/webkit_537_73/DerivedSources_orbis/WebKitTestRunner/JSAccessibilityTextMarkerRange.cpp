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
#include "AccessibilityTextMarkerRange.h"
#include "JSAccessibilityTextMarkerRange.h"
#include <JavaScriptCore/JSRetainPtr.h>
#include <wtf/GetPtr.h>

namespace WTR {

AccessibilityTextMarkerRange* toAccessibilityTextMarkerRange(JSContextRef context, JSValueRef value)
{
    if (!context || !value || !JSAccessibilityTextMarkerRange::accessibilityTextMarkerRangeClass() || !JSValueIsObjectOfClass(context, value, JSAccessibilityTextMarkerRange::accessibilityTextMarkerRangeClass()))
        return 0;
    return static_cast<AccessibilityTextMarkerRange*>(JSWrapper::unwrap(context, value));
}

JSClassRef JSAccessibilityTextMarkerRange::accessibilityTextMarkerRangeClass()
{
    static JSClassRef jsClass;
    if (!jsClass) {
        JSClassDefinition definition = kJSClassDefinitionEmpty;
        definition.className = "AccessibilityTextMarkerRange";
        definition.parentClass = 0;
        definition.staticValues = staticValues();
        definition.staticFunctions = staticFunctions();
        definition.initialize = initialize;
        definition.finalize = finalize;
        jsClass = JSClassCreate(&definition);
    }
    return jsClass;
}

const JSStaticFunction* JSAccessibilityTextMarkerRange::staticFunctions()
{
    static const JSStaticFunction functions[] = {
        { "isEqual", isEqual, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { 0, 0, 0 }
    };
    return functions;
}

const JSStaticValue* JSAccessibilityTextMarkerRange::staticValues()
{
    return 0;
}

// Functions

JSValueRef JSAccessibilityTextMarkerRange::isEqual(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityTextMarkerRange* impl = toAccessibilityTextMarkerRange(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    AccessibilityTextMarkerRange* otherMarkerRange = argumentCount > 0 ? toAccessibilityTextMarkerRange(context, arguments[0]) : 0;
    return JSValueMakeBoolean(context, impl->isEqual(otherMarkerRange));
}

} // namespace WTR

