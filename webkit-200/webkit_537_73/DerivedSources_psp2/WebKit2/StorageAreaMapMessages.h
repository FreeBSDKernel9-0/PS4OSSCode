/*
 * Copyright (C) 2010 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef StorageAreaMapMessages_h
#define StorageAreaMapMessages_h

#include "Arguments.h"
#include "MessageEncoder.h"
#include "StringReference.h"

namespace WTF {
    class String;
}

namespace Messages {
namespace StorageAreaMap {

static inline CoreIPC::StringReference messageReceiverName()
{
    return CoreIPC::StringReference("StorageAreaMap");
}

struct DidGetValues : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidGetValues"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit DidGetValues(uint64_t storageMapSeed)
        : CoreIPC::Arguments1<uint64_t>(storageMapSeed)
    {
    }
};

struct DidSetItem : CoreIPC::Arguments3<uint64_t, const WTF::String&, bool> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidSetItem"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<uint64_t, const WTF::String&, bool> DecodeType;
    DidSetItem(uint64_t storageMapSeed, const WTF::String& key, bool quotaException)
        : CoreIPC::Arguments3<uint64_t, const WTF::String&, bool>(storageMapSeed, key, quotaException)
    {
    }
};

struct DidRemoveItem : CoreIPC::Arguments2<uint64_t, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidRemoveItem"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments2<uint64_t, const WTF::String&> DecodeType;
    DidRemoveItem(uint64_t storageMapSeed, const WTF::String& key)
        : CoreIPC::Arguments2<uint64_t, const WTF::String&>(storageMapSeed, key)
    {
    }
};

struct DidClear : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DidClear"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit DidClear(uint64_t storageMapSeed)
        : CoreIPC::Arguments1<uint64_t>(storageMapSeed)
    {
    }
};

struct DispatchStorageEvent : CoreIPC::Arguments5<uint64_t, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DispatchStorageEvent"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments5<uint64_t, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&> DecodeType;
    DispatchStorageEvent(uint64_t sourceStorageAreaID, const WTF::String& key, const WTF::String& oldValue, const WTF::String& newValue, const WTF::String& urlString)
        : CoreIPC::Arguments5<uint64_t, const WTF::String&, const WTF::String&, const WTF::String&, const WTF::String&>(sourceStorageAreaID, key, oldValue, newValue, urlString)
    {
    }
};

struct ClearCache : CoreIPC::Arguments0 {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("ClearCache"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments0 DecodeType;
};

} // namespace StorageAreaMap
} // namespace Messages

#endif // StorageAreaMapMessages_h
