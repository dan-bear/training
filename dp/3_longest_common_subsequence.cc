/**
 * https://leetcode.com/problems/longest-common-subsequence
 * #dp #DP
 */
class Solution {
public:
    ///dp[i][j] is the longest subequence of text1[0 : i] and text2[0 : j]
    ///dp[i][j] if text1[i] == text2[j]: 
    ///            dp[i][j] = dp[i-1][j-1] + 1 (the last maximal subsequence + current pair)
    ///         else: dp[i][j] = max(dp[i - 1][j] (don't use text1[i]),
    ///                              dp[i][j - 1]) (don't use text2[i])
    ///
    int longestCommonSubsequence(string text1, string text2) {
        int text1Len = text1.length();
        int text2Len = text2.length();
        
        ///First using a dp table, then the code is slightly modified to
        ///use less space.
        ///Note: additional row and col are added, to avoid row0 and col0 edge cases
        ///      they can be thought as the empty string case, so the max common
        ///      subsequence is 0.
        // vector<vector<int>> dp(text1Len + 1, vector<int>(text2Len + 1, 0));
        // for(int rowIdx = 1; rowIdx <= text1Len; rowIdx++){
        //     for(int colIdx = 1; colIdx <= text2Len; colIdx++){
        //         if(text1[rowIdx - 1] == text2[colIdx - 1]){
        //             dp[rowIdx][colIdx] = dp[rowIdx - 1][colIdx - 1] + 1;
        //         }else{
        //             dp[rowIdx][colIdx] = max(dp[rowIdx - 1][colIdx], dp[rowIdx][colIdx - 1]);
        //         }
        //     }
        // }
        // return dp[text1Len][text2Len];

        ///vector<vector<int>> dp(text1Len + 1, vector<int>(text2Len + 1, 0));
        vector<int> prevRow(text2Len + 1, 0);
        vector<int> currRow(text2Len + 1, 0);

        for(int rowIdx = 1; rowIdx <= text1Len; rowIdx++){
            for(int colIdx = 1; colIdx <= text2Len; colIdx++){
                if(text1[rowIdx - 1] == text2[colIdx - 1]){
                    ///dp[rowIdx][colIdx] = dp[rowIdx - 1][colIdx - 1] + 1;
                    ///Note: dp[rowIdx] is just replaced with currRow.
                    currRow[colIdx] = prevRow[colIdx - 1] + 1;
                }else{
                    ///dp[rowIdx][colIdx] = max(dp[rowIdx - 1][colIdx], dp[rowIdx][colIdx - 1]);
                    ///Note: dp[rowIdx] is replaced with currRow.
                    ///      dp[rowIdx - 1] is replaced with prevRow.
                    currRow[colIdx] = max(prevRow[colIdx], currRow[colIdx - 1]);
                }
            }
            prevRow.swap(currRow);
        }
        return prevRow[text2Len];
    }
};
