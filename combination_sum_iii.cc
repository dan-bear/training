/**
 * https://leetcode.com/problems/combination-sum-iii
 * #dp
 */
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> res;
        vector<int> combination;
        searchAllCombinations(k, n, m_minNum, combination, res);
        return res;
    }

private:
    int m_minNum{1};
    int m_maxNum{9};

    void searchAllCombinations(int k, int n, int minNum ,
                               vector<int>& combination, vector<vector<int>>& res){
        if(k == 0 && n == 0){
            res.push_back(combination);
        }else if(k != 0 && n != 0){
            for(int val = minNum; val <= m_maxNum; val++){
                if(val <= n){
                    combination.push_back(val);
                    searchAllCombinations(k - 1, n - val, val + 1, combination, res);
                    combination.pop_back();
                }
            }
        }
    }

    

};
