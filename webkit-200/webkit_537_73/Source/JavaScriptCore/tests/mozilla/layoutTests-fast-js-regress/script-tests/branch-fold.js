function f()
{
    var i;
    var limit = 150000;

    for (i = 0; (i < limit) == true; ++i) {
    }

    assertEq (i,limit);

    for (i = 0; (i < limit) === true; ++i) {
    }

    assertEq (i , limit);

    i = 0;
    for (var done = false; done == false; ) {
        if (!(++i < limit))
            done = true;
    }

    assertEq (i ,limit);

    i = 0;
    while (true) {
        if ((++i < limit) == false)
            break;
    }

    assertEq(i ,limit);

    i = 0;
    while (1) {
        if ((++i < limit) != true)
            break;
    }

    assertEq (i , limit);

    i = limit;
    while (--i) {
        if ((i & 1) == 0)
            continue;
    }

    assertEq (i , 0);
}

function g(x, y)
{
    var i;
    var limit = 150000;

    for (i = 0; i < limit; ++i) {
        if (true == false)
            break;
        if (true != true)
            break;
        if ("start" === "end")
            break;
        if (null !== null)
            break;
    }

    assertEq (i , limit);

    for (i = 0; i < limit; ++i) {
        if (x == false)
            break;
        if (x !== true)
            break;
        if (x != y)
            break;
        if (x !== y)
            break;
        x = x == y;
    }

    assertEq (i , limit);
}

f();
g(true, true);
