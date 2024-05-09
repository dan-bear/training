/**
 * https://leetcode.com/problems/house-robber
 * #dp #one_dim_dp #DP
 */
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size() == 1){
            return nums[0];
        }
        vector<int> prices(nums.size(), 0);
        prices[0] = nums[0];
        prices[1] = max(nums[0], nums[1]);
        for(int idx = 2; idx < nums.size(); idx++){
            prices[idx] = max(prices[idx - 2] + nums[idx], prices[idx - 1]);
        }
        return prices.back();

        ///Another solution without additional vector.
        //if(nums.size() == 1){
        //    return nums[0];
        //}
        // nums[1] = max(nums[0], nums[1]);
        // for(int idx = 2; idx < nums.size(); idx++){
        //     nums[idx] = max(nums[idx - 2] + nums[idx], nums[idx - 1]);
        // }
        // return nums.back();
    }
};
