{
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
    'include_dirs' : [
        '<@(jscore_include_dirs)'
    ],
    'defines' : [
        'BUILDING_JavaScriptCore',
    ],
    'dependencies' : [
        'WTF'
    ],
}
