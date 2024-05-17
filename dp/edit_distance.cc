/**
 * https://leetcode.com/problems/edit-distance
 * #dp #DP
 * Notes:
 *     - Do not forget the empty word case.
 */
class Solution {
public:
    /**
     * At each start I can move from once state to another.
     * The worst case scenario is replacing word1[i] with
     * word2[i] and then, in case word1.len() > word2.len()
     * delete the trailing letters, otherwise, add word2
     * letters using inserts. So, non optimal solution
     * demands max(word1.len(), word2.len()) operations.
     *
     * dp[i][j] minimal number of operatios to change word1[0:i - 1]
     * to word2[0:j - 1]. Then dp[word1.len()][word2.len()] is
     * our solution.Note that word[0 : -1] represents the empty word.
     * 
     * dp[0][0] = 0 : moving from the empty word to an empty word.
     * for i > 0: dp[0][i] = dp[i][0] = i, inserting/deleting the 
     * chars. Note that actually dp[i][0] = 0 also for i = 0, so
     * the dp[0][0] case is covered by this condition.
     * 
     * dp[i][j] for i, j > 0 is the minimal between the following terms:
     *     1: dp[i - 1][j - 1] + 1 if word1[i -  1] != word2[j - 1] else 0.
     *       (replace if word1[i - 1] != word2[j - 1].         
     *     2: dp[i][j - 1] + 1 (reach from word1[0 : i - 1] to word2[0 : j - 2]
     *                          and insert word2[j - 1]).
     *     3: dp[i - 1][j] + 1 (reach form word1[0:i - 2] to word2[0 : j - 1] 
     *                          and delete word1[i - 1]).
     * So, dp[i][j] depends on (dp[i - 1][j - 1], dp[i][j - 1], dp[i  - 1][j]). 
     * Thus filling the table row-by-row can work out after filling the first
     * row and first column.
     */
    int minDistance(string word1, string word2) {
        int upperBound = max(word1.length(), word2.length());
        vector<vector<int>> dp(word1.length() + 1,
                               vector<int>(word2.length() + 1, upperBound));
        fillFirstRowAndCol(word1, word2, dp);
        for(int rowIdx = 1; rowIdx <= word1.length(); rowIdx++){
            for(int colIdx = 1; colIdx <= word2.length(); colIdx++){
                dp[rowIdx][colIdx] = min(
                    {(dp[rowIdx - 1][colIdx - 1] + 
                     (word1[rowIdx - 1] == word2[colIdx - 1] ? 0 : 1)),
                      dp[rowIdx - 1][colIdx] + 1,
                      dp[rowIdx][colIdx - 1] + 1});
            }
        }
        return dp[word1.length()][word2.length()];
    }
private:
    void fillFirstRowAndCol(const string& word1, const string& word2, vector<vector<int>>& dp){
        for(int colIdx = 0; colIdx < word2.length(); colIdx++){
            dp[0][colIdx] = colIdx;
        }
        for(int rowIdx = 0; rowIdx < word1.length(); rowIdx++){
            dp[rowIdx][0] = rowIdx;
        }
    }
};
