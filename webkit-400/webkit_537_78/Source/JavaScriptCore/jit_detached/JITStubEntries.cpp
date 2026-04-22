// Copyright (C) 2012 Sony Interactive Entertainment Inc.
// All Rights Reserved.

#include "config.h"

#if ENABLE(JIT) 

#include "JITStubEntries.h"

#include <limits>

#if ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT

#include "ArrayConstructor.h"
#include "ArrayPrototype.h"
#include "BooleanConstructor.h"
#include "DateConstructor.h"
#include "DateInstance.h"
#include "DatePrototype.h"
#include "Error.h"
#include "ErrorConstructor.h"
#include "FunctionConstructor.h"
#include "FunctionPrototype.h"
#include "InternalFunction.h"
#include "JSActivation.h"
#include "JSArray.h"
#include "JSBoundFunction.h"
#include "JSCJSValue.h"
#include "JSFunction.h"
#include "JSGlobalObject.h"
#include "JSObject.h"
#include "JSString.h"
#include "MathObject.h"
#include "NativeErrorConstructor.h"
#include "NumberConstructor.h"
#include "ObjectConstructor.h"
#include "ObjectPrototype.h"
#include "RegExpConstructor.h"
#include "RegExpPrototype.h"
#include "StringConstructor.h"
#include "Structure.h"

namespace JSC {

#define CTI_STUB_ENTRY(returnType, symbol) returnType symbol
    CTI_STUB_ENTRIES;

#if ENABLE(LLINT)
	CTI_STUB_ENTRIES_LLINT;
#endif

#if ENABLE(DFG_JIT)
    CTI_STUB_ENTRIES_DFG;
namespace DFG {
    CTI_STUB_ENTRIES_DFG_OPERATIONS;
}
#endif

#undef  CTI_STUB_ENTRY

#define CLASSINFO_STUB_ENTRY(classname) namespace classname##Stub { RemoteClassInfoPtr s_info; } //JS_EXPORTDATA ClassInfo classname::s_info;
    CLASSINFO_STUB_ENTRIES;
#undef  CLASSINFO_STUB_ENTRY

    RemotePointerWrapper ctiVMThrowTrampoline;

namespace RemoteStubs {
    RemotePointerWrapper oneConstant;
    RemotePointerWrapper zeroConstant;
    RemotePointerWrapper halfConstant;
    RemotePointerWrapper negativeHalfConstant;
    RemotePointerWrapper negativeZeroConstant;
    RemotePointerWrapper NaN;
    RemotePointerWrapper twoToThe32;
    RemotePointerWrapper byteMax;
} // namespace RemoteStubs

namespace Yarr {
namespace RemoteStubs {
    char const * regExp_spacesData;
    char const * regExp_wordcharData;
}
}

} // namespace JSC

#endif // #if ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT

namespace JSC {

    DEFINE_REMOTE_VAR(const double, oneConstant, 1.0);
    DEFINE_REMOTE_VAR(const double, zeroConstant, 0.0);
    DEFINE_REMOTE_VAR(const double, halfConstant, 0.5);
    DEFINE_REMOTE_VAR(const double, negativeHalfConstant, -0.5);
    DEFINE_REMOTE_VAR(const double, negativeZeroConstant, -0.0);
    DEFINE_REMOTE_VAR(const double, NaN, std::numeric_limits<double>::quiet_NaN());
    DEFINE_REMOTE_VAR(const double, twoToThe32, (double)0x100000000ull);
    DEFINE_REMOTE_VAR(const double, byteMax, 255);

} // namespace JSC

#endif // #if ENABLE(JIT)

