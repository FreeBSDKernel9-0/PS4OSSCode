/*
 * Copyright (C) 2010 Google, Inc. All Rights Reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "DecodedDataDocumentParser.h"

#include "DocumentWriter.h"
#include "SegmentedString.h"
#include "TextResourceDecoder.h"
#if OS(PSP2) && USE(ICU_UNICODE)
#include <unicode/unorm.h>
#endif

namespace WebCore {

#if OS(PSP2) && USE(ICU_UNICODE)
static void normalize(String& string)
{
    const UChar* source = string.characters();
    size_t sourceLength = string.length();
    size_t length = sourceLength;

    Vector<UChar> normalizedCharacters;

    UErrorCode err = U_ZERO_ERROR;
    if (unorm_quickCheck(source, sourceLength, UNORM_NFC, &err) != UNORM_YES) {
        // First try using the length of the original string, since normalization to NFC rarely increases length.
        normalizedCharacters.grow(sourceLength);
        int32_t normalizedLength = unorm_normalize(source, length, UNORM_NFC, 0, normalizedCharacters.data(), length, &err);
        if (err == U_BUFFER_OVERFLOW_ERROR) {
            err = U_ZERO_ERROR;
            normalizedCharacters.resize(normalizedLength);
            normalizedLength = unorm_normalize(source, length, UNORM_NFC, 0, normalizedCharacters.data(), normalizedLength, &err);
        }
        ASSERT(U_SUCCESS(err));

        source = normalizedCharacters.data();
        sourceLength = normalizedLength;
        string = String(source, sourceLength);
    }
}
#endif // OS(PSP2) && USE(ICU_UNICODE)

DecodedDataDocumentParser::DecodedDataDocumentParser(Document* document)
    : DocumentParser(document)
{
}

void DecodedDataDocumentParser::appendBytes(DocumentWriter* writer, const char* data, size_t length)
{
    if (!length)
        return;

    String decoded = writer->createDecoderIfNeeded()->decode(data, length);
    if (decoded.isEmpty())
        return;

#if OS(PSP2) && USE(ICU_UNICODE)
    normalize(decoded);
#endif
    writer->reportDataReceived();
    append(decoded);
}

void DecodedDataDocumentParser::flush(DocumentWriter* writer)
{
    String remainingData = writer->createDecoderIfNeeded()->flush();
    if (remainingData.isEmpty())
        return;

#if OS(PSP2) && USE(ICU_UNICODE)
    normalize(remainingData);
#endif
    writer->reportDataReceived();
    append(remainingData);
}

};
