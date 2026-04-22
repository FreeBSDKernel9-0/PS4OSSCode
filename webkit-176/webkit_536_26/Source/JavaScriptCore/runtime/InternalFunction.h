/*
 *  Copyright (C) 1999-2000 Harri Porten (porten@kde.org)
 *  Copyright (C) 2003, 2006, 2007, 2008 Apple Inc. All rights reserved.
 *  Copyright (C) 2007 Cameron Zwarich (cwzwarich@uwaterloo.ca)
 *  Copyright (C) 2007 Maks Orlovich
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 *
 */

#ifndef InternalFunction_h
#define InternalFunction_h

#include "JSObject.h"
#include "Identifier.h"

namespace JSC {

    class FunctionPrototype;

    class InternalFunction : public JSNonFinalObject {
    public:
        typedef JSNonFinalObject Base;

#if ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT
    private:
        friend void JSCBridge::initializeCompilerSharedData();
        template <typename T> friend T JSCBridge::mapFromVMToCompiler(T) const;
        static JS_EXPORTDATA ClassInfo s_info;
#else
    public:
        static JS_EXPORTDATA const ClassInfo s_info;
#endif

        JS_EXPORT_PRIVATE const UString& name(ExecState*);
        const UString displayName(ExecState*);
        const UString calculatedDisplayName(ExecState*);

#if !ENABLE(DETACHED_JIT) || (ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT)
        static Structure* createStructure(JSGlobalData& globalData, JSGlobalObject* globalObject, JSValue proto) 
        { 
            return Structure::create(globalData, globalObject, proto, TypeInfo(ObjectType, StructureFlags), &s_info); 
        }
#endif // #if !ENABLE(DETACHED_JIT) || (ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT)

    protected:
        static const unsigned StructureFlags = ImplementsHasInstance | JSObject::StructureFlags;

        JS_EXPORT_PRIVATE InternalFunction(JSGlobalObject*, Structure*);

        JS_EXPORT_PRIVATE void finishCreation(JSGlobalData&, const Identifier& name);

        static CallType getCallData(JSCell*, CallData&);
    };

    InternalFunction* asInternalFunction(JSValue);

#if !ENABLE(DETACHED_JIT) || (ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT)
    inline InternalFunction* asInternalFunction(JSValue value)
    {
        ASSERT(asObject(value)->inherits(&InternalFunction::s_info));
        return static_cast<InternalFunction*>(asObject(value));
    }
#endif // #if !ENABLE(DETACHED_JIT) || (ENABLE(DETACHED_JIT) && !BUILDING_DETACHED_JIT)

} // namespace JSC

#endif // InternalFunction_h
