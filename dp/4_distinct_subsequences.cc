/**
 * https://leetcode.com/problems/distinct-subsequences/
 * #dp #DP
 */
class Solution {
public:
    /**
     * t = rab
     * s = rabbbrabbb
     * 0 0 0 0 0 0 0 0 0 0 0
     * 0 1 1 1 1 1 2 2 2 2 2
     * 0 0 1 1 1 1 1 3 3 3 3
     * 0 0 0 1 2 3 3 3 6 9 12 
     *
     *
     * bag
     * babgbag
     * 0 0 0 0 0 0 0 0
     * 0 1 2 2 2 3 3 3
     * 0 0 1 1 1 1 4 4
     * 0 0 0 1 1 1 1 5
     *
     * dp[i][j] = number of times t[0 : i] appears in s[0 : j] when
     *            string[0 : k] is string[0]...string[k - 1] and
     *            string[0 : 0] is the empty string.
     * dp[0][0] = the number of times the empty string appears in
     *            the empty string is 0.
     * dp[i > 0][0] = 0 and dp[0][j > 0] = 0.
     * dp[1][j > 0] := number of times t[0 : 1] == t[0] appears in
     *                 s[0 : j].
     *                 If t[0] == s[j - 1] == t[0]: dp[1][j] = 1 + dp[1][j - 1]
     *                 else: dp[1][j] = dp[1][j - 1].
     *                 In practice it just counts how many times t[0] appears
     *                 s.
     * dp[i > 1][j > 0]: 
     *    if t[i - 1] == s[j - 1] the number of times t[0 : i]
     *    appears in s[0 : j] is the number of times t[0 : i - 1]
     *    appears in s[0 : j - 1] + for each time t[0 : i] appeared
     *    in s[0 : j - 1] one can replace the last character.
     *    Thus, dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1].
     *    else: dp[i][j] = dp[i][j - 1].
     *
     * Since the update rule depends on the previous row, a sapce optiomization
     * can be made.
     * 
     */
    int numDistinct(string s, string t) {
        int32_t sSize = s.size();
        int32_t tSize = t.size();
        vector<uint64_t> prevRow(sSize + 1, 0);
        vector<uint64_t> currRow(sSize + 1, 0);
        
        ///First row, counting the number of times t[0] is in s[0 : j]
        for(int colIdx = 1; colIdx <= sSize; colIdx++){
            prevRow[colIdx] = prevRow[colIdx - 1] +
                              (t[0] == s[colIdx - 1] ? 1 : 0);
        }
        
        for(int rowIdx = 1; rowIdx < tSize; rowIdx++){
            for(int colIdx = 0; colIdx < sSize; colIdx++){
                if(t[rowIdx] == s[colIdx]){
                    currRow[colIdx + 1] = currRow[colIdx] + prevRow[colIdx];
                }else{
                    currRow[colIdx + 1] = currRow[colIdx];
                }
            }
            prevRow.swap(currRow);
        }
        return prevRow[sSize];
    }
};
