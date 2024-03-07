/**
 * https://leetcode.com/problems/find-the-difference-of-two-arrays
 * #hash-table #sort #binary search
 */
class Solution {
public:
    vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> hash;
        for(int elem: nums1){
            if(!hash.count(elem)){
                hash[elem] = 1;
            }
        }
        for(int elem: nums2){
            if(!hash.count(elem)){
                hash[elem] = 2;
            }else{
                if(hash[elem] == 1){
                    hash[elem] = 3;//both appear.
                }
            }
        }
        vector<int> distinct1;
        vector<int> distinct2;
        for(auto& [key, value]: hash){
            if(value == 1){
                distinct1.push_back(key);
            }else if(value == 2){
                distinct2.push_back(key);
            }
        }
        //Another syntax without auto.
        //for(pair<const int, int>& keyValue: hash){
        //    if(keyValue.second == 1){
        //        distinct1.push_back(keyValue.first);
        //    }else if(keyValue.second == 2){
        //        distinct2.push_back(keyValue.first);
        //    }
        //}
        vector<vector<int>> res = {distinct1, distinct2};
        return res;
    }
};
