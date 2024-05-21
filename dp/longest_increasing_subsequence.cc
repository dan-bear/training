/**
 * #dp #DP
 * https://leetcode.com/problems/longest-increasing-subsequence
 */
class Solution {
public:
    /**
     * Edge cases:
     * 1: nums size is 0.
     * 2: nums size = max_int + 1 and nums[i] = i.
     *    the longest subsequence is max_int + 1, but
     *    it leads to int overflow.
     * Algorithm:
     * dp[i] = max subsequence till index i.
     * dp[0] = 1.
     * dp[i > 0] = iterate j in range(i):
     *                 calc the max dp[j] such that nums[i] > nums[j].
     *             write max(1, calculated result) in dp[i].
     * 
     */
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(), 1);
        for(int idx = 1; idx < nums.size(); idx++){
            dp[idx] = findLargestSubsequenceEndingInIdx(nums, dp, idx);
        }
        return ranges::max(dp);
    }
private:
    int findLargestSubsequenceEndingInIdx(const vector<int>& nums,
                                           const vector<int>& dp,
                                           const int lastElemIdx){
        int maxSubsequenceLenWithLastElemIdx = 1;
        for(int prevElemIdx = 0; prevElemIdx < lastElemIdx; prevElemIdx++){
            if(nums[lastElemIdx] > nums[prevElemIdx]){
                maxSubsequenceLenWithLastElemIdx = max(
                    maxSubsequenceLenWithLastElemIdx, dp[prevElemIdx] + 1);
            }
        }
        return maxSubsequenceLenWithLastElemIdx;
    }
};
