/**
 * The function to implement is: 
 * https://leetcode.com/problems/rearrange-array-elements-by-sign/description/
 * Implement the next function: int* rearrangeArray(int nums[], int numsLen) where:
 * 1: nums[] is an array of number consisting of an equal number of positive and negative integer.
 * 2: numsLen is the length of nums.
 * The function should return an array of integers (int*) that contains the integers appearing
 * in nums under the next conditions:
 * 1: Every even index (0, 2, ... ) contains a positive integer.
 * 2: Every odd index (1, 3, ... ) contains a negative integer.
 * 3: For integers of the same sign, the order they appear in the output array is the same
 *    order as in nums.
 * For example: nums = {1,2,-1,-3,4,-2}
 * The output array should be {1, -1, 2, -3, 4, -2}.
 * Note that the next output: {1, -2, 4, -3, 2, -1} is invalid since also the numbers are
 * ordered such that positives are in even index and negative are in odd index, the order
 * within the positives and the negatives was not preserved. For example, 2 appeared before
 * 4 in nums and in this example, 2 appears after 4.
 */
///SOLUTION
#include <stdlib.h>
int* rearrangeArray(int nums[], int numsLen) {
    int* rearrangedArr = (int*)malloc(numsLen * sizeof(int));
    int posIdx = 0;
    int negIdx = 1;
    for(int idx = 0; idx < numsLen; idx++){
        if(nums[idx] < 0){
            rearrangedArr[negIdx] = nums[idx];
            negIdx += 2;
        }else{
            rearrangedArr[posIdx] = nums[idx];
            posIdx += 2;
        }
    }
    return rearrangedArr;
}
