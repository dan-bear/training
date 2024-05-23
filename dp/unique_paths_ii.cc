/**
 * https://leetcode.com/problems/unique-paths-ii
 * #dp #DP
 */
class Solution {
private:
    static constexpr int skSpace{0};
    static constexpr int skObstacle{1};
public:
    /**
     * Algorithm:
     * dp[i][j] = number of ways to reach coordinate (i,j).
     * if grid[i][j] == skObstacle: dp[i][j] = 0 
     * else:
     * dp[0][j > 0] = dp[0][j - 1]
     * dp[i > 0][0] = dp[i - 1][0]
     * dp[i > 0][j > 0] = dp[i - 1][j] + dp[i][j - 1]
     *
     * Memory optimization - use the grid instead of allocating
     * a new dp table.
     */
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int rowDim = obstacleGrid.size();
        int colDim = obstacleGrid[0].size();
        obstacleGrid[0][0] = obstacleGrid[0][0] == skObstacle ? 0 : 1;

        for(int colIdx = 1; colIdx < colDim; colIdx++){
            obstacleGrid[0][colIdx] = obstacleGrid[0][colIdx] == skObstacle ?
                                      0 : obstacleGrid[0][colIdx - 1];
        }
        
        for(int rowIdx = 1; rowIdx < rowDim; rowIdx++){
            obstacleGrid[rowIdx][0] = obstacleGrid[rowIdx][0] == skObstacle ?
                                      0 : obstacleGrid[rowIdx - 1][0];
            for(int colIdx = 1; colIdx < colDim; colIdx++){
                obstacleGrid[rowIdx][colIdx] = 
                    obstacleGrid[rowIdx][colIdx] == skObstacle ?
                        0 : 
                        obstacleGrid[rowIdx - 1][colIdx] +
                        obstacleGrid[rowIdx][colIdx - 1];
            }
        }

        return obstacleGrid[rowDim - 1][colDim - 1];
    }
};
