var p = {f:true};

function foo(b, d) {
    var c;
    if (p.f)
        c = b;
    return d[-c];
}

var result = 0;
var array = [42, 43, 44];
for (var i = 0; i < 1000000; ++i)
    result += foo(-(i % 3), array);

assertEq (result , 42999999);

