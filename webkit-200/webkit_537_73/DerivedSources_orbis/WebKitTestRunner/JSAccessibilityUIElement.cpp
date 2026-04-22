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
#include "AccessibilityTextMarkerRange.h"
#include "AccessibilityUIElement.h"
#include "JSAccessibilityTextMarker.h"
#include "JSAccessibilityTextMarkerRange.h"
#include "JSAccessibilityUIElement.h"
#include <JavaScriptCore/JSRetainPtr.h>
#include <wtf/GetPtr.h>

namespace WTR {

AccessibilityUIElement* toAccessibilityUIElement(JSContextRef context, JSValueRef value)
{
    if (!context || !value || !JSAccessibilityUIElement::accessibilityUIElementClass() || !JSValueIsObjectOfClass(context, value, JSAccessibilityUIElement::accessibilityUIElementClass()))
        return 0;
    return static_cast<AccessibilityUIElement*>(JSWrapper::unwrap(context, value));
}

JSClassRef JSAccessibilityUIElement::accessibilityUIElementClass()
{
    static JSClassRef jsClass;
    if (!jsClass) {
        JSClassDefinition definition = kJSClassDefinitionEmpty;
        definition.className = "AccessibilityUIElement";
        definition.parentClass = 0;
        definition.staticValues = staticValues();
        definition.staticFunctions = staticFunctions();
        definition.initialize = initialize;
        definition.finalize = finalize;
        jsClass = JSClassCreate(&definition);
    }
    return jsClass;
}

const JSStaticFunction* JSAccessibilityUIElement::staticFunctions()
{
    static const JSStaticFunction functions[] = {
        { "isEqual", isEqual, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "elementAtPoint", elementAtPoint, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "childAtIndex", childAtIndex, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "indexOfChild", indexOfChild, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "linkedUIElementAtIndex", linkedUIElementAtIndex, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "selectedChildAtIndex", selectedChildAtIndex, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setSelectedChild", setSelectedChild, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "titleUIElement", titleUIElement, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "parentElement", parentElement, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "stringAttributeValue", stringAttributeValue, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "numberAttributeValue", numberAttributeValue, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "uiElementAttributeValue", uiElementAttributeValue, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "boolAttributeValue", boolAttributeValue, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "isAttributeSupported", isAttributeSupported, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "isAttributeSettable", isAttributeSettable, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "isPressActionSupported", isPressActionSupported, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "isIncrementActionSupported", isIncrementActionSupported, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "isDecrementActionSupported", isDecrementActionSupported, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "increment", increment, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "decrement", decrement, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "press", press, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "showMenu", showMenu, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "allAttributes", allAttributes, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "attributesOfChildren", attributesOfChildren, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "attributesOfLinkedUIElements", attributesOfLinkedUIElements, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "attributesOfDocumentLinks", attributesOfDocumentLinks, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "attributesOfColumnHeaders", attributesOfColumnHeaders, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "attributesOfRowHeaders", attributesOfRowHeaders, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "attributesOfColumns", attributesOfColumns, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "attributesOfRows", attributesOfRows, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "attributesOfVisibleCells", attributesOfVisibleCells, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "attributesOfHeader", attributesOfHeader, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "cellForColumnAndRow", cellForColumnAndRow, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "selectedRowAtIndex", selectedRowAtIndex, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "disclosedByRow", disclosedByRow, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "disclosedRowAtIndex", disclosedRowAtIndex, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "rowAtIndex", rowAtIndex, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "indexInTable", indexInTable, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "rowIndexRange", rowIndexRange, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "columnIndexRange", columnIndexRange, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "rowCount", rowCount, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "columnCount", columnCount, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "ariaOwnsElementAtIndex", ariaOwnsElementAtIndex, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "ariaFlowToElementAtIndex", ariaFlowToElementAtIndex, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "parameterizedAttributeNames", parameterizedAttributeNames, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "lineForIndex", lineForIndex, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "rangeForLine", rangeForLine, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "rangeForPosition", rangeForPosition, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "boundsForRange", boundsForRange, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "stringForRange", stringForRange, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "attributedStringForRange", attributedStringForRange, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "attributedStringRangeIsMisspelled", attributedStringRangeIsMisspelled, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "uiElementForSearchPredicate", uiElementForSearchPredicate, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "setSelectedTextRange", setSelectedTextRange, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "scrollToMakeVisible", scrollToMakeVisible, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "textMarkerRangeForElement", textMarkerRangeForElement, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "textMarkerRangeForMarkers", textMarkerRangeForMarkers, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "startTextMarkerForTextMarkerRange", startTextMarkerForTextMarkerRange, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "endTextMarkerForTextMarkerRange", endTextMarkerForTextMarkerRange, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "textMarkerForPoint", textMarkerForPoint, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "previousTextMarker", previousTextMarker, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "nextTextMarker", nextTextMarker, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "accessibilityElementForTextMarker", accessibilityElementForTextMarker, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "stringForTextMarkerRange", stringForTextMarkerRange, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "textMarkerRangeLength", textMarkerRangeLength, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "attributedStringForTextMarkerRangeContainsAttribute", attributedStringForTextMarkerRangeContainsAttribute, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "indexForTextMarker", indexForTextMarker, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "isTextMarkerValid", isTextMarkerValid, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "textMarkerForIndex", textMarkerForIndex, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "addNotificationListener", addNotificationListener, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "removeNotificationListener", removeNotificationListener, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { 0, 0, 0 }
    };
    return functions;
}

const JSStaticValue* JSAccessibilityUIElement::staticValues()
{
    static const JSStaticValue values[] = {
        { "documentEncoding", documentEncoding, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "documentURI", documentURI, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "role", role, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "subrole", subrole, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "roleDescription", roleDescription, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "title", title, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "description", description, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "language", language, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "helpText", helpText, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "valueDescription", valueDescription, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "url", url, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "speak", speak, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "orientation", orientation, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "insertionPointLineNumber", insertionPointLineNumber, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "selectedTextRange", selectedTextRange, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "stringValue", stringValue, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "intValue", intValue, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "minValue", minValue, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "maxValue", maxValue, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "isEnabled", isEnabled, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "isRequired", isRequired, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "isFocused", isFocused, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "isFocusable", isFocusable, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "isSelected", isSelected, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "isMultiSelectable", isMultiSelectable, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "isExpanded", isExpanded, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "isChecked", isChecked, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "isVisible", isVisible, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "isCollapsed", isCollapsed, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "hasPopup", hasPopup, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "isIgnored", isIgnored, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "isOffScreen", isOffScreen, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "isValid", isValid, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "hierarchicalLevel", hierarchicalLevel, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "ariaIsGrabbed", ariaIsGrabbed, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "ariaDropEffects", ariaDropEffects, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "x", x, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "y", y, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "width", width, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "height", height, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "clickPointX", clickPointX, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "clickPointY", clickPointY, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "childrenCount", childrenCount, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "selectedChildrenCount", selectedChildrenCount, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "rowCount", rowCount, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "columnCount", columnCount, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "horizontalScrollbar", horizontalScrollbar, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "verticalScrollbar", verticalScrollbar, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "supportedActions", supportedActions, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "mathPostscriptsDescription", mathPostscriptsDescription, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "mathPrescriptsDescription", mathPrescriptsDescription, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { "pathDescription", pathDescription, 0, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly },
        { 0, 0, 0, 0 }
    };
    return values;
}

// Functions

JSValueRef JSAccessibilityUIElement::isEqual(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    AccessibilityUIElement* otherElement = argumentCount > 0 ? toAccessibilityUIElement(context, arguments[0]) : 0;
    return JSValueMakeBoolean(context, impl->isEqual(otherElement));
}

JSValueRef JSAccessibilityUIElement::elementAtPoint(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double x = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    double y = argumentCount > 1 ? JSValueToNumber(context, arguments[1], 0) : 0;
    return toJS(context, WTF::getPtr(impl->elementAtPoint(x, y)));
}

JSValueRef JSAccessibilityUIElement::childAtIndex(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double index = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    return toJS(context, WTF::getPtr(impl->childAtIndex(index)));
}

JSValueRef JSAccessibilityUIElement::indexOfChild(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    AccessibilityUIElement* child = argumentCount > 0 ? toAccessibilityUIElement(context, arguments[0]) : 0;
    return JSValueMakeNumber(context, impl->indexOfChild(child));
}

JSValueRef JSAccessibilityUIElement::linkedUIElementAtIndex(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double index = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    return toJS(context, WTF::getPtr(impl->linkedUIElementAtIndex(index)));
}

JSValueRef JSAccessibilityUIElement::selectedChildAtIndex(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double index = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    return toJS(context, WTF::getPtr(impl->selectedChildAtIndex(index)));
}

JSValueRef JSAccessibilityUIElement::setSelectedChild(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    AccessibilityUIElement* element = argumentCount > 0 ? toAccessibilityUIElement(context, arguments[0]) : 0;
    impl->setSelectedChild(element);

    return JSValueMakeUndefined(context);
}

JSValueRef JSAccessibilityUIElement::titleUIElement(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return toJS(context, WTF::getPtr(impl->titleUIElement()));
}

JSValueRef JSAccessibilityUIElement::parentElement(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return toJS(context, WTF::getPtr(impl->parentElement()));
}

JSValueRef JSAccessibilityUIElement::stringAttributeValue(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> attr = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    return JSValueMakeStringOrNull(context, impl->stringAttributeValue(attr.get()).get());
}

JSValueRef JSAccessibilityUIElement::numberAttributeValue(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> attr = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    return JSValueMakeNumber(context, impl->numberAttributeValue(attr.get()));
}

JSValueRef JSAccessibilityUIElement::uiElementAttributeValue(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> attr = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    return toJS(context, WTF::getPtr(impl->uiElementAttributeValue(attr.get())));
}

JSValueRef JSAccessibilityUIElement::boolAttributeValue(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> attr = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    return JSValueMakeBoolean(context, impl->boolAttributeValue(attr.get()));
}

JSValueRef JSAccessibilityUIElement::isAttributeSupported(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> attr = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    return JSValueMakeBoolean(context, impl->isAttributeSupported(attr.get()));
}

JSValueRef JSAccessibilityUIElement::isAttributeSettable(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> attr = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    return JSValueMakeBoolean(context, impl->isAttributeSettable(attr.get()));
}

JSValueRef JSAccessibilityUIElement::isPressActionSupported(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->isPressActionSupported());
}

JSValueRef JSAccessibilityUIElement::isIncrementActionSupported(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->isIncrementActionSupported());
}

JSValueRef JSAccessibilityUIElement::isDecrementActionSupported(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->isDecrementActionSupported());
}

