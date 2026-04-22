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

#include "WebProcess.h"

#include "ArgumentCoders.h"
#include "DataReference.h"
#include "HandleMessage.h"
#include "MessageDecoder.h"
#include "SandboxExtension.h"
#include "SharedMemory.h"
#include "TextCheckerState.h"
#include "WebContextUserMessageCoders.h"
#include "WebCoreArgumentCoders.h"
#include "WebPageCreationParameters.h"
#include "WebProcessCreationParameters.h"
#include "WebProcessMessages.h"
#include <WebCore/LinkHash.h>
#include <WebCore/ResourceRequest.h>
#include <wtf/HashMap.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace WebKit {

void WebProcess::didReceiveWebProcessMessage(CoreIPC::Connection*, CoreIPC::MessageDecoder& decoder)
{
    if (decoder.messageName() == Messages::WebProcess::InitializeWebProcess::name()) {
        CoreIPC::handleMessageVariadic<Messages::WebProcess::InitializeWebProcess>(decoder, this, &WebProcess::initializeWebProcess);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::CreateWebPage::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::CreateWebPage>(decoder, this, &WebProcess::createWebPage);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::SetVisitedLinkTable::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::SetVisitedLinkTable>(decoder, this, &WebProcess::setVisitedLinkTable);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::VisitedLinkStateChanged::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::VisitedLinkStateChanged>(decoder, this, &WebProcess::visitedLinkStateChanged);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::AllVisitedLinkStateChanged::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::AllVisitedLinkStateChanged>(decoder, this, &WebProcess::allVisitedLinkStateChanged);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::SetShouldTrackVisitedLinks::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::SetShouldTrackVisitedLinks>(decoder, this, &WebProcess::setShouldTrackVisitedLinks);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::SetCacheModel::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::SetCacheModel>(decoder, this, &WebProcess::setCacheModel);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::RegisterURLSchemeAsEmptyDocument::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::RegisterURLSchemeAsEmptyDocument>(decoder, this, &WebProcess::registerURLSchemeAsEmptyDocument);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::RegisterURLSchemeAsSecure::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::RegisterURLSchemeAsSecure>(decoder, this, &WebProcess::registerURLSchemeAsSecure);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::SetDomainRelaxationForbiddenForURLScheme::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::SetDomainRelaxationForbiddenForURLScheme>(decoder, this, &WebProcess::setDomainRelaxationForbiddenForURLScheme);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::RegisterURLSchemeAsLocal::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::RegisterURLSchemeAsLocal>(decoder, this, &WebProcess::registerURLSchemeAsLocal);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::RegisterURLSchemeAsNoAccess::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::RegisterURLSchemeAsNoAccess>(decoder, this, &WebProcess::registerURLSchemeAsNoAccess);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::RegisterURLSchemeAsDisplayIsolated::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::RegisterURLSchemeAsDisplayIsolated>(decoder, this, &WebProcess::registerURLSchemeAsDisplayIsolated);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::RegisterURLSchemeAsCORSEnabled::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::RegisterURLSchemeAsCORSEnabled>(decoder, this, &WebProcess::registerURLSchemeAsCORSEnabled);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::SetDefaultRequestTimeoutInterval::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::SetDefaultRequestTimeoutInterval>(decoder, this, &WebProcess::setDefaultRequestTimeoutInterval);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::SetAlwaysUsesComplexTextCodePath::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::SetAlwaysUsesComplexTextCodePath>(decoder, this, &WebProcess::setAlwaysUsesComplexTextCodePath);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::SetShouldUseFontSmoothing::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::SetShouldUseFontSmoothing>(decoder, this, &WebProcess::setShouldUseFontSmoothing);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::UserPreferredLanguagesChanged::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::UserPreferredLanguagesChanged>(decoder, this, &WebProcess::userPreferredLanguagesChanged);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::FullKeyboardAccessModeChanged::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::FullKeyboardAccessModeChanged>(decoder, this, &WebProcess::fullKeyboardAccessModeChanged);
        return;
    }
#if USE(SOUP)
    if (decoder.messageName() == Messages::WebProcess::SetIgnoreTLSErrors::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::SetIgnoreTLSErrors>(decoder, this, &WebProcess::setIgnoreTLSErrors);
        return;
    }
#endif
    if (decoder.messageName() == Messages::WebProcess::EnsurePrivateBrowsingSession::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::EnsurePrivateBrowsingSession>(decoder, this, &WebProcess::ensurePrivateBrowsingSession);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::DestroyPrivateBrowsingSession::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::DestroyPrivateBrowsingSession>(decoder, this, &WebProcess::destroyPrivateBrowsingSession);
        return;
    }
#if ENABLE(NETSCAPE_PLUGIN_API) && !ENABLE(PLUGIN_PROCESS)
    if (decoder.messageName() == Messages::WebProcess::GetSitesWithPluginData::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::GetSitesWithPluginData>(decoder, this, &WebProcess::getSitesWithPluginData);
        return;
    }
#endif
#if ENABLE(NETSCAPE_PLUGIN_API) && !ENABLE(PLUGIN_PROCESS)
    if (decoder.messageName() == Messages::WebProcess::ClearPluginSiteData::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::ClearPluginSiteData>(decoder, this, &WebProcess::clearPluginSiteData);
        return;
    }
#endif
    if (decoder.messageName() == Messages::WebProcess::DidAddPlugInAutoStartOriginHash::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::DidAddPlugInAutoStartOriginHash>(decoder, this, &WebProcess::didAddPlugInAutoStartOriginHash);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::ResetPlugInAutoStartOriginHashes::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::ResetPlugInAutoStartOriginHashes>(decoder, this, &WebProcess::resetPlugInAutoStartOriginHashes);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::StartMemorySampler::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::StartMemorySampler>(decoder, this, &WebProcess::startMemorySampler);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::StopMemorySampler::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::StopMemorySampler>(decoder, this, &WebProcess::stopMemorySampler);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::DownloadRequest::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::DownloadRequest>(decoder, this, &WebProcess::downloadRequest);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::CancelDownload::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::CancelDownload>(decoder, this, &WebProcess::cancelDownload);
        return;
    }
#if PLATFORM(QT)
    if (decoder.messageName() == Messages::WebProcess::StartTransfer::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::StartTransfer>(decoder, this, &WebProcess::startTransfer);
        return;
    }
#endif
    if (decoder.messageName() == Messages::WebProcess::SetTextCheckerState::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::SetTextCheckerState>(decoder, this, &WebProcess::setTextCheckerState);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::SetEnhancedAccessibility::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::SetEnhancedAccessibility>(decoder, this, &WebProcess::setEnhancedAccessibility);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::GetWebCoreStatistics::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::GetWebCoreStatistics>(decoder, this, &WebProcess::getWebCoreStatistics);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::GarbageCollectJavaScriptObjects::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::GarbageCollectJavaScriptObjects>(decoder, this, &WebProcess::garbageCollectJavaScriptObjects);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::SetJavaScriptGarbageCollectorTimerEnabled::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::SetJavaScriptGarbageCollectorTimerEnabled>(decoder, this, &WebProcess::setJavaScriptGarbageCollectorTimerEnabled);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::PostInjectedBundleMessage::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::PostInjectedBundleMessage>(decoder, this, &WebProcess::postInjectedBundleMessage);
        return;
    }
    if (decoder.messageName() == Messages::WebProcess::ReleasePageCache::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::ReleasePageCache>(decoder, this, &WebProcess::releasePageCache);
        return;
    }
#if PLATFORM(MAC)
    if (decoder.messageName() == Messages::WebProcess::SetProcessSuppressionEnabled::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::SetProcessSuppressionEnabled>(decoder, this, &WebProcess::setProcessSuppressionEnabled);
        return;
    }
#endif
#if PLATFORM(MANX)
    if (decoder.messageName() == Messages::WebProcess::SetPrivilegedNetworkBandwidth::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::SetPrivilegedNetworkBandwidth>(decoder, this, &WebProcess::setPrivilegedNetworkBandwidth);
        return;
    }
#endif
#if PLATFORM(MANX)
    if (decoder.messageName() == Messages::WebProcess::SetIFilterHTTPProxy::name()) {
        CoreIPC::handleMessage<Messages::WebProcess::SetIFilterHTTPProxy>(decoder, this, &WebProcess::setIFilterHTTPProxy);
        return;
    }
#endif
    ASSERT_NOT_REACHED();
}

} // namespace WebKit
