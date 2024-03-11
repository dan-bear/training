/**
 * Please read the description here:
 * https://leetcode.com/problems/find-the-difference-of-two-arrays
 *
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 *
 * #merge-sort. #binary-search
 * #hash-tables
 */
///SOLUTION
///Note: I used the qsort in stdlib instead of implementing a merge sort myself.
#include <stdlib.h>
int comp(const void* pIntVal1, const void* pIntVal2){
    return ( *((int*)pIntVal1) - *((int*)pIntVal2) );
}

int binarySearch(int* sortedNums, int len, int target);
void fillDistinct(int* nums1, int nums1Size, int* nums2, int nums2Size, int* distinctElemsOut);
int countDistinct(int* nums1, int nums1Size, int* nums2, int nums2Size);

int** findDifference(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize, int** returnColumnSizes) {
    qsort(nums1, nums1Size, sizeof(int), comp);
    qsort(nums2, nums2Size, sizeof(int), comp);

    int** lists = (int**)malloc(2 * sizeof(int*));
    int* distinctValsCount = (int*)malloc(2 * sizeof(int));
    
    distinctValsCount[0] = countDistinct(nums1, nums1Size, nums2, nums2Size);
    distinctValsCount[1] = countDistinct(nums2, nums2Size, nums1, nums1Size);
    ///Note: one could have avoid the first phase of calculating the
    ///number of distinct values by allocating the maximal possible
    ///number of distinct values, which are nums1Size and nums2Size
    ///and then calculate the number of the distinct values while
    ///filling the array (during fillDistinct method). From complexity point
    ///of view, it does not matter, the as the space complexity it still
    ///O(max(nums1Size, nums2Size)) due to the merge sort.
    lists[0] = (int*)malloc(distinctValsCount[0] * sizeof(int));
    lists[1] = (int*)malloc(distinctValsCount[1] * sizeof(int));
    fillDistinct(nums1, nums1Size, nums2, nums2Size, lists[0]);
    fillDistinct(nums2, nums2Size, nums1, nums1Size, lists[1]);

    *returnSize = 2;
    *returnColumnSizes = distinctValsCount;
    return lists;
}

int binarySearch(int* sortedNums, int len, int target){
    int leftIdx = 0;
    int rightIdx = len - 1;
    int midIdx = -1;
    int res = -1;
    while(leftIdx <= rightIdx && res < 0){
        midIdx = (leftIdx + rightIdx) / 2;
        if(sortedNums[midIdx] == target){
            res = midIdx;
        }else{
            if(sortedNums[midIdx] < target){
                leftIdx = midIdx + 1;
            }else{
                rightIdx = midIdx - 1;
            }
        }
    }
    return res;
}

//count the number of elements in nums1 that do not appear in nums2
int countDistinct(int* nums1, int nums1Size, int* nums2, int nums2Size){
    int distinctCount = 0;
    for(int idx = 0; idx < nums1Size; idx++){
        ///Note that each value should appear only once,
        ///since nums1 is sorted, this check can be done
        ///by checking the previous element.
        if(idx == 0 || nums1[idx - 1] != nums1[idx]){
            if(binarySearch(nums2, nums2Size, nums1[idx]) < 0){
                distinctCount++;
            }
        }
    }
    return distinctCount;
}

//Fill the given array with the elements in nums1 that do not appear in nums2
void fillDistinct(int* nums1, int nums1Size, int* nums2, int nums2Size, int* distinctElemsOut){
    int distinctIdx = 0;
    for(int idx = 0; idx < nums1Size; idx++){
        ///Note that each value should appear only once,
        ///since nums1 is sorted, this check can be done
        ///by checking the previous element.
        if(idx == 0 || nums1[idx - 1] != nums1[idx]){
            if(binarySearch(nums2, nums2Size, nums1[idx]) < 0){
                distinctElemsOut[distinctIdx] = nums1[idx];
                distinctIdx++;
            }
        }
    }
}