JSValueRef JSAccessibilityUIElement::increment(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->increment();

    return JSValueMakeUndefined(context);
}

JSValueRef JSAccessibilityUIElement::decrement(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->decrement();

    return JSValueMakeUndefined(context);
}

JSValueRef JSAccessibilityUIElement::press(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->press();

    return JSValueMakeUndefined(context);
}

JSValueRef JSAccessibilityUIElement::showMenu(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->showMenu();

    return JSValueMakeUndefined(context);
}

JSValueRef JSAccessibilityUIElement::allAttributes(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->allAttributes().get());
}

JSValueRef JSAccessibilityUIElement::attributesOfChildren(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->attributesOfChildren().get());
}

JSValueRef JSAccessibilityUIElement::attributesOfLinkedUIElements(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->attributesOfLinkedUIElements().get());
}

JSValueRef JSAccessibilityUIElement::attributesOfDocumentLinks(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->attributesOfDocumentLinks().get());
}

JSValueRef JSAccessibilityUIElement::attributesOfColumnHeaders(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->attributesOfColumnHeaders().get());
}

JSValueRef JSAccessibilityUIElement::attributesOfRowHeaders(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->attributesOfRowHeaders().get());
}

JSValueRef JSAccessibilityUIElement::attributesOfColumns(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->attributesOfColumns().get());
}

