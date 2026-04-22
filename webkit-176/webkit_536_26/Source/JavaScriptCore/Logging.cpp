// Copyright (C) 2012 Sony Computer Entertainment Inc.
// All Rights Reserved.

#include "config.h"
#include "Logging.h"

namespace JSC {

WTFLogChannel LogDetachedJIT      = { 0x00000001, "JSCoreLogLevel", WTFLogChannelOff };
WTFLogChannel LogDetachedJITProxy = { 0x00000002, "JSCoreLogLevel", WTFLogChannelOff };

}
