{ 
    'includes': [
        '../JavaScriptCore.gypi',
    ], # includes

    'variables': {
        'javascriptcore_files' : [
            '../runtime/WatchdogManx.cpp',
            ],
    }, # variables

    'targets': [
        {
            'target_name'   : 'JscLLIntOffsetExtractor',
            'type'          : 'static_library', 
            'msvs_guid'     : '124328CD-1AC9-47F3-8430-A71C369332ED',
            'includes'      : [ 'common_target.gypi' ],
            'sources'       : [ '../llint/LLIntOffsetsExtractor.cpp' ],
            'msbuild_props' : [ '$(ProjectDir)JscLLIntOffsetExtractor.props' ]
        }, # JscLlintOffsetExtractor target
        {
            'target_name'   : 'JavaScriptCore',
            'type'          : 'static_library',
            'msvs_guid'     : '9A334014-7543-47BF-95C9-000000000001',
            'includes'      : [ 'common_target.gypi' ],
            'sources'       : [
                '<@(javascriptcore_files)',
                '<@(javascriptcore_publicheader_files)',
                '<@(javascriptcore_derived_source_files)',
            ],
            'sources/': [
                [ 'exclude', 'runtime/WatchdogNone.cpp' ],
            ],
            'direct_dependent_settings' : {
                'include_dirs' : [ '<@(jscore_include_dirs)' ],
            }
        }, # JavaScriptCore
        {
            'target_name'   : 'JscConsole',
            'type'          : 'static_library',
            'msvs_guid'     : '70BC1339-271E-430B-9D55-3121794703DE',
            'includes'      : [ 'common_target.gypi' ],
            'sources'       : [ '<@(jsc_files)' ],
        }, # JscConsole
        {
            'target_name'   : 'JscJitCompiler_proxy',
            'type'          : 'static_library',
            'msvs_guid'     : 'F65256E9-FE15-493F-910B-EA1329D77553',
            'includes'      : [ 'common_target.gypi' ],
            'defines'       : [ 'BUILDING_DETACHED_JIT=0' ],
            'sources'       : [ '<@(javascriptcore_proxy_source_files)' ],
        }, # JscJitProxy target
        {
            'target_name'   : 'JscJitCompiler_detached',
            'type'          : 'static_library',
            'msvs_guid'     : 'B6324578-365B-498B-966C-C28C3703B96B',
            'includes'      : [ 'common_target.gypi' ],
            'defines'       : ['BUILDING_DETACHED_JIT=1' ],
            'sources'       : [ '<@(javascriptcore_detached_source_files)' ],
        }, # JscJitCompiler_detached target
    ], # targets
}
