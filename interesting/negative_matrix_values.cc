// https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/
class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
        int rowDim = grid.size();
        if (rowDim == 0){
            return 0;
        }
        int colDim = grid[0].size();
        int backwardRowIdx = rowDim -1;
        int forwardColIdx = 0;
        int res = 0;
        while(backwardRowIdx >= 0 && forwardColIdx < colDim){
            if(grid[backwardRowIdx][forwardColIdx] < 0){
                res += colDim - forwardColIdx;
                backwardRowIdx--; //finished to scan the row.
            }else{
                forwardColIdx++; // continue to the next col
            }
        }
        return res;
    }
};
