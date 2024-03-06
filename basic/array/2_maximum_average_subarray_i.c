/**
 * Please read the question description here:
 * https://leetcode.com/problems/maximum-average-subarray-i
 * #array #sliding window
 */
///SOLUTION
double findMaxAverage(int* nums, int numsSize, int k) {
    int leftIdx = 0;
    int rightIdx = k - 1;    
    int sum = 0;
    for(int idx = leftIdx; idx <= rightIdx; idx++){
        sum += nums[idx];
    }

    int maxSum = sum;
    while(rightIdx < numsSize - 1){
        sum -= nums[leftIdx];
        leftIdx++;
        rightIdx++;
        sum += nums[rightIdx];
        maxSum = maxSum > sum ? maxSum : sum;
    }
    return (double)maxSum / (double)k;
}
