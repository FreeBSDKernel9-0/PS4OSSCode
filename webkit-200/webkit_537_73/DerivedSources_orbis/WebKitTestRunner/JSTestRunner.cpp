/*
 * Copyright (C) 2010, 2011, 2012 Apple Inc. All rights reserved.
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
#include "JSTestRunner.h"
#include "TestRunner.h"
#include <JavaScriptCore/JSRetainPtr.h>
#include <wtf/GetPtr.h>

namespace WTR {

TestRunner* toTestRunner(JSContextRef context, JSValueRef value)
{
    if (!context || !value || !JSTestRunner::testRunnerClass() || !JSValueIsObjectOfClass(context, value, JSTestRunner::testRunnerClass()))
        return 0;
    return static_cast<TestRunner*>(JSWrapper::unwrap(context, value));
}

JSClassRef JSTestRunner::testRunnerClass()
{
    static JSClassRef jsClass;
    if (!jsClass) {
        JSClassDefinition definition = kJSClassDefinitionEmpty;
        definition.className = "TestRunner";
        definition.parentClass = 0;
        definition.staticValues = staticValues();
        definition.staticFunctions = staticFunctions();
        definition.initialize = initialize;
        definition.finalize = finalize;
        jsClass = JSClassCreate(&definition);
    }
    return jsClass;
}

const JSStaticFunction* JSTestRunner::staticFunctions()
{
    static const JSStaticFunction functions[] = {
        { "dumpAsText", dumpAsText, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "dumpChildFramesAsText", dumpChildFramesAsText, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "waitForPolicyDelegate", waitForPolicyDelegate, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "waitUntilDone", waitUntilDone, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "notifyDone", notifyDone, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "preciseTime", preciseTime, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "dumpBackForwardList", dumpBackForwardList, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "dumpChildFrameScrollPositions", dumpChildFrameScrollPositions, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "dumpEditingCallbacks", dumpEditingCallbacks, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "dumpSelectionRect", dumpSelectionRect, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "dumpStatusCallbacks", dumpStatusCallbacks, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "dumpTitleChanges", dumpTitleChanges, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "dumpFullScreenCallbacks", dumpFullScreenCallbacks, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "dumpFrameLoadCallbacks", dumpFrameLoadCallbacks, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "dumpProgressFinishedCallback", dumpProgressFinishedCallback, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "dumpResourceLoadCallbacks", dumpResourceLoadCallbacks, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "dumpResourceResponseMIMETypes", dumpResourceResponseMIMETypes, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "dumpWillCacheResponse", dumpWillCacheResponse, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "dumpApplicationCacheDelegateCallbacks", dumpApplicationCacheDelegateCallbacks, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "dumpDatabaseCallbacks", dumpDatabaseCallbacks, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "dumpDOMAsWebArchive", dumpDOMAsWebArchive, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "keepWebHistory", keepWebHistory, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setAcceptsEditing", setAcceptsEditing, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setCanOpenWindows", setCanOpenWindows, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setCloseRemainingWindowsWhenComplete", setCloseRemainingWindowsWhenComplete, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setXSSAuditorEnabled", setXSSAuditorEnabled, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setAllowUniversalAccessFromFileURLs", setAllowUniversalAccessFromFileURLs, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setAllowFileAccessFromFileURLs", setAllowFileAccessFromFileURLs, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setPluginsEnabled", setPluginsEnabled, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setJavaScriptCanAccessClipboard", setJavaScriptCanAccessClipboard, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setPrivateBrowsingEnabled", setPrivateBrowsingEnabled, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setPopupBlockingEnabled", setPopupBlockingEnabled, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setAuthorAndUserStylesEnabled", setAuthorAndUserStylesEnabled, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setCustomPolicyDelegate", setCustomPolicyDelegate, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "addOriginAccessWhitelistEntry", addOriginAccessWhitelistEntry, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "removeOriginAccessWhitelistEntry", removeOriginAccessWhitelistEntry, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setUserStyleSheetEnabled", setUserStyleSheetEnabled, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setUserStyleSheetLocation", setUserStyleSheetLocation, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setSpatialNavigationEnabled", setSpatialNavigationEnabled, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setTabKeyCyclesThroughElements", setTabKeyCyclesThroughElements, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setSerializeHTTPLoads", setSerializeHTTPLoads, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "dispatchPendingLoadRequests", dispatchPendingLoadRequests, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setCacheModel", setCacheModel, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setAsynchronousSpellCheckingEnabled", setAsynchronousSpellCheckingEnabled, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setPrinting", setPrinting, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "clearBackForwardList", clearBackForwardList, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "execCommand", execCommand, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "isCommandEnabled", isCommandEnabled, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "windowCount", windowCount, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "testRepaint", testRepaint, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "repaintSweepHorizontally", repaintSweepHorizontally, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "display", display, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "isPageBoxVisible", isPageBoxVisible, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setValueForUser", setValueForUser, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "addUserScript", addUserScript, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "addUserStyleSheet", addUserStyleSheet, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "clearAllDatabases", clearAllDatabases, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setDatabaseQuota", setDatabaseQuota, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "pathToLocalResource", pathToLocalResource, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "clearAllApplicationCaches", clearAllApplicationCaches, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setAppCacheMaximumSize", setAppCacheMaximumSize, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "applicationCacheDiskUsageForOrigin", applicationCacheDiskUsageForOrigin, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "clearApplicationCacheForOrigin", clearApplicationCacheForOrigin, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setApplicationCacheOriginQuota", setApplicationCacheOriginQuota, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "disallowIncreaseForApplicationCacheQuota", disallowIncreaseForApplicationCacheQuota, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "originsWithApplicationCache", originsWithApplicationCache, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "findString", findString, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "evaluateScriptInIsolatedWorld", evaluateScriptInIsolatedWorld, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "showWebInspector", showWebInspector, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "closeWebInspector", closeWebInspector, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "evaluateInWebInspector", evaluateInWebInspector, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setPOSIXLocale", setPOSIXLocale, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setTextDirection", setTextDirection, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setWillSendRequestReturnsNull", setWillSendRequestReturnsNull, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setWillSendRequestReturnsNullOnRedirect", setWillSendRequestReturnsNullOnRedirect, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setShouldStayOnPageAfterHandlingBeforeUnload", setShouldStayOnPageAfterHandlingBeforeUnload, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setDefersLoading", setDefersLoading, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setStopProvisionalFrameLoads", setStopProvisionalFrameLoads, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "addChromeInputField", addChromeInputField, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "removeChromeInputField", removeChromeInputField, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "focusWebView", focusWebView, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setBackingScaleFactor", setBackingScaleFactor, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setWindowIsKey", setWindowIsKey, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setAlwaysAcceptCookies", setAlwaysAcceptCookies, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "overridePreference", overridePreference, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setPageVisibility", setPageVisibility, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "resetPageVisibility", resetPageVisibility, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setHasCustomFullScreenBehavior", setHasCustomFullScreenBehavior, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "grantWebNotificationPermission", grantWebNotificationPermission, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "denyWebNotificationPermission", denyWebNotificationPermission, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "removeAllWebNotificationPermissions", removeAllWebNotificationPermissions, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "simulateWebNotificationClick", simulateWebNotificationClick, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setGeolocationPermission", setGeolocationPermission, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setMockGeolocationPosition", setMockGeolocationPosition, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setMockGeolocationPositionUnavailableError", setMockGeolocationPositionUnavailableError, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setAudioResult", setAudioResult, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "callShouldCloseOnWebView", callShouldCloseOnWebView, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "queueBackNavigation", queueBackNavigation, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "queueForwardNavigation", queueForwardNavigation, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "queueLoad", queueLoad, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "queueLoadHTMLString", queueLoadHTMLString, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "queueReload", queueReload, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "queueLoadingScript", queueLoadingScript, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "queueNonLoadingScript", queueNonLoadingScript, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setHandlesAuthenticationChallenges", setHandlesAuthenticationChallenges, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setAuthenticationUsername", setAuthenticationUsername, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setAuthenticationPassword", setAuthenticationPassword, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { 0, 0, 0 }
    };
    return functions;
}

const JSStaticValue* JSTestRunner::staticValues()
{
    static const JSStaticValue values[] = {
        { "globalFlag", globalFlag, setGlobalFlag, kJSPropertyAttributeDontDelete },
        { "platformName", platformName, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "secureEventInputIsEnabled", secureEventInputIsEnabled, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { 0, 0, 0, 0 }
    };
    return values;
}

// Functions

JSValueRef JSTestRunner::dumpAsText(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool dumpPixels = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->dumpAsText(dumpPixels);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::dumpChildFramesAsText(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->dumpChildFramesAsText();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::waitForPolicyDelegate(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->waitForPolicyDelegate();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::waitUntilDone(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->waitUntilDone();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::notifyDone(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->notifyDone();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::preciseTime(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeNumber(context, impl->preciseTime());
}

JSValueRef JSTestRunner::dumpBackForwardList(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->dumpBackForwardList();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::dumpChildFrameScrollPositions(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->dumpChildFrameScrollPositions();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::dumpEditingCallbacks(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->dumpEditingCallbacks();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::dumpSelectionRect(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->dumpSelectionRect();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::dumpStatusCallbacks(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->dumpStatusCallbacks();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::dumpTitleChanges(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->dumpTitleChanges();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::dumpFullScreenCallbacks(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->dumpFullScreenCallbacks();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::dumpFrameLoadCallbacks(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->dumpFrameLoadCallbacks();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::dumpProgressFinishedCallback(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->dumpProgressFinishedCallback();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::dumpResourceLoadCallbacks(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->dumpResourceLoadCallbacks();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::dumpResourceResponseMIMETypes(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->dumpResourceResponseMIMETypes();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::dumpWillCacheResponse(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->dumpWillCacheResponse();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::dumpApplicationCacheDelegateCallbacks(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->dumpApplicationCacheDelegateCallbacks();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::dumpDatabaseCallbacks(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->dumpDatabaseCallbacks();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::dumpDOMAsWebArchive(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->dumpDOMAsWebArchive();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::keepWebHistory(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->keepWebHistory();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setAcceptsEditing(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool value = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setAcceptsEditing(value);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setCanOpenWindows(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool value = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setCanOpenWindows(value);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setCloseRemainingWindowsWhenComplete(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool value = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setCloseRemainingWindowsWhenComplete(value);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setXSSAuditorEnabled(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool value = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setXSSAuditorEnabled(value);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setAllowUniversalAccessFromFileURLs(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool value = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setAllowUniversalAccessFromFileURLs(value);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setAllowFileAccessFromFileURLs(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool value = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setAllowFileAccessFromFileURLs(value);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setPluginsEnabled(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool value = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setPluginsEnabled(value);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setJavaScriptCanAccessClipboard(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool value = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setJavaScriptCanAccessClipboard(value);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setPrivateBrowsingEnabled(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool value = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setPrivateBrowsingEnabled(value);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setPopupBlockingEnabled(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool value = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setPopupBlockingEnabled(value);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setAuthorAndUserStylesEnabled(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool value = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setAuthorAndUserStylesEnabled(value);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setCustomPolicyDelegate(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool enabled = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    bool permissive = argumentCount > 1 && JSValueToBoolean(context, arguments[1]);
    impl->setCustomPolicyDelegate(enabled, permissive);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::addOriginAccessWhitelistEntry(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> sourceOrigin = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    JSRetainPtr<JSStringRef> destinationProtocol = argumentCount > 1 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[1], 0)) : JSRetainPtr<JSStringRef>();
    JSRetainPtr<JSStringRef> destinationHost = argumentCount > 2 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[2], 0)) : JSRetainPtr<JSStringRef>();
    bool allowDestinationSubdomains = argumentCount > 3 && JSValueToBoolean(context, arguments[3]);
    impl->addOriginAccessWhitelistEntry(sourceOrigin.get(), destinationProtocol.get(), destinationHost.get(), allowDestinationSubdomains);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::removeOriginAccessWhitelistEntry(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> sourceOrigin = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    JSRetainPtr<JSStringRef> destinationProtocol = argumentCount > 1 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[1], 0)) : JSRetainPtr<JSStringRef>();
    JSRetainPtr<JSStringRef> destinationHost = argumentCount > 2 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[2], 0)) : JSRetainPtr<JSStringRef>();
    bool allowDestinationSubdomains = argumentCount > 3 && JSValueToBoolean(context, arguments[3]);
    impl->removeOriginAccessWhitelistEntry(sourceOrigin.get(), destinationProtocol.get(), destinationHost.get(), allowDestinationSubdomains);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setUserStyleSheetEnabled(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool value = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setUserStyleSheetEnabled(value);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setUserStyleSheetLocation(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> location = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    impl->setUserStyleSheetLocation(location.get());

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setSpatialNavigationEnabled(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool value = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setSpatialNavigationEnabled(value);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setTabKeyCyclesThroughElements(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool enabled = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setTabKeyCyclesThroughElements(enabled);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setSerializeHTTPLoads(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->setSerializeHTTPLoads();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::dispatchPendingLoadRequests(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->dispatchPendingLoadRequests();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setCacheModel(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double model = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    impl->setCacheModel(model);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setAsynchronousSpellCheckingEnabled(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool value = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setAsynchronousSpellCheckingEnabled(value);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setPrinting(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->setPrinting();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::clearBackForwardList(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->clearBackForwardList();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::execCommand(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> name = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    JSRetainPtr<JSStringRef> argument = argumentCount > 1 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[1], 0)) : JSRetainPtr<JSStringRef>();
    impl->execCommand(name.get(), argument.get());

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::isCommandEnabled(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> name = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    return JSValueMakeBoolean(context, impl->isCommandEnabled(name.get()));
}

JSValueRef JSTestRunner::windowCount(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeNumber(context, impl->windowCount());
}

JSValueRef JSTestRunner::testRepaint(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->testRepaint();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::repaintSweepHorizontally(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->repaintSweepHorizontally();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::display(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->display();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::isPageBoxVisible(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double pageIndex = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    return JSValueMakeBoolean(context, impl->isPageBoxVisible(pageIndex));
}

JSValueRef JSTestRunner::setValueForUser(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSValueRef element = argumentCount > 0 ? arguments[0] : JSValueMakeUndefined(context);
    JSRetainPtr<JSStringRef> value = argumentCount > 1 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[1], 0)) : JSRetainPtr<JSStringRef>();
    impl->setValueForUser(context, element, value.get());

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::addUserScript(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> source = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    bool runAtStart = argumentCount > 1 && JSValueToBoolean(context, arguments[1]);
    bool allFrames = argumentCount > 2 && JSValueToBoolean(context, arguments[2]);
    impl->addUserScript(source.get(), runAtStart, allFrames);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::addUserStyleSheet(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> source = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    bool allFrames = argumentCount > 1 && JSValueToBoolean(context, arguments[1]);
    impl->addUserStyleSheet(source.get(), allFrames);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::clearAllDatabases(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->clearAllDatabases();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setDatabaseQuota(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double quota = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    impl->setDatabaseQuota(quota);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::pathToLocalResource(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> url = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    return JSValueMakeStringOrNull(context, impl->pathToLocalResource(url.get()).get());
}

JSValueRef JSTestRunner::clearAllApplicationCaches(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->clearAllApplicationCaches();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setAppCacheMaximumSize(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double size = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    impl->setAppCacheMaximumSize(size);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::applicationCacheDiskUsageForOrigin(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> origin = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    return JSValueMakeNumber(context, impl->applicationCacheDiskUsageForOrigin(origin.get()));
}

JSValueRef JSTestRunner::clearApplicationCacheForOrigin(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> name = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    impl->clearApplicationCacheForOrigin(name.get());

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setApplicationCacheOriginQuota(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double bytes = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    impl->setApplicationCacheOriginQuota(bytes);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::disallowIncreaseForApplicationCacheQuota(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->disallowIncreaseForApplicationCacheQuota();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::originsWithApplicationCache(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return impl->originsWithApplicationCache();
}

JSValueRef JSTestRunner::findString(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> target = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    JSValueRef optionsArray = argumentCount > 1 ? arguments[1] : JSValueMakeUndefined(context);
    return JSValueMakeBoolean(context, impl->findString(target.get(), optionsArray));
}

JSValueRef JSTestRunner::evaluateScriptInIsolatedWorld(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double worldID = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    JSRetainPtr<JSStringRef> script = argumentCount > 1 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[1], 0)) : JSRetainPtr<JSStringRef>();
    impl->evaluateScriptInIsolatedWorld(context, worldID, script.get());

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::showWebInspector(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->showWebInspector();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::closeWebInspector(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->closeWebInspector();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::evaluateInWebInspector(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double callID = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    JSRetainPtr<JSStringRef> script = argumentCount > 1 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[1], 0)) : JSRetainPtr<JSStringRef>();
    impl->evaluateInWebInspector(callID, script.get());

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setPOSIXLocale(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> locale = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    impl->setPOSIXLocale(locale.get());

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setTextDirection(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> direction = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    impl->setTextDirection(direction.get());

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setWillSendRequestReturnsNull(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool flag = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setWillSendRequestReturnsNull(flag);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setWillSendRequestReturnsNullOnRedirect(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool flag = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setWillSendRequestReturnsNullOnRedirect(flag);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setShouldStayOnPageAfterHandlingBeforeUnload(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool flag = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setShouldStayOnPageAfterHandlingBeforeUnload(flag);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setDefersLoading(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool flag = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setDefersLoading(flag);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setStopProvisionalFrameLoads(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->setStopProvisionalFrameLoads();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::addChromeInputField(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSValueRef callback = argumentCount > 0 ? arguments[0] : JSValueMakeUndefined(context);
    impl->addChromeInputField(callback);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::removeChromeInputField(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSValueRef callback = argumentCount > 0 ? arguments[0] : JSValueMakeUndefined(context);
    impl->removeChromeInputField(callback);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::focusWebView(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSValueRef callback = argumentCount > 0 ? arguments[0] : JSValueMakeUndefined(context);
    impl->focusWebView(callback);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setBackingScaleFactor(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double backingScaleFactor = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    JSValueRef callback = argumentCount > 1 ? arguments[1] : JSValueMakeUndefined(context);
    impl->setBackingScaleFactor(backingScaleFactor, callback);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setWindowIsKey(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool isKey = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setWindowIsKey(isKey);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setAlwaysAcceptCookies(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool accept = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setAlwaysAcceptCookies(accept);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::overridePreference(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> preference = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    JSRetainPtr<JSStringRef> value = argumentCount > 1 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[1], 0)) : JSRetainPtr<JSStringRef>();
    impl->overridePreference(preference.get(), value.get());

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setPageVisibility(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> state = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    impl->setPageVisibility(state.get());

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::resetPageVisibility(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->resetPageVisibility();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setHasCustomFullScreenBehavior(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool value = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setHasCustomFullScreenBehavior(value);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::grantWebNotificationPermission(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> origin = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    impl->grantWebNotificationPermission(origin.get());

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::denyWebNotificationPermission(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> origin = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    impl->denyWebNotificationPermission(origin.get());

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::removeAllWebNotificationPermissions(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->removeAllWebNotificationPermissions();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::simulateWebNotificationClick(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSValueRef notification = argumentCount > 0 ? arguments[0] : JSValueMakeUndefined(context);
    impl->simulateWebNotificationClick(notification);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setGeolocationPermission(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool value = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setGeolocationPermission(value);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setMockGeolocationPosition(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double latitude = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    double longitude = argumentCount > 1 ? JSValueToNumber(context, arguments[1], 0) : 0;
    double accuracy = argumentCount > 2 ? JSValueToNumber(context, arguments[2], 0) : 0;
    JSValueRef altitude = argumentCount > 3 ? arguments[3] : JSValueMakeUndefined(context);
    JSValueRef altitudeAccuracy = argumentCount > 4 ? arguments[4] : JSValueMakeUndefined(context);
    JSValueRef heading = argumentCount > 5 ? arguments[5] : JSValueMakeUndefined(context);
    JSValueRef speed = argumentCount > 6 ? arguments[6] : JSValueMakeUndefined(context);
    impl->setMockGeolocationPosition(latitude, longitude, accuracy, altitude, altitudeAccuracy, heading, speed);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setMockGeolocationPositionUnavailableError(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> errorMessage = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    impl->setMockGeolocationPositionUnavailableError(errorMessage.get());

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setAudioResult(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSValueRef data = argumentCount > 0 ? arguments[0] : JSValueMakeUndefined(context);
    impl->setAudioResult(context, data);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::callShouldCloseOnWebView(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->callShouldCloseOnWebView());
}

JSValueRef JSTestRunner::queueBackNavigation(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double howFarBackward = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    impl->queueBackNavigation(howFarBackward);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::queueForwardNavigation(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double howFarForward = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    impl->queueForwardNavigation(howFarForward);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::queueLoad(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> url = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    JSRetainPtr<JSStringRef> target = argumentCount > 1 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[1], 0)) : JSRetainPtr<JSStringRef>();
    impl->queueLoad(url.get(), target.get());

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::queueLoadHTMLString(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> content = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    JSRetainPtr<JSStringRef> baseURL = argumentCount > 1 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[1], 0)) : JSRetainPtr<JSStringRef>();
    JSRetainPtr<JSStringRef> unreachableURL = argumentCount > 2 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[2], 0)) : JSRetainPtr<JSStringRef>();
    impl->queueLoadHTMLString(content.get(), baseURL.get(), unreachableURL.get());

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::queueReload(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->queueReload();

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::queueLoadingScript(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> script = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    impl->queueLoadingScript(script.get());

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::queueNonLoadingScript(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> script = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    impl->queueNonLoadingScript(script.get());

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setHandlesAuthenticationChallenges(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    bool value = argumentCount > 0 && JSValueToBoolean(context, arguments[0]);
    impl->setHandlesAuthenticationChallenges(value);

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setAuthenticationUsername(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> username = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    impl->setAuthenticationUsername(username.get());

    return JSValueMakeUndefined(context);
}

JSValueRef JSTestRunner::setAuthenticationPassword(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> password = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    impl->setAuthenticationPassword(password.get());

    return JSValueMakeUndefined(context);
}

// Attributes

JSValueRef JSTestRunner::globalFlag(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->globalFlag());
}

bool JSTestRunner::setGlobalFlag(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef value, JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, object);
    if (!impl)
        return false;

    impl->setGlobalFlag(JSValueToBoolean(context, value));

    return true;
}

JSValueRef JSTestRunner::platformName(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->platformName().get());
}

JSValueRef JSTestRunner::secureEventInputIsEnabled(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    TestRunner* impl = toTestRunner(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->secureEventInputIsEnabled());
}

} // namespace WTR

