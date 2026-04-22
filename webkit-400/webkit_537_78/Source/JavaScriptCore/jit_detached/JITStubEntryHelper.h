// Copyright (C) 2012 Sony Interactive Entertainment Inc.
// All Rights Reserved.

/*!
 * @brief This file is an extension to JITStubEntries.h but mainly provided so
 *        that it can be #include'ed from sample apps who don't have macros
 *        s.a. ENABLE(), OS(), etc... defined.
 */

#ifndef JITStubEntryHelper_h
#define JITStubEntryHelper_h

// see DFGOperations.h
#define CTI_STUB_ENTRIES_DFG_OPERATIONS \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<void (*)(ExecState*)>,      compileOSRExit_vmstub); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<D_DFGOperation_DD>,         fmod_vmstub); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<Z_DFGOperation_D>,          toInt32_vmstub); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<C_DFGOperation_EZ>,         operationStringFromCharCode); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<C_DFGOperation_ESt>,        operationNewObject); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<C_DFGOperation_EOZ>,        operationCreateThis); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EJ>,         operationConvertThis); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EJJ>,        operationValueAdd); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EJJ>,        operationValueAddNotNumber); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EJJ>,        operationGetByVal); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_ECJ>,        operationGetByValCell); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EAZ>,        operationGetByValArrayInt); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EJI>,        operationGetById); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EJI>,        operationGetByIdBuildList); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EJI>,        operationGetByIdProtoBuildList); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EJI>,        operationGetByIdOptimize); \
    CTI_STUB_ENTRY(RemotePointerWrapper,                             operationCallCustomGetter); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_ECC>,        operationCallGetter); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_W>,          operationNotifyGlobalVarWrite); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EIRo>,       operationResolve); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EIRoPtbo>,   operationResolveBase); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EIRoPtbo>,   operationResolveBaseStrictPut); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EGriJsgI>,   operationResolveGlobal); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EJ>,         operationToPrimitive); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<P_DFGOperation_EStPS>,      operationNewArray); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<P_DFGOperation_EStSS>,      operationNewArrayBuffer); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<P_DFGOperation_ESt>,        operationNewEmptyArray); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<P_DFGOperation_EStZ>,       operationNewArrayWithSize); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EP>,         operationNewRegexp); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJJJ>,       operationPutByValStrict); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJJJ>,       operationPutByValNonStrict); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_ECJJ>,       operationPutByValCellStrict); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_ECJJ>,       operationPutByValCellNonStrict); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EOZJ>,       operationPutByValBeyondArrayBoundsStrict); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EOZJ>,       operationPutByValBeyondArrayBoundsNonStrict); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EOZD>,       operationPutDoubleByValBeyondArrayBoundsStrict); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EOZD>,       operationPutDoubleByValBeyondArrayBoundsNonStrict); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EJA>,        operationArrayPush); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EDA>,        operationArrayPushDouble); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EA>,         operationArrayPop); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EA>,         operationArrayPopAndRecoverLength); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_ECC>,        operationRegExpExec); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,       operationPutByIdStrict); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,       operationPutByIdNonStrict); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,       operationPutByIdDirectStrict); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,       operationPutByIdDirectNonStrict); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,       operationPutByIdStrictOptimize); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,       operationPutByIdNonStrictOptimize); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,       operationPutByIdDirectStrictOptimize); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,       operationPutByIdDirectNonStrictOptimize); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,       operationPutByIdStrictBuildList); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,       operationPutByIdNonStrictBuildList); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,       operationPutByIdDirectStrictBuildList); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_EJCI>,       operationPutByIdDirectNonStrictBuildList); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_ECC>,        operationRegExpTest); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_EJJ>,        operationCompareLess); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_EJJ>,        operationCompareLessEq); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_EJJ>,        operationCompareGreater); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_EJJ>,        operationCompareGreaterEq); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_EJJ>,        operationCompareEq); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_ECC>,        operationCompareStringEq); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_EJJ>,        operationCompareStrictEqCell); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_EJJ>,        operationCompareStrictEq); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<P_DFGOperation_E>,          operationVirtualCall); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<P_DFGOperation_E>,          operationLinkCall); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<P_DFGOperation_E>,          operationLinkClosureCall); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<P_DFGOperation_E>,          operationVirtualConstruct); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<P_DFGOperation_E>,          operationLinkConstruct); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<C_DFGOperation_E>,          operationCreateActivation); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<C_DFGOperation_E>,          operationCreateArguments); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<C_DFGOperation_EIcf>,       operationCreateInlinedArguments); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_ECC>,        operationTearOffArguments); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGOperation_ECCIcf>,     operationTearOffInlinedArguments); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EZ>,         operationGetArgumentsLength); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EZIcfZ>,     operationGetInlinedArgumentByVal); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EZZ>,        operationGetArgumentByVal); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<C_DFGOperation_EC>,         operationNewFunctionNoCheck); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<J_DFGOperation_EC>,         operationNewFunction); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<C_DFGOperation_EC>,         operationNewFunctionExpression); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<D_DFGOperation_ZZ>,         operationFModOnInts); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_EJ>,         operationIsObject); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_J>,          operationIsFunction); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<C_DFGOperation_EC>,         operationTypeOf); \
    CTI_STUB_ENTRY(RemotePointerWrapper,                             operationReallocateStorageAndFinishPut); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<P_DFGOperation_E>,          operationAllocatePropertyStorageWithInitialCapacity); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<P_DFGOperation_ES>,         operationAllocatePropertyStorage); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<P_DFGOperation_EO>,         operationReallocateButterflyToHavePropertyStorageWithInitialCapacity); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<P_DFGOperation_EOS>,        operationReallocateButterflyToGrowPropertyStorage); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<P_DFGOperation_EC>,         operationEnsureInt32); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<P_DFGOperation_EC>,         operationEnsureDouble); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<P_DFGOperation_EC>,         operationEnsureContiguous); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<P_DFGOperation_EC>,         operationRageEnsureContiguous); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<P_DFGOperation_EC>,         operationEnsureArrayStorage); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<Str_DFGOperation_EJss>,     operationResolveRope); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<C_DFGOperation_EJssSt>,     operationNewStringObject); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<C_DFGOperation_EC>,         operationToStringOnCell); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<C_DFGOperation_EJ>,         operationToString); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<C_DFGOperation_EJssJss>,    operationMakeRope2); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<C_DFGOperation_EJssJssJss>, operationMakeRope3); \
    CTI_STUB_ENTRY(RemotePointerWrapper,                             lookupExceptionHandler); \
    CTI_STUB_ENTRY(RemotePointerWrapper,                             lookupExceptionHandlerInStub); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_EJ>,         dfgConvertJSValueToBoolean); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<S_DFGOperation_EJ>,         dfgConvertJSValueToInt32); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<V_DFGDebugOperation_EPP>,   debugOperationPrintSpeculationFailure); \
    CTI_STUB_ENTRY(RemotePointerWrapper,                             triggerReoptimizationNow);

