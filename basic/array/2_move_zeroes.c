/**
 * Please read the description in:
 * https://leetcode.com/problems/move-zeroes
 * Note: int* nums is just the same as int nums[], so if
 * you are not familiar with pointers syntax yet, just
 * relate to nums as if its int nums[].
 * 
 */
///SOLUTION
void moveZeroes(int* nums, int numsSize) {
    int frontIdx = 0;
    for(int idx = 0; idx < numsSize; idx++){
        if(nums[idx] != 0){
            nums[frontIdx] = nums[idx];
            frontIdx++;
        }
    }
    /// from 0 to frontIdx - 1 all the numbers are non-zero.
    /// all that is left to do is to store the zeros.
    for(int idx = frontIdx; idx < numsSize; idx++){
        nums[idx] = 0;
    }
}
