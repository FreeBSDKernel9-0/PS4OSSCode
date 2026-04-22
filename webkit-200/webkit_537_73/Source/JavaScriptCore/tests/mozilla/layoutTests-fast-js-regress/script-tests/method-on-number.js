function foo(a) {
    var result = 0;
    for (var i = 0 ; i < 500000; ++i)
        result += a.valueOf();
    return result;
}

var result = foo(5);

assertEq (result , 2500000);
