function foo(o) {
    return o.f;
}

function Foo() { }

Foo.prototype.f = 1;

function Bar() { }

Bar.prototype.f = 2;

function bar() {
    var o = new Foo();
    var p = new Bar();
    
    var result = 0;
    for (var i = 0; i < 2000000; ++i)
        result += foo(o) + foo(p);
    
    return result;
}

var result = bar();
assertEq (result , 6000000);

