/**
 * https://leetcode.com/problems/wildcard-matching/
 * #dp #DP 
 */
class Solution {
public:
    /**
     * dp[i][j] = true if p[0 : i] matches s[0 : j] when the slices
     * are python like, i.e. p[0 : i] is p[0]...[i - 1] and
     * p[0 : 0], s[0 : 0] are the empty strings.
     * The result is: dp[p.size()][s.size()].
     * 
     * dp[0][0] = true, since the empty word matched the empty word.
     * dp[0][j > 0] = false, since the empty word cannot match any
     *                non-empty word.
     * dp[i > 0][0] = true iff dp[i - 1][0] and p[i - 1] == *, since only a
     *                sequence of *s can match the empty word.
     * dp[i > 0][j > 0]: 
     *     1: if p[i - 1] == ?: 
     *            dp[i][j] = dp[i - 1][j - 1], 
     *            since p[i - 1] matches s[j - 1].
     *     2: if p[i - 1] == *: 
     *            p[i - 1] can be used 0 to j - 1 times, so
     *            dp[i][j] = OR(dp[i - 1][j] - don't used it
     *                          dp[i - 1][j - 1] - use it for the first time
     *                          dp[i][j - 1] - use it again).
     *    3: else - p[i - 1] is not a joker.
     *           dp[i][j] = p[i - 1] ==  s[j - 1] && dp[i - 1][j - 1]
     */
    bool isMatch(string s, string p) {
        vector<vector<bool>> dp(p.size() + 1, vector<bool>(s.size() + 1, false));
        dp[0][0] = true;
        
        for(int rowIdx = 1; rowIdx <= p.size(); rowIdx++){
            ///Match the empty word:
            dp[rowIdx][0] = p[rowIdx - 1] == skWildJoker && 
                            dp[rowIdx - 1][0];
            ///Match non-empty words:
            for(int colIdx = 1; colIdx <= s.size(); colIdx++){
                if(p[rowIdx - 1] == skSingleJoker){
                    dp[rowIdx][colIdx] = dp[rowIdx - 1][colIdx - 1];
                }else if(p[rowIdx - 1] == skWildJoker){
                    dp[rowIdx][colIdx] = dp[rowIdx - 1][colIdx - 1] || 
                                         dp[rowIdx - 1][colIdx] || 
                                         dp[rowIdx][colIdx - 1];
                }else{
                    dp[rowIdx][colIdx] = p[rowIdx - 1] == s[colIdx - 1] &&
                                         dp[rowIdx - 1][colIdx - 1];
                }
            }
        }

        return dp[p.size()][s.size()];
    }
private:
    static constexpr char skWildJoker{'*'};
    static constexpr char skSingleJoker{'?'};
};
