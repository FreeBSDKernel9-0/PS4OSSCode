description("Test to make sure that document.all works properly with the DFG");

var f = function(a, b) {
    if (a == null) {
        return 0;
    }
    if (b == null) {
        return a;
    }
    return a + b;
};

for (var i = 1; i < 100; i++) {
    shouldBe("f(2, 42)", "44");
}

var test = {};
