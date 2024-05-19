/**
 * https://leetcode.com/problems/minimum-size-subarray-sum
 * #two_pointers #array
 *
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
int minSubArrayLen(int target, int* nums, int numsSize) {   
    int backIdx = -1;
    int sum = 0;
    int minSubArrLen = numsSize + 1;
    for(int frontIdx = 0;
        frontIdx < numsSize && backIdx <= frontIdx;
        frontIdx++){
        sum += nums[frontIdx];
        if(sum >= target){
            ///move backIdx and update minSubArrLen
            while(sum >= target && backIdx < frontIdx){
                minSubArrLen = frontIdx - backIdx < minSubArrLen ?
                               frontIdx - backIdx : minSubArrLen;
                backIdx++;
                sum -= nums[backIdx];
            }
        }
    }
        
    int res = minSubArrLen == numsSize + 1 ? 0 : minSubArrLen;
    return res;
}
