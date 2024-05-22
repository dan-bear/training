/**
 * https://leetcode.com/problems/minimum-path-sum
 * #dp #DP
 */
class Solution {
public:
    /**
     * Edge cases:
     * 1: grid is empty.
     * 2: sum exceeds max int val.
     *
     * Simple test cases:
     * 0 1    0 0  should return 0. 
     * 0 0    1 0
     * 
     * Algorithm:
     * dp[i][j] = minimal path sum to reach from (0,0) to (i,j).
     * dp[0][0] = grid[0][0]
     * dp[0][i] = sum(grid[0][j] for j in range(i + 1))
     * dp[i][0] = sum(grid[j][0] for j in range(i + 1))
     * for i, j > 0: dp[i][j] = min(dp[i][j - 1], dp[i - 1][j]) + grid[i][j].
     *
     * To reduce memory usage, the grid itself can be used.
     */
    int minPathSum(vector<vector<int>>& grid) {
        int rowDim = grid.size();
        int colDim = grid[0].size();
        ///Do the first row to avoid conditions inside the loop.
        for(int colIdx = 1; colIdx < colDim; colIdx++){
            grid[0][colIdx] += grid[0][colIdx - 1];
        }

        for(int rowIdx = 1; rowIdx < rowDim; rowIdx++){
            ///If rowIdx had started with 0, a condition for rowIdx - 1
            ///out of range access would be needed.
            grid[rowIdx][0] += grid[rowIdx - 1][0];
            for(int colIdx = 1; colIdx < colDim; colIdx++){
                grid[rowIdx][colIdx] += min(grid[rowIdx - 1][colIdx], 
                                            grid[rowIdx][colIdx - 1]);
            }
        }
        
        return grid[rowDim - 1][colDim - 1];
    }
};
