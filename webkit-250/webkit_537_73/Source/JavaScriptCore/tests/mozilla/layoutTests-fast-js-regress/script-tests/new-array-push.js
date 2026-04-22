function foo() {
    return new Array();
}

var arrays = [];

for (var i = 0; i < 100000; ++i)
    arrays.push(foo());

for (var i = 0; i < 100000; ++i) {
    assertEq (arrays[i].length , 0);
}
