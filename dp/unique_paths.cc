/**
 * https://leetcode.com/problems/unique-paths
 * #dp #DP
 */
class Solution {
public:
    int uniquePaths(int m, int n) {
        ///dp[i][j] number of unique paths.
        ///dp[0][colIdx] = 1 for colId in 0..n - 1.
        ///dp[rowIdx][0] = 1 for rowIdx in 0..m - 1.
        ///dp[i][j] from top: dp[i - 1][j] + from left: dp[i][j - 1]
        vector<vector<int>> dp(m, vector<int>(n, 1));
        for(int rowIdx = 1; rowIdx < m; rowIdx++){
           for(int colIdx = 1; colIdx < n; colIdx++){
               ///rowIdx and colIdx >= 0
               dp[rowIdx][colIdx] = dp[rowIdx - 1][colIdx] + dp[rowIdx][colIdx - 1];
           }
        }
        return dp[m - 1][n - 1];
        
        ///Make it space efficient (O(n*m) time but O(n) space).
        // vector<int> dpLine(n, 1);
        // for(int rowNum = 2; rowNum <= m; rowNum++){
        //     for(int colIdx = 1; colIdx < n; colIdx++){
        //         dpLine[colIdx] = dpLine[colIdx] + dpLine[colIdx - 1];
        //     }
        // }
        // return dpLine[n - 1];
    }
};
