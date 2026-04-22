function foo(o) {
    return o.f;
}

var o = {f:42};
var result = 0;
for (var i = 0; i < 500; ++i) {
    for (var j = 0; j < 10000; ++j)
        result += foo(o);
    o.g = 43;
}

assertEq (result , 210000000);
