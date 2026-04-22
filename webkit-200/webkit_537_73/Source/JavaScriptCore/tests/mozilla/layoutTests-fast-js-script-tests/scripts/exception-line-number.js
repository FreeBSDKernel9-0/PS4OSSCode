description('This test makes sure the exception stack has line number information.');

// Test error.stack:
function foo() {    // line 4
    try {
        doError();  // line 6
    } catch(err) {
        temp = err.stack;
    }
}
foo();              // line 11

// The stack trace contains the full path to the file.  We need to trim it to
// only the part below LayoutTest so that the test results are consistent
// regardless of which server it is served from.
//
// String.match() generates an array of matches.  We'll just convert all the
// elements back into a comma separated string by simply stringifying the
// array.  This makes it easier to compare the resultant stack trace info.

result = String(temp.match(/:[0-9]+\:[0-9]+/g));

shouldBe("result", '":6:16,:11:4"');



