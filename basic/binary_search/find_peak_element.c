/**
 * https://leetcode.com/problems/find-peak-element
 * #binary earch
 */
///Go to the middle:
///If it's a pick, cool.
///If it's not a pick, it means that:
///   1: It's a vally.
///   2: It's a left-right decreasing triplet.
///   3: It's a left-right increasing triplet.
///If it's a vally:
///    choose one of the sides, and contiue the search.
///If it's a left-right decreasing triplet:
///    continue the search in the left part.
///If it's a left-right increasing triplet:
///    continus the search in the right part.
long long power(long long base, long long exp);
int findPeakElement(int* nums, int numsSize) {
    int leftIdx = 0;
    int rightIdx = numsSize - 1;
    long long lowestVal = -1 * power(2, 32);
    int midIdx = -1;
    while(leftIdx <= rightIdx){
        midIdx = (leftIdx + rightIdx) / 2;  
        long long midVal = (nums[midIdx]);
        long long leftVal = midIdx > 0 ? nums[midIdx - 1] : lowestVal;
        long long rightVal = midIdx < numsSize - 1 ? nums[midIdx + 1] : lowestVal;
        if(midVal > leftVal && midVal > rightVal){
            break;
        }else if(midVal < leftVal){
            rightIdx = midIdx - 1;
        }else{
            leftIdx = midIdx + 1;
        }
    }
    return midIdx;
}


long long power(long long base, long long exp){
    long long res = 1;
    while(exp > 0){
        res *= base;
        exp--;
    }
    return res;
}
