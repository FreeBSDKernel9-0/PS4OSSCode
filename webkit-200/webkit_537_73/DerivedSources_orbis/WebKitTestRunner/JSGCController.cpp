/*
 * Copyright (C) 2010 Apple Inc. All rights reserved.
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
#include "GCController.h"
#include "JSGCController.h"
#include <JavaScriptCore/JSRetainPtr.h>
#include <wtf/GetPtr.h>

namespace WTR {

GCController* toGCController(JSContextRef context, JSValueRef value)
{
    if (!context || !value || !JSGCController::gCControllerClass() || !JSValueIsObjectOfClass(context, value, JSGCController::gCControllerClass()))
        return 0;
    return static_cast<GCController*>(JSWrapper::unwrap(context, value));
}

JSClassRef JSGCController::gCControllerClass()
{
    static JSClassRef jsClass;
    if (!jsClass) {
        JSClassDefinition definition = kJSClassDefinitionEmpty;
        definition.className = "GCController";
        definition.parentClass = 0;
        definition.staticValues = staticValues();
        definition.staticFunctions = staticFunctions();
        definition.initialize = initialize;
        definition.finalize = finalize;
        jsClass = JSClassCreate(&definition);
    }
    return jsClass;
}

const JSStaticFunction* JSGCController::staticFunctions()
{
    static const JSStaticFunction functions[] = {
        { "collect", collect, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "collectOnAlternateThread", collectOnAlternateThread, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "getJSObjectCount", getJSObjectCount, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { 0, 0, 0 }
    };
    return functions;
}

const JSStaticValue* JSGCController::staticValues()
{
    return 0;
}

// Functions

JSValueRef JSGCController::collect(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    GCController* impl = toGCController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->collect();

    return JSValueMakeUndefined(context);
}

JSValueRef JSGCController::collectOnAlternateThread(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    GCController* impl = toGCController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool waitUntilDone = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->collectOnAlternateThread(waitUntilDone);

    return JSValueMakeUndefined(context);
}

JSValueRef JSGCController::getJSObjectCount(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    GCController* impl = toGCController(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeNumber(context, impl->getJSObjectCount());
}

} // namespace WTR

