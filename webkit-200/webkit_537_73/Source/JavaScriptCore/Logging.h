// Copyright (C) 2012 Sony Computer Entertainment Inc.
// All Rights Reserved.

#ifndef Logging_h
#define Logging_h

#include <wtf/Assertions.h>

#ifndef LOG_CHANNEL_PREFIX
#define LOG_CHANNEL_PREFIX Log
#endif

namespace JSC {

extern WTFLogChannel LogDetachedJIT;        // for logs coming from the detached JIT compiler
extern WTFLogChannel LogDetachedJITProxy;   // for logs coming from the JIT compiler proxy invoked by the VM

} // namespace JSC

#endif // #ifndef Logging_h