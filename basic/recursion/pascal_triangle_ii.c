/**
 * https://leetcode.com/problems/pascals-triangle-ii/
 */
///SOLUTION
int* calcPascalTriangleRowAux(int targetRowIdx,
                              int currentRowIdx,
                              int* currentRow);
void calcNextRowFromCurrentRow(int* currentRow,
                               int* nextRow,
                               int nextRowLen);
/**
 * @param rowIndex the index of the row to return (0 based index)
 * @param returnSize the length of the row we return as an output parameter.
 * @return a pointer to the allocated row.
 */
int* getRow(int rowIndex, int* returnSize){
    ///since the length of a row in rowIdx is rowIdx + 1, 
    ///the returnSize is just rowIdx + 1
    *returnSize = rowIndex + 1;
  
    int* firstRow = (int*)malloc(sizeof(int) * 1);
    firstRow[0] = 1;
    return calcPascalTriangleRowAux(rowIndex, 0, firstRow);
}

int* calcPascalTriangleRowAux(int targetRowIdx,
                              int currentRowIdx,
                              int* currentRow){
    if(targetRowIdx == currentRowIdx){
        return currentRow;
    }
    
    int currentRowLen = currentRowIdx + 1;
    int nextRowLen = currentRowLen + 1;
    int* nextRow = (int*)malloc(sizeof(int) * nextRowLen);
    calcNextRowFromCurrentRow(currentRow, nextRow, nextRowLen);
    free(currentRow);//the current row is not needed anymore.
                     //as the rest of the calculation is done
                     //with the next row. So, let's free it.
    
    ///Start over with the next row.
    return calcPascalTriangleRowAux(targetRowIdx,
                                    currentRowIdx + 1, 
                                    nextRow);
}

void calcNextRowFromCurrentRow(int* currentRow,
                               int* nextRow,
                               int nextRowLen){
    nextRow[0] = 1;
    nextRow[nextRowLen - 1] = 1;
    for (int idx = 1; idx < nextRowLen - 1; idx++){
        ///pascal's triangle rule.  
        nextRow[idx] = currentRow[idx - 1] + currentRow[idx];
    }
}
