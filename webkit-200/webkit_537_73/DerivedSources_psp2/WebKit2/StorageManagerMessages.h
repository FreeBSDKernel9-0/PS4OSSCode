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

#ifndef StorageManagerMessages_h
#define StorageManagerMessages_h

#include "Arguments.h"
#include "MessageEncoder.h"
#include "StringReference.h"
#include <wtf/HashMap.h>
#include <wtf/text/WTFString.h>

namespace WTF {
    class String;
}

namespace WebKit {
    struct SecurityOriginData;
}

namespace Messages {
namespace StorageManager {

static inline CoreIPC::StringReference messageReceiverName()
{
    return CoreIPC::StringReference("StorageManager");
}

struct CreateLocalStorageMap : CoreIPC::Arguments3<uint64_t, uint64_t, const WebKit::SecurityOriginData&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CreateLocalStorageMap"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<uint64_t, uint64_t, const WebKit::SecurityOriginData&> DecodeType;
    CreateLocalStorageMap(uint64_t storageMapID, uint64_t storageNamespaceID, const WebKit::SecurityOriginData& securityOriginData)
        : CoreIPC::Arguments3<uint64_t, uint64_t, const WebKit::SecurityOriginData&>(storageMapID, storageNamespaceID, securityOriginData)
    {
    }
};

struct CreateSessionStorageMap : CoreIPC::Arguments3<uint64_t, uint64_t, const WebKit::SecurityOriginData&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("CreateSessionStorageMap"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments3<uint64_t, uint64_t, const WebKit::SecurityOriginData&> DecodeType;
    CreateSessionStorageMap(uint64_t storageMapID, uint64_t storageNamespaceID, const WebKit::SecurityOriginData& securityOriginData)
        : CoreIPC::Arguments3<uint64_t, uint64_t, const WebKit::SecurityOriginData&>(storageMapID, storageNamespaceID, securityOriginData)
    {
    }
};

struct DestroyStorageMap : CoreIPC::Arguments1<uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("DestroyStorageMap"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments1<uint64_t> DecodeType;
    explicit DestroyStorageMap(uint64_t storageMapID)
        : CoreIPC::Arguments1<uint64_t>(storageMapID)
    {
    }
};

struct GetValues : CoreIPC::Arguments2<uint64_t, uint64_t> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("GetValues"); }
    static const bool isSync = true;

    typedef CoreIPC::Arguments1<WTF::HashMap<WTF::String, WTF::String>&> Reply;
    typedef CoreIPC::Arguments2<uint64_t, uint64_t> DecodeType;
    GetValues(uint64_t storageMapID, uint64_t storageMapSeed)
        : CoreIPC::Arguments2<uint64_t, uint64_t>(storageMapID, storageMapSeed)
    {
    }
};

struct SetItem : CoreIPC::Arguments6<uint64_t, uint64_t, uint64_t, const WTF::String&, const WTF::String&, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("SetItem"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments6<uint64_t, uint64_t, uint64_t, const WTF::String&, const WTF::String&, const WTF::String&> DecodeType;
    SetItem(uint64_t storageMapID, uint64_t sourceStorageAreaID, uint64_t storageMapSeed, const WTF::String& key, const WTF::String& value, const WTF::String& urlString)
        : CoreIPC::Arguments6<uint64_t, uint64_t, uint64_t, const WTF::String&, const WTF::String&, const WTF::String&>(storageMapID, sourceStorageAreaID, storageMapSeed, key, value, urlString)
    {
    }
};

struct RemoveItem : CoreIPC::Arguments5<uint64_t, uint64_t, uint64_t, const WTF::String&, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("RemoveItem"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments5<uint64_t, uint64_t, uint64_t, const WTF::String&, const WTF::String&> DecodeType;
    RemoveItem(uint64_t storageMapID, uint64_t sourceStorageAreaID, uint64_t storageMapSeed, const WTF::String& key, const WTF::String& urlString)
        : CoreIPC::Arguments5<uint64_t, uint64_t, uint64_t, const WTF::String&, const WTF::String&>(storageMapID, sourceStorageAreaID, storageMapSeed, key, urlString)
    {
    }
};

struct Clear : CoreIPC::Arguments4<uint64_t, uint64_t, uint64_t, const WTF::String&> {
    static CoreIPC::StringReference receiverName() { return messageReceiverName(); }
    static CoreIPC::StringReference name() { return CoreIPC::StringReference("Clear"); }
    static const bool isSync = false;

    typedef CoreIPC::Arguments4<uint64_t, uint64_t, uint64_t, const WTF::String&> DecodeType;
    Clear(uint64_t storageMapID, uint64_t sourceStorageAreaID, uint64_t storageMapSeed, const WTF::String& urlString)
        : CoreIPC::Arguments4<uint64_t, uint64_t, uint64_t, const WTF::String&>(storageMapID, sourceStorageAreaID, storageMapSeed, urlString)
    {
    }
};

} // namespace StorageManager
} // namespace Messages

#endif // StorageManagerMessages_h
