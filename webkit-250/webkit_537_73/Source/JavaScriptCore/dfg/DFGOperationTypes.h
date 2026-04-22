/*
 * Copyright (C) 2011 Apple Inc. All rights reserved.
 * Copyright (C) 2013 Sony Computer Entertainment
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

#ifndef DFGOperationTypes_h
#define DFGOperationTypes_h

#include "bytecode/ResolveOperation.h"
#include "MacroAssemblerCodeRef.h"

namespace JSC {

class  ExecState;
class  Identifier;
struct InlineCallFrame;
class  JSArray;
class  JSCell;
class  JSString;
struct PutToBaseOperation;
class  WatchpointSet;

namespace DFG {

extern "C" {

#if CALLING_CONVENTION_IS_STDCALL
#define DFG_OPERATION CDECL
#else
#define DFG_OPERATION
#endif

// These typedefs provide typechecking when generating calls out to helper routines;
// this helps prevent calling a helper routine with the wrong arguments!
/*
    Key:
    V: void
    J: JSValue
    P: pointer (void*)
    C: JSCell*
    A: JSArray*
    S: size_t
    Z: int32_t
    D: double
    I: Identifier*
    G: GlobalResolveInfo*
*/
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_E)(ExecState*);
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_EA)(ExecState*, JSArray*);
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_EAZ)(ExecState*, JSArray*, int32_t);
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_EC)(ExecState*, JSCell*);
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_ECC)(ExecState*, JSCell*, JSCell*);
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_ECI)(ExecState*, JSCell*, Identifier*);
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_ECJ)(ExecState*, JSCell*, EncodedJSValue);
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_EDA)(ExecState*, double, JSArray*);
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_EGriJsgI)(ExecState*, ResolveOperation*, JSGlobalObject*, Identifier*);
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_EI)(ExecState*, Identifier*);
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_EIRo)(ExecState*, Identifier*, ResolveOperations*);
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_EIRoPtbo)(ExecState*, Identifier*, ResolveOperations*, PutToBaseOperation*);
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_EJ)(ExecState*, EncodedJSValue);
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_EJA)(ExecState*, EncodedJSValue, JSArray*);
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_EJI)(ExecState*, EncodedJSValue, Identifier*);
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_EJJ)(ExecState*, EncodedJSValue, EncodedJSValue);
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_EJP)(ExecState*, EncodedJSValue, void*);
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_EP)(ExecState*, void*);
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_EPP)(ExecState*, void*, void*);
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_EPS)(ExecState*, void*, size_t);
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_ESS)(ExecState*, size_t, size_t);
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_EZ)(ExecState*, int32_t);
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_EZIcfZ)(ExecState*, int32_t, InlineCallFrame*, int32_t);
typedef EncodedJSValue DFG_OPERATION (*J_DFGOperation_EZZ)(ExecState*, int32_t, int32_t);
typedef JSCell* DFG_OPERATION (*C_DFGOperation_E)(ExecState*);
typedef JSCell* DFG_OPERATION (*C_DFGOperation_EZ)(ExecState*, int32_t);
typedef JSCell* DFG_OPERATION (*C_DFGOperation_EC)(ExecState*, JSCell*);
typedef JSCell* DFG_OPERATION (*C_DFGOperation_ECC)(ExecState*, JSCell*, JSCell*);
typedef JSCell* DFG_OPERATION (*C_DFGOperation_EIcf)(ExecState*, InlineCallFrame*);
typedef JSCell* DFG_OPERATION (*C_DFGOperation_EJ)(ExecState*, EncodedJSValue);
typedef JSCell* DFG_OPERATION (*C_DFGOperation_EJssSt)(ExecState*, JSString*, Structure*);
typedef JSCell* DFG_OPERATION (*C_DFGOperation_EJssJss)(ExecState*, JSString*, JSString*);
typedef JSCell* DFG_OPERATION (*C_DFGOperation_EJssJssJss)(ExecState*, JSString*, JSString*, JSString*);
typedef JSCell* DFG_OPERATION (*C_DFGOperation_EOZ)(ExecState*, JSObject*, int32_t);
typedef JSCell* DFG_OPERATION (*C_DFGOperation_ESt)(ExecState*, Structure*);
typedef JSCell* DFG_OPERATION (*C_DFGOperation_EZ)(ExecState*, int32_t);
typedef double DFG_OPERATION (*D_DFGOperation_DD)(double, double);
typedef double DFG_OPERATION (*D_DFGOperation_ZZ)(int32_t, int32_t);
typedef double DFG_OPERATION (*D_DFGOperation_EJ)(ExecState*, EncodedJSValue);
typedef int32_t DFG_OPERATION (*Z_DFGOperation_D)(double);
typedef size_t DFG_OPERATION (*S_DFGOperation_ECC)(ExecState*, JSCell*, JSCell*);
typedef size_t DFG_OPERATION (*S_DFGOperation_EJ)(ExecState*, EncodedJSValue);
typedef size_t DFG_OPERATION (*S_DFGOperation_EJJ)(ExecState*, EncodedJSValue, EncodedJSValue);
typedef size_t DFG_OPERATION (*S_DFGOperation_J)(EncodedJSValue);
typedef void DFG_OPERATION (*V_DFGOperation_EOZD)(ExecState*, JSObject*, int32_t, double);
typedef void DFG_OPERATION (*V_DFGOperation_EOZJ)(ExecState*, JSObject*, int32_t, EncodedJSValue);
typedef void DFG_OPERATION (*V_DFGOperation_EC)(ExecState*, JSCell*);
typedef void DFG_OPERATION (*V_DFGOperation_ECIcf)(ExecState*, JSCell*, InlineCallFrame*);
typedef void DFG_OPERATION (*V_DFGOperation_ECCIcf)(ExecState*, JSCell*, JSCell*, InlineCallFrame*);
typedef void DFG_OPERATION (*V_DFGOperation_ECJJ)(ExecState*, JSCell*, EncodedJSValue, EncodedJSValue);
typedef void DFG_OPERATION (*V_DFGOperation_ECZ)(ExecState*, JSCell*, int32_t);
typedef void DFG_OPERATION (*V_DFGOperation_ECC)(ExecState*, JSCell*, JSCell*);
typedef void DFG_OPERATION (*V_DFGOperation_EJCI)(ExecState*, EncodedJSValue, JSCell*, Identifier*);
typedef void DFG_OPERATION (*V_DFGOperation_EJJJ)(ExecState*, EncodedJSValue, EncodedJSValue, EncodedJSValue);
typedef void DFG_OPERATION (*V_DFGOperation_EJPP)(ExecState*, EncodedJSValue, EncodedJSValue, void*);
typedef void DFG_OPERATION (*V_DFGOperation_EPZJ)(ExecState*, void*, int32_t, EncodedJSValue);
typedef void DFG_OPERATION (*V_DFGOperation_W)(WatchpointSet*);
typedef char* DFG_OPERATION (*P_DFGOperation_E)(ExecState*);
typedef char* DFG_OPERATION (*P_DFGOperation_EC)(ExecState*, JSCell*);
typedef char* DFG_OPERATION (*P_DFGOperation_EO)(ExecState*, JSObject*);
typedef char* DFG_OPERATION (*P_DFGOperation_EOS)(ExecState*, JSObject*, size_t);
typedef char* DFG_OPERATION (*P_DFGOperation_EOZ)(ExecState*, JSObject*, int32_t);
typedef char* DFG_OPERATION (*P_DFGOperation_EPS)(ExecState*, void*, size_t);
typedef char* DFG_OPERATION (*P_DFGOperation_ES)(ExecState*, size_t);
typedef char* DFG_OPERATION (*P_DFGOperation_ESt)(ExecState*, Structure*);
typedef char* DFG_OPERATION (*P_DFGOperation_EStPS)(ExecState*, Structure*, void*, size_t);
typedef char* DFG_OPERATION (*P_DFGOperation_EStSS)(ExecState*, Structure*, size_t, size_t);
typedef char* DFG_OPERATION (*P_DFGOperation_EStZ)(ExecState*, Structure*, int32_t);
typedef StringImpl* DFG_OPERATION (*Str_DFGOperation_EJss)(ExecState*, JSString*);

typedef void (*V_DFGDebugOperation_EPP)(ExecState*, void*, void*);

} // extern "C"
} // namespace DFG
} // namespace JSC

#endif
