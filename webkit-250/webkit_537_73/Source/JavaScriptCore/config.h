/*
 * Copyright (C) 2006, 2007, 2008 Apple Inc. All rights reserved.
 * Copyright (C) 2006 Samuel Weinig <sam.weinig@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#if defined(HAVE_CONFIG_H) && HAVE_CONFIG_H
#ifdef BUILDING_WITH_CMAKE
#include "cmakeconfig.h"
#else
#include "autotoolsconfig.h"
#endif
#endif

#include <wtf/Platform.h>
#include <wtf/ExportMacros.h>
#if !defined(BUILDING_WTF)
#include "JSExportMacros.h"
#endif

#if OS(WINDOWS)

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0502
#endif

#ifndef WINVER
#define WINVER 0x0502
#endif

// If we don't define these, they get defined in windef.h. 
// We want to use std::min and std::max
#define max max
#define min min

#if !COMPILER(MSVC7_OR_LOWER) && !OS(WINCE)
// We need to define this before the first #include of stdlib.h or it won't contain rand_s.
#ifndef _CRT_RAND_S
#define _CRT_RAND_S
#endif
#endif // !COMPILER(MSVC7_OR_LOWER) && !OS(WINCE)

#endif // OS(WINDOWS)

#define WTF_CHANGES 1

#ifdef __cplusplus
#undef new
#undef delete
#include <wtf/FastMalloc.h>
#endif

#include <wtf/DisallowCType.h>

#if COMPILER(MSVC)
#define SKIP_STATIC_CONSTRUCTORS_ON_MSVC 1
#else
#define SKIP_STATIC_CONSTRUCTORS_ON_GCC 1
#endif

#if PLATFORM(MANX)
#include <manx/util.h>

#define PUSH_CPU_MARKER(label, color) pa_push_marker(label, color)
#define POP_CPU_MARKER() pa_pop_marker()
#define CPU_SYNC() pa_sync()

#ifdef __cplusplus
class ScopedMarker
{
public:
    ScopedMarker(const char* label, unsigned int color) { PUSH_CPU_MARKER(label, color); }
    ~ScopedMarker() { POP_CPU_MARKER(); }
};
#define TOKENPASTE(x, y) x ## y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)
#define SCOPED_MARKER(label, color) ScopedMarker TOKENPASTE2(marker, __LINE__)(label, color)
#define FUNCTION_MARKER SCOPED_MARKER(__PRETTY_FUNCTION__, PA_COLOR_GREEN)
#endif // __cplusplus

#endif
