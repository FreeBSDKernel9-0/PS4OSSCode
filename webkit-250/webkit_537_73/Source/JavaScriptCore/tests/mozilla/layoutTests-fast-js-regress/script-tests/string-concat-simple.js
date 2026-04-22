function foo(a) {
    return "foo" + a + "bar";
}

var result;
for (var i = 0; i < 1000000; ++i)
    result = foo("hello");

assertEq (result , "foohellobar");