JSValueRef JSAccessibilityUIElement::attributesOfRows(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->attributesOfRows().get());
}

JSValueRef JSAccessibilityUIElement::attributesOfVisibleCells(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->attributesOfVisibleCells().get());
}

JSValueRef JSAccessibilityUIElement::attributesOfHeader(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->attributesOfHeader().get());
}

JSValueRef JSAccessibilityUIElement::cellForColumnAndRow(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double column = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    double row = argumentCount > 1 ? JSValueToNumber(context, arguments[1], 0) : 0;
    return toJS(context, WTF::getPtr(impl->cellForColumnAndRow(column, row)));
}

JSValueRef JSAccessibilityUIElement::selectedRowAtIndex(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double index = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    return toJS(context, WTF::getPtr(impl->selectedRowAtIndex(index)));
}

JSValueRef JSAccessibilityUIElement::disclosedByRow(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return toJS(context, WTF::getPtr(impl->disclosedByRow()));
}

JSValueRef JSAccessibilityUIElement::disclosedRowAtIndex(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double index = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    return toJS(context, WTF::getPtr(impl->disclosedRowAtIndex(index)));
}

JSValueRef JSAccessibilityUIElement::rowAtIndex(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double index = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    return toJS(context, WTF::getPtr(impl->rowAtIndex(index)));
}