// see JITStubs.h
#define CTI_STUB_ENTRIES_DFG \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoid, cti_optimize);

// see JITStubs.h
#define CTI_STUB_ENTRIES \
    \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_add); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_bitand); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_bitor); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_bitxor); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_call_NotJSFunction); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_call_eval); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_construct_NotJSConstruct); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_check_has_instance); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_create_this); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_convert_this); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_create_arguments); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_del_by_id); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_del_by_val); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_div); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_get_by_id); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_get_by_id_array_fail); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_get_by_id_custom_stub); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_get_by_id_generic); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_get_by_id_getter_stub); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_get_by_id_proto_fail); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_get_by_id_proto_list); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_get_by_id_proto_list_full); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_get_by_id_self_fail); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_get_by_id_string_fail); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_get_by_val); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_get_by_val_generic); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_get_by_val_string); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_in); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_instanceof); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_is_function); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_is_object); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_less); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_lesseq); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_greater); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_greatereq); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_lshift); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_mod); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_mul); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_negate); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_not); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_nstricteq); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_dec); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_inc); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_resolve); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_resolve_base); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_resolve_base_strict_put); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_resolve_with_base); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_resolve_with_this); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoid,    cti_op_put_to_base); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_rshift); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_strcat); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_stricteq); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_sub); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_to_number); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_to_primitive); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_typeof); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_op_urshift); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningValue,   cti_to_object); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningObject,  cti_op_new_array); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningObject,  cti_op_new_array_with_size); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningObject,  cti_op_new_array_buffer); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningObject,  cti_op_new_func); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningObject,  cti_op_new_func_exp); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningObject,  cti_op_new_object); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningObject,  cti_op_new_regexp); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningObject,  cti_op_push_activation); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoid,    cti_op_push_name_scope); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoid,    cti_op_push_with_scope); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningObject,  cti_op_put_by_id_transition_realloc); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningObject,  cti_op_get_pnames); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningInt,     cti_op_eq); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningInt,     cti_op_eq_strings); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningInt,     cti_op_jless); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningInt,     cti_op_jlesseq); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningInt,     cti_op_jgreater); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningInt,     cti_op_jgreatereq); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningInt,     cti_op_jtrue); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoidPtr, cti_op_load_varargs); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoid,    cti_handle_watchdog_timer); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningInt,     cti_has_property); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoid,    cti_op_debug); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoid,    cti_op_pop_scope); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoid,    cti_op_profile_did_call); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoid,    cti_op_profile_will_call); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoid,    cti_op_put_by_id); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoid,    cti_op_put_by_id_fail); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoid,    cti_op_put_by_id_generic); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoid,    cti_op_put_by_id_direct); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoid,    cti_op_put_by_id_direct_fail); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoid,    cti_op_put_by_id_direct_generic); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoid,    cti_op_put_by_index); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoid,    cti_op_put_by_val); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoid,    cti_op_put_by_val_generic); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoid,    cti_op_put_getter_setter); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoid,    cti_op_init_global_const_check); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoid,    cti_op_tear_off_activation); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoid,    cti_op_tear_off_arguments); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoid,    cti_op_throw_static_error); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoidPtr, cti_op_call_arityCheck); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoidPtr, cti_op_construct_arityCheck); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoidPtr, cti_op_call_jitCompile); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoidPtr, cti_op_construct_jitCompile); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoidPtr, cti_op_switch_char); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoidPtr, cti_op_switch_imm); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoidPtr, cti_op_switch_string); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoidPtr, cti_op_throw); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoidPtr, cti_stack_check); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoidPtr, cti_vm_lazyLinkCall); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoidPtr, cti_vm_lazyLinkClosureCall); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoidPtr, cti_vm_lazyLinkConstruct); \
    CTI_STUB_ENTRY(RemoteCtiFunctionReturningVoidPtr, cti_vm_throw);

#define CTI_STUB_ENTRIES_LLINT \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<void (*)()>, llint_native_call_trampoline); \
    CTI_STUB_ENTRY(RemoteFunctionWrapper<void (*)()>, llint_native_construct_trampoline);

#define CLASSINFO_STUB_ENTRIES \
    CLASSINFO_STUB_ENTRY(Arguments); \
    CLASSINFO_STUB_ENTRY(ArrayConstructor); \
    CLASSINFO_STUB_ENTRY(ArrayPrototype); \
    CLASSINFO_STUB_ENTRY(BooleanConstructor); \
    CLASSINFO_STUB_ENTRY(DateConstructor); \
    CLASSINFO_STUB_ENTRY(DateInstance); \
    CLASSINFO_STUB_ENTRY(DatePrototype); \
    CLASSINFO_STUB_ENTRY(ErrorConstructor); \
    CLASSINFO_STUB_ENTRY(FunctionConstructor); \
    CLASSINFO_STUB_ENTRY(FunctionExecutable); \
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
