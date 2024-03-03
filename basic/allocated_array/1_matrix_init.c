/**
 * initialize an already allocated matrix such that all its
 * entries hold the same given value.
 * @param matrix the matrix.
 * @param rowDim the rows dimension of the matrix.
 * @param colDim the columns dimension of the matrix.
 * @param val the value to initialize the matrix's entries
 * with.
 */
void initIntMatrix(int** matrix, int rowDim, int colDim, int val)
{
    for (int rowIdx = 0; rowIdx < rowDim; rowIdx++) {
        for (int colIdx = 0; colIdx < colDim; colIdx++) {
            matrix[rowIdx][colIdx] = val;
        }
    }
}