JSValueRef JSAccessibilityUIElement::indexInTable(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeNumber(context, impl->indexInTable());
}

JSValueRef JSAccessibilityUIElement::rowIndexRange(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->rowIndexRange().get());
}

JSValueRef JSAccessibilityUIElement::columnIndexRange(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->columnIndexRange().get());
}

JSValueRef JSAccessibilityUIElement::rowCount(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeNumber(context, impl->rowCount());
}

JSValueRef JSAccessibilityUIElement::columnCount(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeNumber(context, impl->columnCount());
}

JSValueRef JSAccessibilityUIElement::ariaOwnsElementAtIndex(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double index = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    return toJS(context, WTF::getPtr(impl->ariaOwnsElementAtIndex(index)));
}

JSValueRef JSAccessibilityUIElement::ariaFlowToElementAtIndex(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double index = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    return toJS(context, WTF::getPtr(impl->ariaFlowToElementAtIndex(index)));
}

JSValueRef JSAccessibilityUIElement::parameterizedAttributeNames(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->parameterizedAttributeNames().get());
}

JSValueRef JSAccessibilityUIElement::lineForIndex(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double index = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    return JSValueMakeNumber(context, impl->lineForIndex(index));
}

JSValueRef JSAccessibilityUIElement::rangeForLine(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double index = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    return JSValueMakeStringOrNull(context, impl->rangeForLine(index).get());
}

JSValueRef JSAccessibilityUIElement::rangeForPosition(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double x = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    double y = argumentCount > 1 ? JSValueToNumber(context, arguments[1], 0) : 0;
    return JSValueMakeStringOrNull(context, impl->rangeForPosition(x, y).get());
}

JSValueRef JSAccessibilityUIElement::boundsForRange(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double location = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    double length = argumentCount > 1 ? JSValueToNumber(context, arguments[1], 0) : 0;
    return JSValueMakeStringOrNull(context, impl->boundsForRange(location, length).get());
}

JSValueRef JSAccessibilityUIElement::stringForRange(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double location = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    double length = argumentCount > 1 ? JSValueToNumber(context, arguments[1], 0) : 0;
    return JSValueMakeStringOrNull(context, impl->stringForRange(location, length).get());
}

JSValueRef JSAccessibilityUIElement::attributedStringForRange(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double location = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    double length = argumentCount > 1 ? JSValueToNumber(context, arguments[1], 0) : 0;
    return JSValueMakeStringOrNull(context, impl->attributedStringForRange(location, length).get());
}

JSValueRef JSAccessibilityUIElement::attributedStringRangeIsMisspelled(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double location = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    double length = argumentCount > 1 ? JSValueToNumber(context, arguments[1], 0) : 0;
    return JSValueMakeBoolean(context, impl->attributedStringRangeIsMisspelled(location, length));
}

