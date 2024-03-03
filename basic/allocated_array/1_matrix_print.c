/**
 * Print a matrix such that:
 * 1: each row is printed with space between each element.
 * 2: each row is printed in a separate line.
 * For example:
 * The matrix [[1, 2],[3, 4]] is printed as:
 * 1 2
 * 3 4
 * @param matrix the matrix.
 * @param rowDim the rows dimension of the matrix.
 * @param colDim the columns dimension of the matrix.
 */
void printIntMatrix(int** matrix, int rowDim, int colDim)
{
    for (int rowIdx = 0; rowIdx < rowDim; rowIdx++) {
        for (int colIdx = 0; colIdx < colDim; colIdx++) {
            printf("%d ", matrix[rowIdx][colIdx]);
        }
        printf("\n");
    }
}
