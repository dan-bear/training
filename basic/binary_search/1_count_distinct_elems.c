/**
 * Given two sorted arrays of nums, sortedNums1 and
 * sortedNums2, count the number of distinct values in
 * sortedNums1 with respect to sortedNums2. 
 * That means, how may DIFFERENT numbers in nums1 do not
 * appear in nums2.
 * For example:
 * nums1 = [1, 1, 2, 3, 4]
 * nums2 = [2, 3, 5, 6]
 * the result should be 2 since 1 and 4 are the values that
 * appear only in nums1 but not in nums2. Note that also 1
 * appears twice in nums1 it's counted only once.
 * 
 * Function signature:
 * int countDistinct(int* sortedNums1, int nums1Size, int* sortedNums2, int nums2Size)
 * 
 * @param sortedNums1 the array that its distinct values 
 * count should be calculated.
 * @param nums1Size sortedNums1 number of elements.
 * 
 * @param sortedNums2 the array to compare sortedNums1 with.
 * @param nums1Size sortedNums2 number of elements.
 * @return the number of DIFFERENT distinct values in sortedNums1.
 * 
 */
///SOLUTION
int binarySearch(int* sortedNums, int len, int target);
int countDistinct(int* sortedNums1, int nums1Size, int* sortedNums2, int nums2Size){
    int distinctCount = 0;
    for(int idx = 0; idx < nums1Size; idx++){
        ///Note that each value should appear only once,
        ///since nums1 is sorted, this check can be done
        ///by checking the previous element.
        if(idx == 0 || sortedNums1[idx - 1] != sortedNums1[idx]){
            if(binarySearch(sortedNums2, nums2Size, sortedNums1[idx]) < 0){
                distinctCount++;
            }
        }
    }
    return distinctCount;
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

/// Simple print based test.
//#include <stdio.h>
// int main()
// {
//     int nums1[] = { 2, 2, 2, 4, 6,};
//     int nums2[] = { 1, 4, 6,};
//     printf("%d", countDistinct(nums1, 5, nums2, 3));
//     return 0;
// }
