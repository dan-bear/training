/**
 * https://leetcode.com/problems/minimum-size-subarray-sum
 * #two_pointers #array
 */
class Solution {
public:
    /**
     * Edge cases:
     * 1: target = max_int.
     * 2: target = min_int
     * 3: nums.size() = 0
     * 4: The intermediate additions adds up to int overflow.
     * 
     * Note: the problem constraints eliminate the possibility
     *       for signed int overflow in intermediate results.
     *
     * Algorithm:
     * firstIdx = -1, lastIdx = 0.
     * start iterating with lastIdx.
     *      sum the range [firstIdx, lastIdx]
     *      if the sum >= target:
     *         - check whether the length of the range is smaller than
     *           the last previous range.
     *         - inc firstIdx by 1 till the sum is smaller than
     *           target or firstIdx reaches lastIdx.    
     */
    int minSubArrayLen(int target, vector<int>& nums) {
        int32_t backIdx = -1;
        uint32_t sum = 0;
        uint32_t u32Target = static_cast<uint32_t>(target);
        int32_t minSubArrLen = nums.size() + 1;

        for(int frontIdx = 0;
            frontIdx < nums.size() && backIdx <= frontIdx;
            frontIdx++){
            sum += static_cast<uint32_t>(nums[frontIdx]);
            
            if(sum >= target){
                ///move backIdx
                while(sum >= u32Target && backIdx < frontIdx){
                    minSubArrLen = min(minSubArrLen, frontIdx - backIdx);
                    backIdx++;
                    sum -= static_cast<uint32_t>(nums[backIdx]);
                }
            }
        }
        
        int res = minSubArrLen == nums.size() + 1 ? 0 : minSubArrLen;
        return res;
    }
};
