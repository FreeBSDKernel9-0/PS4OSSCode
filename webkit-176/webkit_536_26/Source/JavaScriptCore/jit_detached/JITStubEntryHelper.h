// Copyright (C) 2012 Sony Computer Entertainment Inc.
// All Rights Reserved.

/*!
 * @brief This file is an extension to JITStubEntries.h but mainly provided so
 *        that it can be #include'ed from sample apps who don't have macros
 *        s.a. ENABLE(), OS(), etc... defined.
 */

#ifndef JITStubEntryHelper_h
#define JITStubEntryHelper_h

#define CTI_STUB_ENTRIES_DFG_OPERATIONS \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<void (*)(ExecState*)>, compileOSRExit_vmstub); \
    CTI_STUB_ENTRY(RemotePointerWrapper,                        lookupExceptionHandler); \
    CTI_STUB_ENTRY(RemotePointerWrapper,                        lookupExceptionHandlerInStub); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_EJ>,    dfgConvertJSValueToBoolean); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_EJ>,    dfgConvertJSValueToInt32); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<D_DFGOperation_EJ>,    dfgConvertJSValueToNumber); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<D_DFGOperation_DD>,    fmod_vmstub); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<Z_DFGOperation_D>,     toInt32_vmstub); \
    \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EA>,    operationArrayPop); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EJA>,   operationArrayPush); \
    CTI_STUB_ENTRY(RemotePointerWrapper,                        operationCallCustomGetter); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_ECC>,   operationCallGetter); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_EJJ>,   operationCompareEq); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_EJJ>,   operationCompareGreater); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_EJJ>,   operationCompareGreaterEq); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_EJJ>,   operationCompareLess); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_EJJ>,   operationCompareLessEq); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_EJJ>,   operationCompareStrictEq); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_EJJ>,   operationCompareStrictEqCell); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EJ>,    operationConvertThis); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<C_DFGOperation_E>,     operationCreateActivation); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<C_DFGOperation_EC>,    operationCreateThis); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<C_DFGOperation_ECC>,   operationCreateThisInlined); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EJI>,   operationGetById); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EJI>,   operationGetByIdBuildList); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EJI>,   operationGetByIdProtoBuildList); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EJI>,   operationGetByIdOptimize); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EJJ>,   operationGetByVal); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_J>,     operationIsFunction); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_J>,     operationIsObject); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<P_DFGOperation_E>,     operationLinkCall); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<P_DFGOperation_E>,     operationLinkConstruct); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EPS>,   operationNewArray); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_ESS>,   operationNewArrayBuffer); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<C_DFGOperation_EC>,    operationNewFunction); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<C_DFGOperation_EC>,    operationNewFunctionExpression); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<C_DFGOperation_E>,     operationNewObject); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EP>,    operationNewRegexp); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,  operationPutByIdDirectNonStrict); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,  operationPutByIdDirectNonStrictBuildList); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,  operationPutByIdDirectNonStrictOptimize); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,  operationPutByIdDirectStrict); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,  operationPutByIdDirectStrictBuildList); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,  operationPutByIdDirectStrictOptimize); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,  operationPutByIdNonStrict); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,  operationPutByIdNonStrictBuildList); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,  operationPutByIdNonStrictOptimize); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,  operationPutByIdStrict); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,  operationPutByIdStrictBuildList); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,  operationPutByIdStrictOptimize); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EAZJ>,  operationPutByValBeyondArrayBoundsNonStrict); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EAZJ>,  operationPutByValBeyondArrayBoundsStrict); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJJJ>,  operationPutByValNonStrict); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJJJ>,  operationPutByValStrict); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_ECC>,   operationRegExpExec); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_ECC>,   operationRegExpTest); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EI>,    operationResolve); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EI>,    operationResolveBase); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EI>,    operationResolveBaseStrictPut); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EGI>,   operationResolveGlobal); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EPS>,   operationStrCat); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EC>,    operationTearOffActivation); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EJ>,    operationToPrimitive); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EJJ>,   operationValueAdd); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EJJ>,   operationValueAddNotNumber); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<P_DFGOperation_E>,     operationVirtualCall); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<P_DFGOperation_E>,     operationVirtualConstruct);

#define CTI_STUB_ENTRIES_DFG \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoid,                   cti_optimize_from_loop); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoid,                   cti_optimize_from_ret);

