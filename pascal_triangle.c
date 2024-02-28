/**
 * For the question description see:
 * https://leetcode.com/problems/pascals-triangle/
 * Function parameters and return value:
 */

int** generatePascal(int numRows, int* rowsSize);
void calcPascalRows(int** ppRows, int numRows);
void fillRow(int* pPrevRow, int* pCurrRow, int currRowLen);

/**
 * @param numRows number of rows to generate.
 * @param returnSize output parameter for the size of the
 * array holding pointers to pascal rows that's the size of
 * the return value.
 * @param returnColumnSizes an output parameter holding the
 * lengthes of every row in pascal traignle.
 */
int** generate(int numRows, int* returnSize, int** returnColumnSizes) {
    int* pRowsLen = (int*)malloc(numRows * sizeof(int));
    *returnColumnSizes = pRowsLen;
    *returnSize = numRows;
    return generatePascal(numRows, pRowsLen);
}

/**
 * Function parameters and return value:
 * INPUT PARAMETER
 * @param numRows the number of rows of pascal triangle that need
 * to be calculated.
 * RETURN AND OUTPUT PARAMETERS
 * The output parameter is an array of arrays (or pointers)
 * representing the calculated pascal traignle. 
 * For example, if numRows = 3 the pascal triangle is 
 * stored in memory as follows:
 * rowsArray = [ptrToFirstRow, ptrToSecondRow, ptrToThirdTow]
 * firstRow = [1]
 * secondRow = [1, 1]
 * thirdRow = [1, 2, 1]
 * Since rowArray, firstRow, secondRow and thirdRow need to be 
 * iterated by the caller, the caller needs to know the length
 * of each row and the length of rowsArray, thus it gives us 
 * an output parameter rowsSize, it's an array allocated by
 * the caller where the length of each row should be stored.
 * In this example rowsSize should be [1, 2, 3] befoer the
 * function returns.
 * The return value is a pointer to rowsArray, allocated by this
 * function. Note, the rowsArray should not be deallocated, its
 * the user's responsibility to do so. 
 * @param rowsSize an output arry to hold the length of each
 * row.
 * @return a pointer to the array holding the calculated rows
 * as explained above. 
 */
//Forward declaration:
void calcPascalRows(int** ppRows, int numRows);
void fillRow(int* pPrevRow, int* pCurrRow, int currRowLen);
//SOLUTION:
int** generatePascal(int numRows, int* rowsSize){
    //Allocation phase.
    int** ppRows = (int**)malloc(sizeof(int*) * numRows);
    for(int rowLen = 1; rowLen <= numRows; rowLen++){
        int* pRow = (int*)malloc(sizeof(int) * rowLen);
        int rowIdx = rowLen - 1;
        ppRows[rowIdx] = pRow;
        rowsSize[rowIdx] = rowLen;
    }
    calcPascalRows(ppRows, numRows);
    return ppRows;
}

void calcPascalRows(int** ppRows, int numRows){
    int* pFirstRow = ppRows[0];
    pFirstRow[0] = 1;
    // Note: make sure you understand the previous two lines can
    // be replaced with ppRows[0][0] = 1;
    
    for(int rowIdx = 1; rowIdx < numRows; rowIdx++){
        //Fill each row based on the previous row.
        int currRowLen = rowIdx + 1;
        fillRow(ppRows[rowIdx - 1], ppRows[rowIdx], currRowLen);
    }
}

void fillRow(int* pPrevRow, int* pCurrRow, int currRowLen){
    int lastIdx = currRowLen - 1;
    pCurrRow[0] = 1; //first element is always 1.
    pCurrRow[lastIdx] = 1; //lastElement is alwyas 1.
    for(int idx = 1; idx < lastIdx; idx++){
        //FINALLY Pascal traingale rule.
        pCurrRow[idx] = pPrevRow[idx - 1] + pPrevRow[idx];
    }
}
