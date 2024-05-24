/**
 * https://leetcode.com/problems/rotate-array/
 * #interesting #array
 */
///Solution: O(1) memory and O(numsSize) time.
void swap(int* ptr1, int* ptr2);
void reverse(int* nums, int firstIdx, int lastIdx);

void rotate(int* nums, int numsSize, int k) {
    k %= numsSize;
    reverse(nums, 0, numsSize - k - 1);
    reverse(nums, numsSize - k, numsSize - 1);
    reverse(nums, 0, numsSize - 1);    
}

void reverse(int* nums, int firstIdx, int lastIdx){
    while(firstIdx < lastIdx){
        swap(&nums[firstIdx], &nums[lastIdx]);
        firstIdx++;
        lastIdx--;
    }
}

void swap(int* ptr1, int* ptr2){
    int temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}
