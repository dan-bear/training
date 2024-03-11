/**
 * Please read the description here:
 * https://leetcode.com/problems/equal-row-and-column-pairs
 * @note the parameter gridColSize in int equalPairs(int** grid, int gridSize, int* gridColSize) 
 * is not needed. Just ignore it, so you can check your question.
 * #matrix #mat #MATRIX #MAT #array #ARRAY
 */
///SOLUTION
bool compareRowAndCol(int rowIdx, int colIdx, int** grid, int gridSize);
int countEqualRows(int rowIdx, int** grid, int gridSize);
int equalPairs(int** grid, int gridSize, int* gridColSize) {
    int numOfEqualPairs = 0;
    for(int rowIdx = 0; rowIdx < gridSize; rowIdx++){
        numOfEqualPairs += countEqualRows(rowIdx, grid, gridSize);
    }
    return numOfEqualPairs;
}
    
int countEqualRows(int rowIdx, int** grid, int gridSize){
    int count = 0;
    for(int colIdx = 0; colIdx < gridSize; colIdx++){
        if(compareRowAndCol(rowIdx, colIdx, grid, gridSize)){
            count++;
        }       
    }
    return count;
}

bool compareRowAndCol(int rowIdx, int colIdx, int** grid, int gridSize){
    bool res = true;
    for(int elementIdx = 0; elementIdx < gridSize && res; elementIdx++){
        res = (grid[rowIdx][elementIdx] == grid[elementIdx][colIdx]);
    }
    return res;
}
