/**
 * https://leetcode.com/problems/maximal-rectangle/
 * #dp #DP
 */
class Solution {
public:
    /**
     * dp[i][j] holds the dimension of the max rectangle whose
     * right-down corner coordinate is (i,j).
     * dp[i][j] = (0, 0) if matrix[i][j] == 0.
     * given dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] how
     * to determine dp[i][j] in case matrix[i][j] = 1.
     * given dp[i - 1][j] = (r1, c1) and dp[i][j - 1] = (r2, c2)
     * such that both are not (0 , 0).
     * Adding 
     *       
     *       1 1 
     *       1 1 -> (2, 2)
     * 1 1 1 1 1 
     *     (1,4)
     * 
     * (2, 2) and (1, 4)
     * option1: add 1 to (i, j-1) col dim: (1, 4) => (1, 5)
     * option2: add 1 to (i-1, j) row dim: (2, 2) => (3, 1)
     * option3: col = min(4, 2), row = 1 + row in (i - 1, j)
     * pick the maximum between the three options.
     */
    using Coor = array<int, 2>;
    int maximalRectangle(vector<vector<char>>& matrix) {
        int maxArea = 0;
        vector<vector<Coor>> dp(matrix.size() + 1,
                                vector<Coor>(matrix[0].size() + 1,
                                             Coor({0, 0})));
        for(int rowIdx = 1; rowIdx <= matrix.size(); rowIdx++){
            for(int colIdx = 1; colIdx <= matrix[0].size(); colIdx++){
                if(matrix[rowIdx - 1][colIdx - 1] != '0'){
                    dp[rowIdx][colIdx] = calcDpRule(matrix, dp, rowIdx, colIdx);
                    
                    maxArea = max(maxArea, calcArea(dp[rowIdx][colIdx]));
                }
                cout << "(" << dp[rowIdx][colIdx][0] << " , " << dp[rowIdx][colIdx][1] << ")" << " ";
            }
            cout << "\n";
        }


        return maxArea;
    }
private:
    int calcArea(const Coor& coordinate){
        return coordinate[0] * coordinate[1];
    }

    Coor calcDpRule(const vector<vector<char>>& matrix,
                    const vector<vector<Coor>>& dp,
                    int rowIdx,
                    int colIdx){
        vector<Coor> optionalDims(3);
        optionalDims[0] = {1, dp[rowIdx][colIdx - 1][1] + 1};
        optionalDims[1] = {dp[rowIdx - 1][colIdx][0] + 1};
        int mutualColDim = min(dp[rowIdx - 1][colIdx][1], dp[rowIdx][colIdx - 1][1] + 1);
        int mutualRowDim = dp[rowIdx - 1][colIdx][0] + 1;
        optionalDims[2] = {mutualRowDim, mutualColDim};
        Coor maxAreaCoor = getDimWithMaxArea(optionalDims);
        return maxAreaCoor;
    }

    Coor getDimWithMaxArea(const vector<Coor>& dims){
        int maxArea = 0;
        int maxAreaIdx = 0;
        for(int idx = 0; idx < dims.size(); idx++){
            int currentArea = calcArea(dims[idx]);
            if(currentArea > maxArea){
                maxArea = currentArea;
                maxAreaIdx = idx;
            }
        }
        return dims[maxAreaIdx];
    }




};
