/*
 * Copyright (C) 2007 Kevin Ollivier <kevino@theolliviers.com>
 * Copyright (C) 2012 Sony Computer Entertainment Inc.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "Editor.h"

#include "ClipboardManx.h"
#include "CompositionEvent.h"
#include "Frame.h"
#include "NotImplemented.h"
#include "Text.h"
#include "TypingCommand.h"
#include "UserTypingGestureIndicator.h"

namespace WebCore {

PassRefPtr<Clipboard> Editor::newGeneralClipboard(ClipboardAccessPolicy policy, Frame *frame)
{
    return ClipboardManx::create(policy, Clipboard::CopyAndPaste);
}

void Editor::confirmComposition(const String& text, unsigned int caretIndexInText)
{
    SetCompositionMode mode = ConfirmComposition;
    UserTypingGestureIndicator typingGestureIndicator(m_frame);

    setIgnoreCompositionSelectionChange(true);

    selectComposition();

    if (m_frame->selection()->isNone()) {
        setIgnoreCompositionSelectionChange(false);
        return;
    }
    
    Node* target = m_frame->document()->focusedNode();
    if (target) {
        RefPtr<CompositionEvent> event = CompositionEvent::create(eventNames().compositionendEvent, m_frame->domWindow(), text);
        ExceptionCode ec = 0;
        target->dispatchEvent(event, ec);
    }

    if (text.isEmpty() && mode != CancelComposition)
        TypingCommand::deleteSelection(m_frame->document(), 0);

    m_compositionNode = 0;
    m_customCompositionUnderlines.clear();

    insertTextForConfirmedComposition(text);

    Position base = m_frame->selection()->base().downstream();
    Position extent = m_frame->selection()->extent();
    Node* baseNode = base.deprecatedNode();
    unsigned baseOffset = base.deprecatedEditingOffset();
    Node* extentNode = extent.deprecatedNode();

    if (baseNode && baseNode == extentNode && baseNode->isTextNode()) {
        unsigned actualCaretIndex = (baseOffset - text.length() + caretIndexInText);
        RefPtr<Range> selectedRange = Range::create(baseNode->document(), baseNode, actualCaretIndex, baseNode, actualCaretIndex);                
        m_frame->selection()->setSelectedRange(selectedRange.get(), DOWNSTREAM, false);
    }

    setIgnoreCompositionSelectionChange(false);
}

void Editor::showColorPanel()
{
    notImplemented();
}

void Editor::showFontPanel()
{
    notImplemented();
}

void Editor::showStylesPanel()
{
    notImplemented();
}

}
