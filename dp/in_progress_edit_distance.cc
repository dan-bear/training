/**
 * https://leetcode.com/problems/edit-distance
 * #dp #DP
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
     * dp[i][j] minimal number of operatios to change word1[0:i]
     * to word2[0:j]. Then dp[word1.len() - 1][word2.len() - 1] is
     * our solution.
     *
     * Note: maybe a histogram is needed!
     * 
     * dp[0][0] is 1 if word1[0] != word2[0] and 0 otherwise.
     * dp[0][i] is i if word1[0] is not in word2[0 : i] otherwise i - 1.
     * dp[i][0] is i if word2[0] is not in word1[0 : i] otherwise i - 1. 
     * 
     * dp[i][j] for i, j > 0 = minimal of the following terms:
     *     1: dp[i - 1][j - 1] + 1 if word1[i] != word2[j] else 0.
     *       (reach from word1[0: i - 1] to word2[0:j-1] and replace if 
     *        word1[i] != word2[j]).                  
     *     2: dp[i][j - 1] + 1 (reach from word1[0:i] to word2[0:j-1] and
     *                          insert word2[j]).
     *     3: dp[i-1][j] + 1 (reach form word1[0:i-1] to word2[0:j] and
     *                        delete word1[i]).
     * So, dp[i][j] depends on (dp[i - 1][j - 1], dp[i][j-1], dp[i-1][j]). 
     * Thus filling the table row-by-row can work out after filling the first
     * row and first column.
     */
    int minDistance(string word1, string word2) {
        int upperBound = max(word1.length(), word2.length());
        vector<vector<int>> dp(word1.length(),
                               vector<int>(word2.length(), upperBound));
        fillFirstRowAndCol(word1, word2, dp);
        for(int rowIdx = 1; rowIdx < word1.length(); rowIdx++){
            for(int colIdx = 1; colIdx < word2.length(); colIdx++){
                dp[rowIdx][colIdx] = min(
                    {(dp[rowIdx - 1][colIdx - 1] + (word1[rowIdx] == word2[colIdx] ? 0 : 1)),
                      dp[rowIdx - 1][colIdx] + 1,
                      dp[rowIdx][colIdx - 1] + 1});
            }
        }

        return dp[word1.length() - 1][word2.length() - 1];
    }
private:
    void fillFirstRowAndCol(const string& word1, const string& word2, vector<vector<int>>& dp){
        dp[0][0] = word1[0] == word2[0] ? 0 : 1;
        
        int firstRowDec = word2.find(word1[0]) != string::npos ? 1 : 0; 
        int firstColDec = word1.find(word2[0]) != string::npos ? 1 : 0;
        for(int colIdx = 1; colIdx < word2.length(); colIdx++){
            dp[0][colIdx] = colIdx - firstRowDec;
        }
        for(int rowIdx = 1; rowIdx < word1.length(); rowIdx++){
            dp[rowIdx][0] = rowIdx - firstColDec;
        }
    }
};
