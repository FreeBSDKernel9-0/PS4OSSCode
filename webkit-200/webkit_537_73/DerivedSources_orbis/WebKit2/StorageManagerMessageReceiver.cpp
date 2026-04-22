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

#include "config.h"

#include "StorageManager.h"

#include "ArgumentCoders.h"
#include "HandleMessage.h"
#include "MessageDecoder.h"
#include "SecurityOriginData.h"
#include "StorageManagerMessages.h"
#include <wtf/HashMap.h>
#include <wtf/text/WTFString.h>

namespace WebKit {

void StorageManager::didReceiveMessage(CoreIPC::Connection* connection, CoreIPC::MessageDecoder& decoder)
{
    if (decoder.messageName() == Messages::StorageManager::CreateLocalStorageMap::name()) {
        CoreIPC::handleMessage<Messages::StorageManager::CreateLocalStorageMap>(connection, decoder, this, &StorageManager::createLocalStorageMap);
        return;
    }
    if (decoder.messageName() == Messages::StorageManager::CreateSessionStorageMap::name()) {
        CoreIPC::handleMessage<Messages::StorageManager::CreateSessionStorageMap>(connection, decoder, this, &StorageManager::createSessionStorageMap);
        return;
    }
    if (decoder.messageName() == Messages::StorageManager::DestroyStorageMap::name()) {
        CoreIPC::handleMessage<Messages::StorageManager::DestroyStorageMap>(connection, decoder, this, &StorageManager::destroyStorageMap);
        return;
    }
    if (decoder.messageName() == Messages::StorageManager::SetItem::name()) {
        CoreIPC::handleMessage<Messages::StorageManager::SetItem>(connection, decoder, this, &StorageManager::setItem);
        return;
    }
    if (decoder.messageName() == Messages::StorageManager::RemoveItem::name()) {
        CoreIPC::handleMessage<Messages::StorageManager::RemoveItem>(connection, decoder, this, &StorageManager::removeItem);
        return;
    }
    if (decoder.messageName() == Messages::StorageManager::Clear::name()) {
        CoreIPC::handleMessage<Messages::StorageManager::Clear>(connection, decoder, this, &StorageManager::clear);
        return;
    }
    UNUSED_PARAM(connection);
    ASSERT_NOT_REACHED();
}

void StorageManager::didReceiveSyncMessage(CoreIPC::Connection* connection, CoreIPC::MessageDecoder& decoder, OwnPtr<CoreIPC::MessageEncoder>& replyEncoder)
{
    if (decoder.messageName() == Messages::StorageManager::GetValues::name()) {
        CoreIPC::handleMessage<Messages::StorageManager::GetValues>(connection, decoder, *replyEncoder, this, &StorageManager::getValues);
        return;
    }
    UNUSED_PARAM(connection);
    ASSERT_NOT_REACHED();
}

} // namespace WebKit
