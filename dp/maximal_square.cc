/**
 * https://leetcode.com/problems/maximal-square
 * #dp #DP
 */
class Solution {
private:
    static constexpr char skZero{'0'};
    static constexpr char skOne{'1'};
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int rowDim = matrix.size();
        int colDim = matrix[0].size();
        vector<vector<int>> dp(rowDim, vector<int>(colDim, 0));
        
        int maxEdge = 0;
        for(int colIdx = 0; colIdx < colDim; colIdx++){
            if(matrix[0][colIdx] == skOne){
                dp[0][colIdx] = 1;
                maxEdge = 1;
            }
        }

        for(int rowIdx = 1; rowIdx < rowDim; rowIdx++){
            if(matrix[rowIdx][0] == skOne){
                dp[rowIdx][0] = 1;
                if(maxEdge == 0){
                    maxEdge = 1;
                }
            }

            for(int colIdx = 1; colIdx < colDim; colIdx++){
                if(matrix[rowIdx][colIdx] == skOne){
                    dp[rowIdx][colIdx] = 1 + min({dp[rowIdx - 1][colIdx - 1],
                                                  dp[rowIdx - 1][colIdx],
                                                  dp[rowIdx][colIdx - 1]});
                    
                    if(maxEdge < dp[rowIdx][colIdx]){
                        maxEdge = dp[rowIdx][colIdx];
                    }
                }
            }
        }

        return maxEdge * maxEdge;
    }
};
