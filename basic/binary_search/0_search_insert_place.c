/**
 * Please read the description here:
 * https://leetcode.com/problems/search-insert-position/
 */
///SOLUTION
int searchInsert(int* nums, int numsSize, int target) {
    ///Note: this solution just modifies the binary search
    ///return value in case target is not in the list.
    int leftIdx = 0;
    int rightIdx = numsSize - 1;
    while (leftIdx <= rightIdx) {
        int midIdx = (leftIdx + rightIdx) / 2;
        if (nums[midIdx] == target) {
            return midIdx;
        } else {
            if (nums[midIdx] < target) {
                leftIdx = midIdx + 1;
            } else {
                rightIdx = midIdx - 1;
            }
        }
    }
    return rightIdx + 1;    
    
    
    //// Here is another solution that is more explicit
    //// but demands more condition checks.
    // int res = -1;
    // int leftIdx = 0;
    // int rightIdx = numsSize - 1;
   
    // while(leftIdx <= rightIdx){
    //     int middleIdx = (leftIdx + rightIdx) / 2;
    //     if(nums[middleIdx] == target){
    //         res = middleIdx;
    //         break;
    //     }else{
    //         if(nums[middleIdx] < target){
    //             if(middleIdx + 1 < numsSize){
    //                 if(target < nums[middleIdx + 1]){
    //                     res = middleIdx + 1;
    //                     break;
    //                 }else{
    //                     //search in right part.
    //                     leftIdx = middleIdx + 1;
    //                 }
    //             }else{ //target > all elements in nums.
    //                 res = numsSize;
    //                 break;
    //             }
    //         }else{//nums[middleIdx] > target
    //             if(middleIdx - 1 >= 0){
    //                 if(target > nums[middleIdx - 1]){
    //                     res = middleIdx;
    //                     break;
    //                 }else{
    //                     //search in left part.
    //                     rightIdx = middleIdx - 1;
    //                 }
    //             }else{ //target < all elements in nums.
    //                 res = 0;
    //                 break;
    //             }
    //         }
    //     }
    // }
    // return res;
}
