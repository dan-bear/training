/**
 * Allocates a matrix of integers with given row dimension
 * and col dimension.
 * @note You don't need to initialize the memory value, just
 * allocate it.
 * @param rowDim the rows dimension of the matrix.
 * @param colDim the columns dimension of the matrix.
 * @return the allocated matrix.
 */
#include <stdlib.h>
int** allocateIntMatrix(int rowDim, int colDim)
{
    int** matrix = (int**)malloc(rowDim * sizeof(int*));
    for (int rowIdx = 0; rowIdx < rowDim; rowIdx++) {
        matrix[rowIdx] = (int*)malloc(colDim * sizeof(int));
    }
    return matrix;
}
