/*
 *  Copyright (C) 1999-2001 Harri Porten (porten@kde.org)
 *  Copyright (C) 2001 Peter Kelly (pmk@post.com)
 *  Copyright (C) 2003, 2004, 2005, 2006, 2007, 2008 Apple Inc. All rights reserved.
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

#ifndef ClassInfo_h
#define ClassInfo_h

#include "CallFrame.h"
#include "ConstructData.h"
#include "JSCell.h"
#if ENABLE(DETACHED_JIT)
#include "JSCBridge.h"
#endif

namespace JSC {

class HashEntry;
struct HashTable;

struct MethodTable {
    typedef void (*DestroyFunctionPtr)(JSCell*);
    DestroyFunctionPtr destroy;

    typedef void (*VisitChildrenFunctionPtr)(JSCell*, SlotVisitor&);
    VisitChildrenFunctionPtr visitChildren;

    typedef void (*CopyBackingStoreFunctionPtr)(JSCell*, CopyVisitor&);
    CopyBackingStoreFunctionPtr copyBackingStore;

    typedef CallType (*GetCallDataFunctionPtr)(JSCell*, CallData&);
    GetCallDataFunctionPtr getCallData;

    typedef ConstructType (*GetConstructDataFunctionPtr)(JSCell*, ConstructData&);
    GetConstructDataFunctionPtr getConstructData;

    typedef void (*PutFunctionPtr)(JSCell*, ExecState*, PropertyName propertyName, JSValue, PutPropertySlot&);
    PutFunctionPtr put;

    typedef void (*PutByIndexFunctionPtr)(JSCell*, ExecState*, unsigned propertyName, JSValue, bool shouldThrow);
    PutByIndexFunctionPtr putByIndex;

    typedef bool (*DeletePropertyFunctionPtr)(JSCell*, ExecState*, PropertyName);
    DeletePropertyFunctionPtr deleteProperty;

    typedef bool (*DeletePropertyByIndexFunctionPtr)(JSCell*, ExecState*, unsigned);
    DeletePropertyByIndexFunctionPtr deletePropertyByIndex;

    typedef bool (*GetOwnPropertySlotFunctionPtr)(JSCell*, ExecState*, PropertyName, PropertySlot&);
    GetOwnPropertySlotFunctionPtr getOwnPropertySlot;

    typedef bool (*GetOwnPropertySlotByIndexFunctionPtr)(JSCell*, ExecState*, unsigned, PropertySlot&);
    GetOwnPropertySlotByIndexFunctionPtr getOwnPropertySlotByIndex;

    typedef JSObject* (*ToThisObjectFunctionPtr)(JSCell*, ExecState*);
    ToThisObjectFunctionPtr toThisObject;

    typedef JSValue (*DefaultValueFunctionPtr)(const JSObject*, ExecState*, PreferredPrimitiveType);
    DefaultValueFunctionPtr defaultValue;

    typedef void (*GetOwnPropertyNamesFunctionPtr)(JSObject*, ExecState*, PropertyNameArray&, EnumerationMode);
    GetOwnPropertyNamesFunctionPtr getOwnPropertyNames;

    typedef void (*GetOwnNonIndexPropertyNamesFunctionPtr)(JSObject*, ExecState*, PropertyNameArray&, EnumerationMode);
    GetOwnNonIndexPropertyNamesFunctionPtr getOwnNonIndexPropertyNames;

    typedef void (*GetPropertyNamesFunctionPtr)(JSObject*, ExecState*, PropertyNameArray&, EnumerationMode);
    GetPropertyNamesFunctionPtr getPropertyNames;

    typedef String (*ClassNameFunctionPtr)(const JSObject*);
    ClassNameFunctionPtr className;

    typedef bool (*CustomHasInstanceFunctionPtr)(JSObject*, ExecState*, JSValue);
    CustomHasInstanceFunctionPtr customHasInstance;

    typedef void (*PutWithAttributesFunctionPtr)(JSObject*, ExecState*, PropertyName propertyName, JSValue, unsigned attributes);
    PutWithAttributesFunctionPtr putDirectVirtual;

    typedef bool (*DefineOwnPropertyFunctionPtr)(JSObject*, ExecState*, PropertyName, PropertyDescriptor&, bool);
    DefineOwnPropertyFunctionPtr defineOwnProperty;

    typedef bool (*GetOwnPropertyDescriptorFunctionPtr)(JSObject*, ExecState*, PropertyName, PropertyDescriptor&);
    GetOwnPropertyDescriptorFunctionPtr getOwnPropertyDescriptor;
};

#define CREATE_MEMBER_CHECKER(member) \
    template <typename T> \
    struct MemberCheck##member { \
        struct Fallback { \
            void member(...); \
        }; \
        struct Derived : T, Fallback { }; \
        template <typename U, U> struct Check; \
        typedef char Yes[2]; \
        typedef char No[1]; \
        template <typename U> \
        static No &func(Check<void (Fallback::*)(...), &U::member>*); \
        template <typename U> \
        static Yes &func(...); \
        enum { has = sizeof(func<Derived>(0)) == sizeof(Yes) }; \
    }

#define HAS_MEMBER_NAMED(klass, name) (MemberCheck##name<klass>::has)

#define CREATE_METHOD_TABLE(ClassName) { \
        &ClassName::destroy, \
        &ClassName::visitChildren, \
        &ClassName::copyBackingStore, \
        &ClassName::getCallData, \
        &ClassName::getConstructData, \
        &ClassName::put, \
        &ClassName::putByIndex, \
        &ClassName::deleteProperty, \
        &ClassName::deletePropertyByIndex, \
        &ClassName::getOwnPropertySlot, \
        &ClassName::getOwnPropertySlotByIndex, \
        &ClassName::toThisObject, \
        &ClassName::defaultValue, \
        &ClassName::getOwnPropertyNames, \
        &ClassName::getOwnNonIndexPropertyNames, \
        &ClassName::getPropertyNames, \
        &ClassName::className, \
        &ClassName::customHasInstance, \
        &ClassName::putDirectVirtual, \
        &ClassName::defineOwnProperty, \
        &ClassName::getOwnPropertyDescriptor, \
    }, \
    ClassName::TypedArrayStorageType

struct ClassInfo {
    /**
     * A string denoting the class name. Example: "Window".
     */
    const char* className;

    /**
     * Pointer to the class information of the base class.
     * 0L if there is none.
     */
    const ClassInfo* parentClass;
    /**
     * Static hash-table of properties.
     * For classes that can be used from multiple threads, it is accessed via a getter function that would typically return a pointer to thread-specific value.
     */
    const HashTable* propHashTable(ExecState* exec) const
    {
        if (classPropHashTableGetterFunction)
            return classPropHashTableGetterFunction(exec);
        return staticPropHashTable;
    }
        
    bool isSubClassOf(const ClassInfo* other) const
    {
#if ENABLE(DETACHED_JIT) && BUILDING_DETACHED_JIT
        JSCBridge & bridge(*JSCBridge::sharedInstance());
        ClassInfo const * me(bridge.mapFromVMToCompiler(this));
        other = bridge.mapFromVMToCompiler(other);
        for (const ClassInfo* ci = me; ci; ci = ci->parentClass) {
            ci = ci ? bridge.mapFromVMToCompiler(ci) : ci;
            if (ci == other)
                return true;
        }
        return false;
#else
        for (const ClassInfo* ci = this; ci; ci = ci->parentClass) {
            if (ci == other)
                return true;
        }
        return false;
#endif
    }

    bool hasStaticProperties() const
    {
        for (const ClassInfo* ci = this; ci; ci = ci->parentClass) {
            if (ci->staticPropHashTable || ci->classPropHashTableGetterFunction)
                return true;
        }
        return false;
    }

    const HashTable* staticPropHashTable;
    typedef const HashTable* (*ClassPropHashTableGetterFunction)(ExecState*);
    const ClassPropHashTableGetterFunction classPropHashTableGetterFunction;

    MethodTable methodTable;

    TypedArrayType typedArrayStorageType;

#if ENABLE(DETACHED_JIT)
        ClassInfo(
            const char* className,
            const ClassInfo* parentClass,
            const HashTable* staticPropHashTable,
            ClassPropHashTableGetterFunction classPropHashTableGetterFunction,
            MethodTable const & methodTable,
            TypedArrayType typedArrayStorageType)
            : className(className)
            , parentClass(parentClass)
            , staticPropHashTable(staticPropHashTable)
            , classPropHashTableGetterFunction(classPropHashTableGetterFunction)
            , methodTable(methodTable)
            , typedArrayStorageType(typedArrayStorageType)
        {
            JSCBridge::registerRuntimeClassinfo(this);
        }
    private:
        ClassInfo(ClassInfo const & other);
        ClassInfo & operator=(ClassInfo const & other); 
#endif
};

} // namespace JSC

#endif // ClassInfo_h
