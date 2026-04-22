{
    'conditions' : [['OS == "orbis"', {
        'configurations' : {
            'Debug-SingleJITProcess' : {
                'msvs_configuration_platform' : 'ORBIS',
                'defines'                     : [ '_DEBUG', 'ENABLE_DETACHED_JIT=0' ],
            },
            'Release-SingleJITProcess' : {
                'msvs_configuration_platform' : 'ORBIS',
                'defines'                     : [ 'NDEBUG', 'ENABLE_DETACHED_JIT=0' ],
                'msbuild_settings' : {
                    'ClCompile' : { 
                        'AdditionalOptions' : ['-O2'],
                    },
                },
            },
        },
    }]]
}
