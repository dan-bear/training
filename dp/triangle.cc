/**
 * https://leetcode.com/problems/triangle
 * #dp #DP 
 */
class Solution {
public:
    /**
     * Edge cases:
     * triangle.size() = 0, in this case the minimum total is 0.
     * 
     * Define dp[i][j] as the minimal distance from row i to row j.
     * dp[0][0] = triangle[0][0] (the minimal path to triangle[0][0]).
     * dp[1][0] = dp[0][0] + triangle[1][0] (minimal path to triangle[1][0])
     * dp[1][1] = dp[0][0] + triangle[1][1] (minimal path to triangle[1][1])
     * dp[i][j] (the minimal path to triangle[i][j]) = 
     *          min(dp[i - 1][j], dp[i - 1][j - 1]) + triangle[i][j].
     * The returned value should be the minimal value of dp[triangle.length].
     */
    int minimumTotal(vector<vector<int>>& triangle) {
        int lastLineSize = triangle[triangle.size() - 1].size();
        ///Without space optimization:
        // vector<vector<int>> dp(lastLineSize, vector<int>(lastLineSize, 0));
        // dp[0][0] = triangle[0][0];
        // for(int rowIdx = 1; rowIdx < triangle.size(); rowIdx++){
        //     int lastColIdx = triangle[rowIdx].size() - 1;
        //     dp[rowIdx][0] = triangle[rowIdx][0] + dp[rowIdx - 1][0];
        //     dp[rowIdx][lastColIdx] = triangle[rowIdx][lastColIdx] + 
        //                                 dp[rowIdx - 1][lastColIdx - 1];
            
        //     for(int colIdx = 1; colIdx < lastColIdx; colIdx++){
        //         dp[rowIdx][colIdx] = triangle[rowIdx][colIdx] + 
        //             min(dp[rowIdx - 1][colIdx], dp[rowIdx - 1][colIdx - 1]);
        //     }
        // }
        // return ranges::min(dp[triangle.size() - 1]);

        ///With space optimization:
        vector<int> prevDpRow(lastLineSize, 0);
        vector<int> currDpRow(lastLineSize, 0);
        prevDpRow[0] = triangle[0][0];
        for(int rowIdx = 1; rowIdx < triangle.size(); rowIdx++){
            int lastColIdx = triangle[rowIdx].size() - 1;
            currDpRow[0] = triangle[rowIdx][0] + prevDpRow[0];
            currDpRow[lastColIdx] = triangle[rowIdx][lastColIdx] + 
                                        prevDpRow[lastColIdx - 1];
            
            for(int colIdx = 1; colIdx < lastColIdx; colIdx++){
                currDpRow[colIdx] = triangle[rowIdx][colIdx] + 
                    min(prevDpRow[colIdx], prevDpRow[colIdx - 1]);
            }

            prevDpRow.swap(currDpRow);
        }
        return ranges::min(prevDpRow);
    }
};
