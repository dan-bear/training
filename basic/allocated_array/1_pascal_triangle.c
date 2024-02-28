/**
 * For the question description see:
 * https://leetcode.com/problems/pascals-triangle/
 */

#include <stdlib.h>
/**
 * Modified function parameters and return values:
 * @param numRows the number of rows of pascal triangle that need
 * to be calculated.
 * @param rowsSize the length of each row in the generated
 * solution corresponding the the rowIdx.
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
 * In this example rowsSize should be [1, 2, 3] before the
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
    // Note: make sure you are comfortable with the
    // the next syntax as a replacement for the previous two lines:
    // ppRows[0][0] = 1;
    
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
