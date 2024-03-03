/**
 * See the description in the next link.
 * https://leetcode.com/problems/pascals-triangle-ii/
 * 
 * #ptr #PTR #array #ARRAY #pointer_swap #ptr_swap
 * 
 * The function to implement:
 * @param rowIndex the index of the row to return (0 based index)
 * @param returnSize the length of the row we return as an output parameter.
 * @return a pointer to the allocated row.
 * int* getRow(int rowIndex, int* returnSize) 
 * Note: The returned array must be malloced, assume caller calls free().
 *
 * sOLUTION STARTS HERE!
 */
void fillCurrRow(int* pPrevRow, int rowLen, int* pCurrRow);
int* calcRow(int rowIdx, int* pCurrRow, int* pPrevRow);
void swapRow(int** ppRow1, int** ppRow2);

int* getRow(int rowIndex, int* returnSize) {
    int rowLen = rowIndex + 1;
    *returnSize = rowLen;
    int* pPrevRow = (int*)malloc(rowLen * sizeof(int));
    int* pCurrRow = (int*)malloc(rowLen * sizeof(int));
    
    int* pRowToReturn = calcRow(rowIndex, pCurrRow, pPrevRow);
    int* pRowToFree = pRowToReturn == pCurrRow ? pPrevRow : pCurrRow;
    
    free(pRowToFree);
    return pRowToReturn;
}

int* calcRow(int rowIndex, int* pCurrRow, int* pPrevRow){
    pPrevRow[0] = 1;
    pCurrRow[0] = 1;
    for(int currRowIdx = 1; currRowIdx <= rowIndex; currRowIdx++){
        fillCurrRow(pPrevRow, currRowIdx + 1, pCurrRow);
        swapRow(&pPrevRow, &pCurrRow);
    }
    ///prevRow since the loop ended with a swap.
    return pPrevRow;   
}

void fillCurrRow(int* pPrevRow, int rowLen, int* pCurrRow){
    pCurrRow[0] = 1;
    pCurrRow[rowLen - 1] = 1;
    for(int idx = 1; idx < rowLen - 1; idx++){
        pCurrRow[idx] = pPrevRow[idx - 1] + pPrevRow[idx];
    }
}

void swapRow(int** ppRow1, int** ppRow2){
    int* pTemp = *ppRow1;
    *ppRow1 = *ppRow2;
    *ppRow2 = pTemp;
}
