function f(a,b) {
    var result = 0;
    for (var i = 0; i < 1000; i++)
        result = (result + Math.imul(a,b)) | 0
    return result;
}
var result = 0;
for (var i = 0; i < 1000; i++)
    result = result + f(result | 1, i+0.5) ^ f(i+1.3, result | 1);

assertEq (result , -1567919232);