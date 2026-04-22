description(
"This tests that a assigning to a readonly property in a static or symbol table throws in strict mode."
);

 
function testNumberMAX_VALUE()
{
    "use strict";
    try {
         Number.MAX_VALUE = 42;
    } catch (e) {
        return e instanceof TypeError;
    }
    return false;
}


shouldBeTrue('testNumberMAX_VALUE()');