JSValueRef JSAccessibilityUIElement::uiElementForSearchPredicate(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    AccessibilityUIElement* startElement = argumentCount > 0 ? toAccessibilityUIElement(context, arguments[0]) : 0;
    bool isDirectionNext = argumentCount > 1 && JSValueToBoolean(context, arguments[1]);
    JSValueRef searchKey = argumentCount > 2 ? arguments[2] : JSValueMakeUndefined(context);
    JSRetainPtr<JSStringRef> searchText = argumentCount > 3 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[3], 0)) : JSRetainPtr<JSStringRef>();
    bool visibleOnly = argumentCount > 4 && JSValueToBoolean(context, arguments[4]);
    return toJS(context, WTF::getPtr(impl->uiElementForSearchPredicate(context, startElement, isDirectionNext, searchKey, searchText.get(), visibleOnly)));
}

JSValueRef JSAccessibilityUIElement::setSelectedTextRange(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double location = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    double length = argumentCount > 1 ? JSValueToNumber(context, arguments[1], 0) : 0;
    impl->setSelectedTextRange(location, length);

    return JSValueMakeUndefined(context);
}

JSValueRef JSAccessibilityUIElement::scrollToMakeVisible(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    impl->scrollToMakeVisible();

    return JSValueMakeUndefined(context);
}

JSValueRef JSAccessibilityUIElement::textMarkerRangeForElement(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    AccessibilityUIElement* element = argumentCount > 0 ? toAccessibilityUIElement(context, arguments[0]) : 0;
    return toJS(context, WTF::getPtr(impl->textMarkerRangeForElement(element)));
}

JSValueRef JSAccessibilityUIElement::textMarkerRangeForMarkers(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    AccessibilityTextMarker* startMarker = argumentCount > 0 ? toAccessibilityTextMarker(context, arguments[0]) : 0;
    AccessibilityTextMarker* endMarker = argumentCount > 1 ? toAccessibilityTextMarker(context, arguments[1]) : 0;
    return toJS(context, WTF::getPtr(impl->textMarkerRangeForMarkers(startMarker, endMarker)));
}

JSValueRef JSAccessibilityUIElement::startTextMarkerForTextMarkerRange(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    AccessibilityTextMarkerRange* range = argumentCount > 0 ? toAccessibilityTextMarkerRange(context, arguments[0]) : 0;
    return toJS(context, WTF::getPtr(impl->startTextMarkerForTextMarkerRange(range)));
}

JSValueRef JSAccessibilityUIElement::endTextMarkerForTextMarkerRange(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    AccessibilityTextMarkerRange* range = argumentCount > 0 ? toAccessibilityTextMarkerRange(context, arguments[0]) : 0;
    return toJS(context, WTF::getPtr(impl->endTextMarkerForTextMarkerRange(range)));
}

JSValueRef JSAccessibilityUIElement::textMarkerForPoint(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double x = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    double y = argumentCount > 1 ? JSValueToNumber(context, arguments[1], 0) : 0;
    return toJS(context, WTF::getPtr(impl->textMarkerForPoint(x, y)));
}

JSValueRef JSAccessibilityUIElement::previousTextMarker(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    AccessibilityTextMarker* marker = argumentCount > 0 ? toAccessibilityTextMarker(context, arguments[0]) : 0;
    return toJS(context, WTF::getPtr(impl->previousTextMarker(marker)));
}

JSValueRef JSAccessibilityUIElement::nextTextMarker(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    AccessibilityTextMarker* marker = argumentCount > 0 ? toAccessibilityTextMarker(context, arguments[0]) : 0;
    return toJS(context, WTF::getPtr(impl->nextTextMarker(marker)));
}

JSValueRef JSAccessibilityUIElement::accessibilityElementForTextMarker(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    AccessibilityTextMarker* marker = argumentCount > 0 ? toAccessibilityTextMarker(context, arguments[0]) : 0;
    return toJS(context, WTF::getPtr(impl->accessibilityElementForTextMarker(marker)));
}

