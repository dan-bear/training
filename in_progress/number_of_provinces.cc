/**
 * https://leetcode.com/problems/number-of-provinces
 * #graph #dfs
 */

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int count = 0;
        vector<bool> reachedState(isConnected.size(), false);
        for(int idx = 0; idx < reachedState.size(); idx++){
            if(!reachedState[idx]){
                count++;
                reachedState[idx] = true;
                expand(isConnected, reachedState, idx);
            }
        }
        return count;
    }

    void expand(const vector<vector<int>>& isConnected,
           vector<bool>& reachedState,
           int rowIdx){
        for(int colIdx = 0; colIdx < isConnected[rowIdx].size(); colIdx++){
            if(isConnected[rowIdx][colIdx] && !reachedState[colIdx]){
                reachedState[colIdx] = true;
                expand(isConnected, reachedState, colIdx);
            }
        }
    }
};
