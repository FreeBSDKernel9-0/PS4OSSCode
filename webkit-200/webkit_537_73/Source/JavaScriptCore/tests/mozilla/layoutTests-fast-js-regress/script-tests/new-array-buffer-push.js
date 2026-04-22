function foo() {
    return [[1,2,3], [5,6,6]];
}

function bar() {
    return ["foo", "bar"];
}

function baz() {
    return [foo(), bar(), foo(), bar()];
}

function thingy() {
    var result = [];
    for (var i = 0; i < 50000; ++i)
        result.push(baz());
    return result;
}

var size = thingy().length;
assertEq (size , 50000);