#define CTI_STUB_ENTRIES \
    CTI_STUB_ENTRY(RemoteFunctionReturningInt,     cti_has_property); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_add); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_bitand); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_bitor); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_bitxor); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_call_NotJSFunction); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoidPtr, cti_op_call_arityCheck); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_call_eval); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoidPtr, cti_op_call_jitCompile); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoid,    cti_op_check_has_instance); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_construct_NotJSConstruct); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoidPtr, cti_op_construct_arityCheck); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoidPtr, cti_op_construct_jitCompile); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_convert_this); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_create_arguments); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_create_this); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoid,    cti_op_debug); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_del_by_id); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_del_by_val); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_div); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_ensure_property_exists); \
    CTI_STUB_ENTRY(RemoteFunctionReturningInt,     cti_op_eq); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_get_by_id); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_get_by_id_array_fail); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_get_by_id_custom_stub); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_get_by_id_generic); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_get_by_id_getter_stub); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_get_by_id_method_check); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_get_by_id_method_check_update); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_get_by_id_proto_list); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_get_by_id_self_fail); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_get_by_id_string_fail); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_get_by_val); \
    CTI_STUB_ENTRY(RemoteFunctionReturningCell,    cti_op_get_pnames); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_greater); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_greatereq); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_in); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_instanceof); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_is_function); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_is_object); \
    CTI_STUB_ENTRY(RemoteFunctionReturningInt,     cti_op_jgreater); \
    CTI_STUB_ENTRY(RemoteFunctionReturningInt,     cti_op_jgreatereq); \
    CTI_STUB_ENTRY(RemoteFunctionReturningInt,     cti_op_jless); \
    CTI_STUB_ENTRY(RemoteFunctionReturningInt,     cti_op_jlesseq); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoid,    cti_op_jmp_scopes); \
    CTI_STUB_ENTRY(RemoteFunctionReturningInt,     cti_op_jtrue); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoidPtr, cti_op_load_varargs); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_less); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_lesseq); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_lshift); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_mod); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_mul); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_negate); \
    CTI_STUB_ENTRY(RemoteFunctionReturningCell,    cti_op_new_array); \
    CTI_STUB_ENTRY(RemoteFunctionReturningCell,    cti_op_new_array_buffer); \
    CTI_STUB_ENTRY(RemoteFunctionReturningCell,    cti_op_new_func); \
    CTI_STUB_ENTRY(RemoteFunctionReturningCell,    cti_op_new_func_exp); \
    CTI_STUB_ENTRY(RemoteFunctionReturningCell,    cti_op_new_object); \
    CTI_STUB_ENTRY(RemoteFunctionReturningCell,    cti_op_new_regexp); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_not); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_nstricteq); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_pre_dec); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_pre_inc); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoid,    cti_op_profile_did_call); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoid,    cti_op_profile_will_call); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoid,    cti_op_pop_scope); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_post_dec); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_post_inc); \
    CTI_STUB_ENTRY(RemoteFunctionReturningCell,    cti_op_push_activation); \
    CTI_STUB_ENTRY(RemoteFunctionReturningCell,    cti_op_push_new_scope); \
    CTI_STUB_ENTRY(RemoteFunctionReturningCell,    cti_op_push_scope); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoid,    cti_op_put_by_id); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoid,    cti_op_put_by_id_direct); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoid,    cti_op_put_by_id_direct_fail); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoid,    cti_op_put_by_id_direct_generic); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoid,    cti_op_put_by_id_fail); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoid,    cti_op_put_by_id_generic); \
    CTI_STUB_ENTRY(RemoteFunctionReturningCell,    cti_op_put_by_id_transition_realloc); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoid,    cti_op_put_by_index); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoid,    cti_op_put_by_val); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoid,    cti_op_put_getter_setter); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_resolve); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_resolve_base); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_resolve_base_strict_put); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_resolve_global); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_resolve_skip); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_resolve_with_base); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_resolve_with_this); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_rshift); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_strcat); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_stricteq); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_sub); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoidPtr, cti_op_switch_char); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoidPtr, cti_op_switch_imm); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoidPtr, cti_op_switch_string); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoid,    cti_op_tear_off_activation); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoid,    cti_op_tear_off_arguments); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoidPtr, cti_op_throw); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoid,    cti_op_throw_reference_error); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_to_jsnumber); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_to_primitive); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_typeof); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_op_urshift); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoidPtr, cti_register_file_check); \
    CTI_STUB_ENTRY(RemoteFunctionReturningInt,     cti_timeout_check); \
    CTI_STUB_ENTRY(RemoteFunctionReturningValue,   cti_to_object); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoidPtr, cti_vm_lazyLinkCall); \
    CTI_STUB_ENTRY(RemoteFunctionReturningVoidPtr, cti_vm_lazyLinkConstruct);

#define CLASSINFO_STUB_ENTRIES \
    CLASSINFO_STUB_ENTRY(ArrayConstructor); \
    CLASSINFO_STUB_ENTRY(ArrayPrototype); \
    CLASSINFO_STUB_ENTRY(BooleanConstructor); \
    CLASSINFO_STUB_ENTRY(DateConstructor); \
    CLASSINFO_STUB_ENTRY(DateInstance); \
    CLASSINFO_STUB_ENTRY(DatePrototype); \
    CLASSINFO_STUB_ENTRY(ErrorConstructor); \
    CLASSINFO_STUB_ENTRY(FunctionConstructor); \
    CLASSINFO_STUB_ENTRY(FunctionPrototype); \
    CLASSINFO_STUB_ENTRY(InternalFunction); \
    CLASSINFO_STUB_ENTRY(JSActivation); \
    CLASSINFO_STUB_ENTRY(JSArray); \
    CLASSINFO_STUB_ENTRY(JSBoundFunction); \
    CLASSINFO_STUB_ENTRY(JSFinalObject); \
    CLASSINFO_STUB_ENTRY(JSFunction); \
    CLASSINFO_STUB_ENTRY(JSGlobalObject); \
    CLASSINFO_STUB_ENTRY(JSObject); \
    CLASSINFO_STUB_ENTRY(JSString); \
    CLASSINFO_STUB_ENTRY(MathObject); \
    CLASSINFO_STUB_ENTRY(NativeErrorConstructor); \
    CLASSINFO_STUB_ENTRY(NumberConstructor); \
    CLASSINFO_STUB_ENTRY(ObjectConstructor); \
    CLASSINFO_STUB_ENTRY(ObjectPrototype); \
    CLASSINFO_STUB_ENTRY(RegExpConstructor); \
    CLASSINFO_STUB_ENTRY(RegExpObject); \
    CLASSINFO_STUB_ENTRY(RegExpPrototype); \
    CLASSINFO_STUB_ENTRY(StrictModeTypeErrorFunction); \
    CLASSINFO_STUB_ENTRY(StringConstructor); \
    CLASSINFO_STUB_ENTRY(StringPrototype); \
    CLASSINFO_STUB_ENTRY(StringObject); \
    CLASSINFO_STUB_ENTRY(Structure);

#endif // #ifndef JITStubEntryHelper_h
