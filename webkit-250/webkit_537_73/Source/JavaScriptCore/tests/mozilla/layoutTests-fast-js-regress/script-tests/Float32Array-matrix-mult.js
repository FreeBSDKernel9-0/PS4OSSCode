function makeEmptyMatrix(rows, columns)
{
    var result = new Array(rows);
    for (var i = 0; i < rows; ++i)
        result[i] = new Float32Array(columns);
    result.rows = rows;
    result.columns = columns;
    return result;
}

function multiplyMatrices(left, right)
{
    assertEq (left.columns , right.rows) ;
    
    var result = makeEmptyMatrix(left.rows, right.columns);
    
    for (var row = 0; row < result.rows; ++row) {
        for (var column = 0; column < result.columns; ++column) {
            for (var i = 0; i < left.columns; ++i)
                result[row][column] += left[row][i] * right[i][column];
        }
    }
    
    return result;
}

function checkMatricesEqual(left, right)
{
    assertEq (left.columns , right.columns);
    assertEq (left.rows , right.rows);
    
    for (var row = 0; row < left.rows; ++row) {
        for (var column = 0; column < left.columns; ++column) {
            assertEq (left[row][column] , right[row][column]);
        }
    }
}

function parseMatrix(string)
{
    var columns = null;
    var result = [];
    string.split("\\").forEach(function(string){
        var row = [];
        string.split(" ").forEach(function(string){
            if (string.match(/^ *$/))
                return;
            row.push(parseFloat(string));
        });
        if (columns) {
            assertEq (columns ,row.length);
        } else
            columns = row.length;
        var typedRow = new Float32Array(row.length);
        for (var i = 0; i < columns; ++i)
            typedRow[i] = row[i];
        result.push(typedRow);
    });
    result.rows = result.length;
    result.columns = columns;
    return result;
}

function printMatrix(matrix)
{
    var maxCellSize = 0;
    
    for (var row = 0; row < matrix.rows; ++row) {
        for (var column = 0; column < matrix.columns; ++column)
            maxCellSize = Math.max(maxCellSize, ("" + matrix[row][column]).length);
    }
    
    function pad(value)
    {
        var result = "" + value;
        while (result.length < maxCellSize)
            result = " " + result;
        return result;
    }
    
    for (var row = 0; row < matrix.rows; ++row) {
        var rowText = "";
        for (var column = 0; column < matrix.columns; ++column) {
            if (column)
                rowText += " ";
            rowText += pad(matrix[row][column]);
        }
        print(rowText);
    }
}

var left = parseMatrix("1 2 3 4 5 \\ 6 7 8 9 10 \\ 21 22 23 24 25 \\ 26 27 28 29 30");
var right = parseMatrix("11 12 31 32 \\ 13 14 33 34 \\ 15 16 35 36 \\ 17 18 37 38 \\ 19 20 39 40");
var expectedResult = parseMatrix("245 260 545 560 \\ 620 660 1420 1460 \\ 1745 1860 4045 4160 \\ 2120 2260 4920 5060");

for (var i = 0; i < 3000; ++i)
    checkMatricesEqual(multiplyMatrices(left, right), expectedResult);


