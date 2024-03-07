/**
 * Please read the description here:
 * https://leetcode.com/problems/find-pivot-index
 * #prefix-sum
 */
int sum(int* nums, int numsSize);
int pivotIndex(int* nums, int numsSize) {
    int resIdx = -1;
    int sumOfNums = sum(nums, numsSize);
    int prefixSum = 0;
    for(int idx = 0; idx < numsSize && resIdx < 0; idx++){
        if(prefixSum == sumOfNums - nums[idx] - prefixSum){
            resIdx = idx;
        }
        prefixSum += nums[idx];
    }
    return resIdx;
}

int sum(int* nums, int numsSize){
    int sum = 0;
    for(int idx = 0; idx < numsSize; idx++){
        sum += nums[idx];
    }
    return sum;
}
