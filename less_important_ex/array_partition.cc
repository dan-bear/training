/**
 * https://leetcode.com/problems/array-partition
 */
class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int res = 0;
        for(int idx = 0; idx < nums.size(); idx += 2){
            res += nums[idx];
        }
        return res;
    }
};