JSValueRef JSAccessibilityUIElement::stringForTextMarkerRange(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    AccessibilityTextMarkerRange* range = argumentCount > 0 ? toAccessibilityTextMarkerRange(context, arguments[0]) : 0;
    return JSValueMakeStringOrNull(context, impl->stringForTextMarkerRange(range).get());
}

JSValueRef JSAccessibilityUIElement::textMarkerRangeLength(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    AccessibilityTextMarkerRange* range = argumentCount > 0 ? toAccessibilityTextMarkerRange(context, arguments[0]) : 0;
    return JSValueMakeNumber(context, impl->textMarkerRangeLength(range));
}

JSValueRef JSAccessibilityUIElement::attributedStringForTextMarkerRangeContainsAttribute(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSRetainPtr<JSStringRef> attr = argumentCount > 0 ? JSRetainPtr<JSStringRef>(Adopt, JSValueToStringCopy(context, arguments[0], 0)) : JSRetainPtr<JSStringRef>();
    AccessibilityTextMarkerRange* range = argumentCount > 1 ? toAccessibilityTextMarkerRange(context, arguments[1]) : 0;
    return JSValueMakeBoolean(context, impl->attributedStringForTextMarkerRangeContainsAttribute(attr.get(), range));
}

JSValueRef JSAccessibilityUIElement::indexForTextMarker(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    AccessibilityTextMarker* marker = argumentCount > 0 ? toAccessibilityTextMarker(context, arguments[0]) : 0;
    return JSValueMakeNumber(context, impl->indexForTextMarker(marker));
}

JSValueRef JSAccessibilityUIElement::isTextMarkerValid(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    AccessibilityTextMarker* marker = argumentCount > 0 ? toAccessibilityTextMarker(context, arguments[0]) : 0;
    return JSValueMakeBoolean(context, impl->isTextMarkerValid(marker));
}

JSValueRef JSAccessibilityUIElement::textMarkerForIndex(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    double textIndex = argumentCount > 0 ? JSValueToNumber(context, arguments[0], 0) : 0;
    return toJS(context, WTF::getPtr(impl->textMarkerForIndex(textIndex)));
}

JSValueRef JSAccessibilityUIElement::addNotificationListener(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    JSValueRef callbackFunction = argumentCount > 0 ? arguments[0] : JSValueMakeUndefined(context);
    return JSValueMakeBoolean(context, impl->addNotificationListener(callbackFunction));
}

JSValueRef JSAccessibilityUIElement::removeNotificationListener(JSContextRef context, JSObjectRef, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, thisObject);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->removeNotificationListener());
}

// Attributes

JSValueRef JSAccessibilityUIElement::documentEncoding(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->documentEncoding().get());
}

JSValueRef JSAccessibilityUIElement::documentURI(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->documentURI().get());
}

JSValueRef JSAccessibilityUIElement::role(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->role().get());
}

JSValueRef JSAccessibilityUIElement::subrole(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->subrole().get());
}

JSValueRef JSAccessibilityUIElement::roleDescription(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->roleDescription().get());
}

JSValueRef JSAccessibilityUIElement::title(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->title().get());
}

JSValueRef JSAccessibilityUIElement::description(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->description().get());
}

JSValueRef JSAccessibilityUIElement::language(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->language().get());
}

JSValueRef JSAccessibilityUIElement::helpText(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->helpText().get());
}

JSValueRef JSAccessibilityUIElement::valueDescription(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->valueDescription().get());
}

JSValueRef JSAccessibilityUIElement::url(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->url().get());
}

JSValueRef JSAccessibilityUIElement::speak(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->speak().get());
}

JSValueRef JSAccessibilityUIElement::orientation(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->orientation().get());
}

JSValueRef JSAccessibilityUIElement::insertionPointLineNumber(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeNumber(context, impl->insertionPointLineNumber());
}

JSValueRef JSAccessibilityUIElement::selectedTextRange(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->selectedTextRange().get());
}

JSValueRef JSAccessibilityUIElement::stringValue(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->stringValue().get());
}

