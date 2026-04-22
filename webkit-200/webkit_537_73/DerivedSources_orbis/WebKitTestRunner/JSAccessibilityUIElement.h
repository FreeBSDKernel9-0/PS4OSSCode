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
#ifndef JSAccessibilityUIElement_h
#define JSAccessibilityUIElement_h

#include "JSWrapper.h"

namespace WTR {

class AccessibilityUIElement;

class JSAccessibilityUIElement : public JSWrapper {
public:
    static JSClassRef accessibilityUIElementClass();

private:
    static const JSStaticFunction* staticFunctions();
    static const JSStaticValue* staticValues();

    // Functions

    static JSValueRef isEqual(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef elementAtPoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef childAtIndex(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef indexOfChild(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef linkedUIElementAtIndex(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef selectedChildAtIndex(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef setSelectedChild(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef titleUIElement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef parentElement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef stringAttributeValue(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef numberAttributeValue(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef uiElementAttributeValue(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef boolAttributeValue(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef isAttributeSupported(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef isAttributeSettable(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef isPressActionSupported(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef isIncrementActionSupported(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef isDecrementActionSupported(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef increment(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef decrement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef press(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef showMenu(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef allAttributes(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef attributesOfChildren(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef attributesOfLinkedUIElements(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef attributesOfDocumentLinks(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef attributesOfColumnHeaders(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef attributesOfRowHeaders(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef attributesOfColumns(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef attributesOfRows(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef attributesOfVisibleCells(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef attributesOfHeader(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef cellForColumnAndRow(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef selectedRowAtIndex(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef disclosedByRow(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef disclosedRowAtIndex(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef rowAtIndex(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef indexInTable(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef rowIndexRange(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef columnIndexRange(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef rowCount(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef columnCount(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef ariaOwnsElementAtIndex(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef ariaFlowToElementAtIndex(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef parameterizedAttributeNames(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef lineForIndex(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef rangeForLine(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef rangeForPosition(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef boundsForRange(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef stringForRange(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef attributedStringForRange(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef attributedStringRangeIsMisspelled(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef uiElementForSearchPredicate(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef setSelectedTextRange(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef scrollToMakeVisible(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef textMarkerRangeForElement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef textMarkerRangeForMarkers(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef startTextMarkerForTextMarkerRange(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef endTextMarkerForTextMarkerRange(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef textMarkerForPoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef previousTextMarker(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef nextTextMarker(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef accessibilityElementForTextMarker(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef stringForTextMarkerRange(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef textMarkerRangeLength(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef attributedStringForTextMarkerRangeContainsAttribute(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef indexForTextMarker(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef isTextMarkerValid(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef textMarkerForIndex(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef addNotificationListener(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    static JSValueRef removeNotificationListener(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    // Attributes

    static JSValueRef documentEncoding(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef documentURI(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef role(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef subrole(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef roleDescription(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef title(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef description(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef language(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef helpText(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef valueDescription(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef url(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef speak(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef orientation(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef insertionPointLineNumber(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef selectedTextRange(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef stringValue(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef intValue(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef minValue(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef maxValue(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef isEnabled(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef isRequired(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef isFocused(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef isFocusable(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef isSelected(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef isMultiSelectable(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef isExpanded(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef isChecked(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef isVisible(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef isCollapsed(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef hasPopup(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef isIgnored(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef isOffScreen(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef isValid(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef hierarchicalLevel(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef ariaIsGrabbed(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef ariaDropEffects(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef x(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef y(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef width(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef height(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef clickPointX(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef clickPointY(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef childrenCount(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef selectedChildrenCount(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef rowCount(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef columnCount(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef horizontalScrollbar(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef verticalScrollbar(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef supportedActions(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef mathPostscriptsDescription(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef mathPrescriptsDescription(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
    static JSValueRef pathDescription(JSContextRef, JSObjectRef, JSStringRef, JSValueRef*);
};
    
AccessibilityUIElement* toAccessibilityUIElement(JSContextRef, JSValueRef);

} // namespace WTR

#endif // JSAccessibilityUIElement_h
