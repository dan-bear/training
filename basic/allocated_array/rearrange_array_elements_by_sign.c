//https://leetcode.com/problems/rearrange-array-elements-by-sign/description/
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