JSValueRef JSAccessibilityUIElement::intValue(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeNumber(context, impl->intValue());
}

JSValueRef JSAccessibilityUIElement::minValue(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeNumber(context, impl->minValue());
}

JSValueRef JSAccessibilityUIElement::maxValue(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeNumber(context, impl->maxValue());
}

JSValueRef JSAccessibilityUIElement::isEnabled(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->isEnabled());
}

JSValueRef JSAccessibilityUIElement::isRequired(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->isRequired());
}

JSValueRef JSAccessibilityUIElement::isFocused(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->isFocused());
}

JSValueRef JSAccessibilityUIElement::isFocusable(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->isFocusable());
}

JSValueRef JSAccessibilityUIElement::isSelected(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->isSelected());
}

JSValueRef JSAccessibilityUIElement::isMultiSelectable(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->isMultiSelectable());
}

JSValueRef JSAccessibilityUIElement::isExpanded(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->isExpanded());
}

JSValueRef JSAccessibilityUIElement::isChecked(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->isChecked());
}

JSValueRef JSAccessibilityUIElement::isVisible(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->isVisible());
}

JSValueRef JSAccessibilityUIElement::isCollapsed(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->isCollapsed());
}

JSValueRef JSAccessibilityUIElement::hasPopup(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->hasPopup());
}

JSValueRef JSAccessibilityUIElement::isIgnored(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->isIgnored());
}

JSValueRef JSAccessibilityUIElement::isOffScreen(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->isOffScreen());
}

JSValueRef JSAccessibilityUIElement::isValid(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->isValid());
}

JSValueRef JSAccessibilityUIElement::hierarchicalLevel(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeNumber(context, impl->hierarchicalLevel());
}

JSValueRef JSAccessibilityUIElement::ariaIsGrabbed(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeBoolean(context, impl->ariaIsGrabbed());
}

JSValueRef JSAccessibilityUIElement::ariaDropEffects(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->ariaDropEffects().get());
}

JSValueRef JSAccessibilityUIElement::x(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeNumber(context, impl->x());
}

JSValueRef JSAccessibilityUIElement::y(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeNumber(context, impl->y());
}

JSValueRef JSAccessibilityUIElement::width(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeNumber(context, impl->width());
}

JSValueRef JSAccessibilityUIElement::height(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeNumber(context, impl->height());
}

JSValueRef JSAccessibilityUIElement::clickPointX(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeNumber(context, impl->clickPointX());
}

JSValueRef JSAccessibilityUIElement::clickPointY(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeNumber(context, impl->clickPointY());
}

JSValueRef JSAccessibilityUIElement::childrenCount(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeNumber(context, impl->childrenCount());
}

JSValueRef JSAccessibilityUIElement::selectedChildrenCount(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeNumber(context, impl->selectedChildrenCount());
}

JSValueRef JSAccessibilityUIElement::rowCount(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeNumber(context, impl->rowCount());
}

JSValueRef JSAccessibilityUIElement::columnCount(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeNumber(context, impl->columnCount());
}

JSValueRef JSAccessibilityUIElement::horizontalScrollbar(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return toJS(context, WTF::getPtr(impl->horizontalScrollbar()));
}

JSValueRef JSAccessibilityUIElement::verticalScrollbar(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return toJS(context, WTF::getPtr(impl->verticalScrollbar()));
}

JSValueRef JSAccessibilityUIElement::supportedActions(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->supportedActions().get());
}

JSValueRef JSAccessibilityUIElement::mathPostscriptsDescription(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->mathPostscriptsDescription().get());
}

JSValueRef JSAccessibilityUIElement::mathPrescriptsDescription(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->mathPrescriptsDescription().get());
}

JSValueRef JSAccessibilityUIElement::pathDescription(JSContextRef context, JSObjectRef object, JSStringRef, JSValueRef* exception)
{
    AccessibilityUIElement* impl = toAccessibilityUIElement(context, object);
    if (!impl)
        return JSValueMakeUndefined(context);

    return JSValueMakeStringOrNull(context, impl->pathDescription().get());
}

} // namespace WTR

