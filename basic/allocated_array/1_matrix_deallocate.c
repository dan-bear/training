/**
 * Deallocates a matrix of integers with given row
 * dimension.
 * @param matrix the matrix.
 * @param rowDim the rows dimension of the matrix.
 * @note make sure you understand why the colDim is unneeded.
 */
#include <stdlib.h>
void deallocateIntMatrix(int** matrix, int rowDim)
{
    for (int rowIdx = 0; rowIdx < rowDim; rowIdx++) {
        free(matrix[rowIdx]);
    }
    free(matrix);
}
