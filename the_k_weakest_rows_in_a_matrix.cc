/**
 * https://leetcode.com/problems/the-k-weakest-rows-in-a-matrix
 */
class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        vector<pair<int,int>> scoreAndIdxPairs = calcScoreAndIdxPairs(mat);
        sort(scoreAndIdxPairs.begin(), scoreAndIdxPairs.end(), sLessOrEqual);
        vector<int> res = calcKWeakestRows(scoreAndIdxPairs, k);      
        return res;
    }

private:
    vector<pair<int,int>> calcScoreAndIdxPairs(const vector<vector<int>>& mat){
        vector<pair<int,int>> scoreAndIdxPairs;
        for(int rowIdx = 0 ; rowIdx < mat.size(); rowIdx++){
            int score = calcRowScore(mat, rowIdx);
            scoreAndIdxPairs.push_back(pair<int,int>(score, rowIdx));
        }
        return scoreAndIdxPairs;
    }

    int calcRowScore(const vector<vector<int>>& mat, int rowIdx){
        int score = 0;
        for(int val: mat[rowIdx]){
            if(val == 0){
                break;
            }
            score += val;
        }
        return score;
    }

    vector<int> calcKWeakestRows(vector<pair<int,int>> sortedScoreAndIdxPairs, int k){
        vector<int> res(k, -1);
        for(int pairIdx = 0; pairIdx < k; pairIdx++){
            res[pairIdx] = sortedScoreAndIdxPairs[pairIdx].second;
        }
        return res;
    }


    static bool sLessOrEqual(const pair<int,int>& pair1, const pair<int,int>& pair2){
        return (pair1.first < pair2.first) ||
         (pair1.first == pair2.first && pair1.second <= pair2.second);
    }
};
