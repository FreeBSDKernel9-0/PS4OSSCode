function foo(a) {
    return "foo" + new String(a) + "bar";
}

var result;
for (var i = 0; i < 100000; ++i)
    result = foo("hello");

assertEq (result , "foohellobar");
