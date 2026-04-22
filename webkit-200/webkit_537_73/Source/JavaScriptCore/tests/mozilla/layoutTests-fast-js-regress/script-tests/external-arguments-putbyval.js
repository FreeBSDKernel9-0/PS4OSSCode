function foo(args)
{
    var result = 0;
    for (var i = 0; i < args.length; ++i) {
        result += args[i];
        args[i] += i;
    }
    return result;
}

function bar(a, b, c, d)
{
    return [foo(arguments), a, b, c, d];
}

for (var i = 0; i < 10000; ++i) {
    var result = bar(i, i + 1, i + 2, i + 3);
    assertEq (result.length , 5);
    assertEq (result[0] , i * 4 + 6);
  
    assertEq (result[1] , i);
    
    assertEq (result[2] , i + 1 + 1);
   
    assertEq (result[3] , i + 2 + 2);
    
    assertEq (result[4] , i + 3 + 3);
}


