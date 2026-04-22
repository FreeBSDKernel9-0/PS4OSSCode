{ 
    'includes': [
        '../JavaScriptCore.gypi',
        ],

    'variables': {
        'javascriptcore_files' : [
            ],
        }, # variables

    'targets': [
        {
            'target_name': 'JavaScriptCoreGenerated',
            'type'       : 'none',
            'actions': [
                {
                    'action_name' : 'Generate JavaScriptCore Derived Sources',
                    'inputs'      : [ 'generate-derived-sources-manx.sh' ],
                    'outputs'     : [ '<@(javascriptcore_derived_source_files)' ],
                    'action'      : [ 'bash', 'generate-derived-sources-manx.sh', '<(PRODUCT_DIR)/DerivedSources'],
                    },
                ],
            }, # DerivedSources target

        {
            'target_name'   : 'JavaScriptCore',
            'type'          : 'static_library', 
            'msvs_guid' : '9A334014-7543-47BF-95C9-000000000001',
            'dependencies'  : [
                'WTF',
                ],
            'direct_dependent_settings' : {
                'include_dirs' : [ '<@(jscore_include_dirs)' ]
                }, # direct_dependent_settings
            'include_dirs' : [ '<@(jscore_include_dirs)' ],
            'defines' : [
                'BUILDING_JavaScriptCore',
                ],
            'sources': [
                '<@(javascriptcore_files)',
                '<@(javascriptcore_publicheader_files)',
                '<@(javascriptcore_privateheader_files)',
                '<@(javascriptcore_derived_source_files)',
                ],
            'sources/': [
                ['exclude', 'API/tests/'],
                ['exclude', 'ForwardingHeaders/'],
                ['exclude', '(?<!unicode)/icu/'],
                ['exclude', 'os-win32/'],
                ['exclude', 'wtf/url/'],
                ['exclude', 'BSTR[^/]*$'],
                ['exclude', 'CF[.][^/]*$'],
                ['exclude', 'JSNumberCell.*$'],
                ['exclude', 'TracingDtrace.h'],
                ],
            'conditions' : [
                ['OS == "win" and _type == "shared_library"', {
                    'libraries' : [
                        'libicrt.lib',
                        'libicuin.lib',
                        'libicuuc.lib',
                        'pthreadVC2.lib',
                        'Winmm.lib',
                        ],
                    'msvs_settings': {
                        'VCLinkerTool': {
                            'ModuleDefinitionFile' : '../JavaScriptCore.vcproj/JavaScriptCore/JavaScriptCore.def',
                            },
                        },
                    }],
                ['OS == "orbis"', {
                    'sources': [
                        '../Logging.cpp'
                        ],
                    }]
                ],
            'includes' : [ 
                '../../gyp/single_jit_configuration.gypi',
                ],
            }, # JavaScriptCore target

        {
            'target_name'   : 'JSCConsole',
            'type'          : 'static_library',
            'msvs_guid'     : 'D49D97EB-3AED-420F-A9A7-6141F1498F6B',
            'dependencies'  : [
                'JavaScriptCore',
                ],
            'include_dirs'  : [
                '<@(jscore_include_dirs)',
                '../../WTF',
                ],
            'sources'       : [
                '<@(jsc_files)',
                ],
            'includes' : [ 
                '../../gyp/single_jit_configuration.gypi',
                ],
            }, # JSCConsole

        ], # targets


    'conditions' : [['OS == "orbis" or OS == "win"', {
        'targets' : [
            {
                'target_name'   : 'JSCJITCompiler',
                'type'          : 'static_library',
                'msvs_guid'     : 'F06849B4-2B23-4E9F-809A-68C90E797CC4',
                'include_dirs'  : [
                    '<@(jscore_include_dirs)',
                    '../../WTF',
                    '../../WTF/wtf',
                    ],
                'defines'       : [
                    'BUILDING_JavaScriptCore',
                    'BUILDING_DETACHED_JIT',
                    ],
                'sources'       : [
                    '../bytecode/CodeBlock.cpp',
                    '../bytecode/CodeBlock.h',
                    '../bytecode/DFGExitProfile.cpp',
                    '../bytecode/DFGExitProfile.h',
                    '../bytecode/ExecutionCounter.cpp',
                    '../bytecode/ExecutionCounter.h',
                    '../bytecode/LazyOperandValueProfile.cpp',
                    '../bytecode/LazyOperandValueProfile.h',
                    '../bytecode/MethodOfGettingAValueProfile.cpp',
                    '../bytecode/MethodOfGettingAValueProfile.h',
                    '../bytecode/PredictedType.cpp',
                    '../bytecode/PredictedType.h',
                    '../dfg/DFGAbstractState.cpp',
                    '../dfg/DFGAbstractState.h',
                    '../dfg/DFGAssemblyHelpers.cpp',
                    '../dfg/DFGAssemblyHelpers.h',
#                    '../dfg/DFGByteCodeParser.cpp',
#                    '../dfg/DFGCapabilities.cpp',
#                    '../dfg/DFGCFAPhase.cpp',
                    '../dfg/DFGCorrectableJumpPoint.cpp',
                    '../dfg/DFGCorrectableJumpPoint.h',
#                    '../dfg/DFGCSEPhase.cpp',
#                    '../dfg/DFGDriver.cpp',
#                    '../dfg/DFGFixupPhase.cpp',
#                    '../dfg/DFGGraph.cpp',
                    '../dfg/DFGJITCompiler.cpp',
#                    '../dfg/DFGNodeFlags.cpp',
#                    '../dfg/DFGOperations.cpp',
#                    '../dfg/DFGOSREntry.cpp',
                    '../dfg/DFGOSRExit.cpp',
                    '../dfg/DFGOSRExit.h',
                    '../dfg/DFGOSRExitCompiler.cpp',
                    '../dfg/DFGOSRExitCompiler.h',
                    '../dfg/DFGOSRExitCompiler64.cpp',
#                    '../dfg/DFGPhase.cpp',
#                    '../dfg/DFGPredictionPropagationPhase.cpp',
#                    '../dfg/DFGRedundantPhiEliminationPhase.cpp',
                    '../dfg/DFGRepatch.cpp',
                    '../dfg/DFGRepatch.h',
                    '../dfg/DFGSpeculativeJIT.cpp',
                    '../dfg/DFGSpeculativeJIT.h',
                    '../dfg/DFGSpeculativeJIT64.cpp',
                    '../dfg/DFGThunks.cpp',
                    '../dfg/DFGThunks.h',
#                    '../dfg/DFGVirtualRegisterAllocationPhase.cpp',
                    '../jit/ExecutableAllocatorFixedVMPool.cpp',
                    '../jit/ExecutableAllocator.cpp',
                    '../jit/JIT.cpp',
                    '../jit/JITArithmetic.cpp',
                    '../jit/JITCall.cpp',
                    '../jit/JITOpcodes.cpp',
                    '../jit/JITPropertyAccess.cpp',
                    '../jit/JITStubs.cpp',
                    '../jit/ThunkGenerators.cpp',
                    '../jit_detached/JITStubEntries.cpp',
                    '../jit_detached/JITStubEntries.h',
                    '../jit_detached/JITStubEntryHelper.h',
                    '../jit_detached/JSCBridgeComp.cpp',
                    '../jit_detached/VMProxy.cpp',
                    '../runtime/InitializeThreading.cpp',
                    '../runtime/Executable.cpp',
                    '../runtime/Executable.h',
                    '../runtime/Options.cpp',
                    '../runtime/Options.h',
                    '../runtime/JSValue.cpp',
                    '../runtime/JSValue.h',
                    '../yarr/YarrCanonicalizeUCS2.cpp',
                    '../yarr/YarrJIT.cpp',
                    '../yarr/YarrPattern.cpp',
                    '../Logging.cpp',
                    '../../WTF/wtf/dtoa/bignum-dtoa.cc',
                    '../../WTF/wtf/dtoa/bignum.cc',
                    '../../WTF/wtf/dtoa/cached-powers.cc',
                    '../../WTF/wtf/dtoa/diy-fp.cc',
                    '../../WTF/wtf/dtoa/double-conversion.cc',
                    '../../WTF/wtf/dtoa/fast-dtoa.cc',
                    '../../WTF/wtf/dtoa/fixed-dtoa.cc',
                    '../../WTF/wtf/dtoa/strtod.cc',
                    '../../WTF/wtf/manx/MainThreadManx.cpp',
                    '../../WTF/wtf/manx/OSAllocatorManx.cpp',
                    '../../WTF/wtf/text/AtomicString.cpp',
                    '../../WTF/wtf/text/CString.cpp',
                    '../../WTF/wtf/text/StringBuilder.cpp',
                    '../../WTF/wtf/text/StringImpl.cpp',
                    '../../WTF/wtf/text/StringStatics.cpp',
                    '../../WTF/wtf/text/WTFString.cpp',
                    '../../WTF/wtf/unicode/CollatorDefault.cpp',
                    '../../WTF/wtf/unicode/UTF8.cpp',
                    '../../WTF/wtf/Assertions.cpp',
                    '../../WTF/wtf/BitVector.cpp',
                    '../../WTF/wtf/BitVector.h',
                    '../../WTF/wtf/CryptographicallyRandomNumber.cpp',
                    '../../WTF/wtf/CurrentTime.cpp',
                    '../../WTF/wtf/DataLog.cpp',
                    '../../WTF/wtf/DateMath.cpp',
                    '../../WTF/wtf/dtoa.cpp',
                    '../../WTF/wtf/FastMalloc.cpp',
                    '../../WTF/wtf/MainThread.cpp',
                    '../../WTF/wtf/MetaAllocator.cpp',
                    '../../WTF/wtf/OSRandomSource.cpp',
                    '../../WTF/wtf/PageBlock.cpp',
                    '../../WTF/wtf/StackBounds.cpp',
                    '../../WTF/wtf/TCSystemAlloc.cpp',
                    '../../WTF/wtf/ThreadIdentifierDataPthreads.cpp',
                    '../../WTF/wtf/ThreadingPthreads.cpp',
                    '../../WTF/wtf/WTFThreadData.cpp',
                    ],
                },
            {
                'target_name'   : 'JSCJITProxy',
                'type'          : 'static_library',
                'msvs_guid'     : 'F65256E9-FE15-493F-910B-EA1329D77553',
                'dependencies'  : [
                    'WTF',
                    ],
                'include_dirs'  : [
                    '<@(jscore_include_dirs)',
                    ],
                'defines'       : [
                    'BUILDING_JavaScriptCore',
                    ],
                'sources'       : [
                    '../dfg_detached/DFGJITCompilerProxy.cpp',
                    '../dfg_detached/DFGOSRExitCompilerProxy.cpp',
                    '../dfg_detached/DFGRepatchProxy.cpp',
                    '../jit_detached/AbstractMacroAssemblerProxy.cpp',
                    '../jit_detached/JITOpcodesProxy.cpp',
                    '../jit_detached/JITPropertyAccessProxy.cpp',
                    '../jit_detached/JITProxy.cpp',
                    '../jit_detached/JITStubEntries.cpp',
                    '../jit_detached/JSCBridgeVM.cpp',
                    '../jit_detached/MacroAssemblerX86_64Proxy.cpp',
                    '../jit_detached/RepatchBufferProxy.cpp',
                    '../jit_detached/ThunkGeneratorsProxy.cpp',
                    '../jit_detached/YarrJITProxy.cpp'
                    ],
                'includes'      : [ 
                    '../../gyp/single_jit_configuration.gypi',
                    ],
                },
            ],
        }]]
    }
