/**
 * Read the question description here:
 * https://leetcode.com/problems/max-number-of-k-sum-pairs
 * 
 * #two-pointers #sort
 */
///SOLUTION
/// If you read the solution, I decided to use the qsort in 
/// stdlib instead of implementing merge-sort by myself.
#include <stdlib.h>
void sort(int* nums, int numsLen);
int maxOperations(int* nums, int numsSize, int k){
    sort(nums, numsSize);
    int opCount = 0;
    int leftIdx = 0;
    int rightIdx = numsSize - 1;
    int pairSum = 0;
    while(leftIdx < rightIdx){
        pairSum = nums[leftIdx] + nums[rightIdx]; 
        if(pairSum == k){
            opCount++;
            leftIdx++;
            rightIdx--;
        }else if(pairSum < k){
            leftIdx++;
        }else{
            rightIdx--;
        }
    }
    return opCount;
}

int comp(const void* pFirstVal, const void* pSecondVal) {
    int firstVal = *((int*)pFirstVal);
    int secondVal = *((int*)pSecondVal);
    int res = 0;
    if(firstVal < secondVal){
        res = -1;
    }else if(firstVal > secondVal){
        res = 1;
    }else{
        res = 0;
    }
    return res;
}

void sort(int* nums, int numsLen){
    qsort(nums, numsLen, sizeof(int), comp);
}
