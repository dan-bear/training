/**
 * Please read the description here:
 * https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element
 * #array #sliding-window
 */
///SOLUTION
int max(int val1, int val2);
int longestSubarray(int* nums, int numsSize) {
    ///So it's all about finding the longest window with at most a single 0.
    ///and return its length - 1.
    int zeroCount = 0;
    int backIdx = 0;
    int maxSubArrLen = 0;
    for(int frontIdx = 0; frontIdx < numsSize; frontIdx++){
        if(nums[frontIdx] == 0){
            zeroCount++;
        }
        while(zeroCount > 1){
            if(nums[backIdx] == 0){
                zeroCount--;
            }
            backIdx++;
        }
        maxSubArrLen = max(maxSubArrLen, frontIdx - backIdx + 1);
    }
    ///got the length of the max sub array that contains at most a single 0.
    ///Now, let's delete one element.
    ///Note: one could have changed the last line in the for loop to:
    ///maxSubArrLen = max(maxSubArrLen, frontIdx - backIdx);
    ///and by that to avoid decreasing maxSubArrLen by -1 here.
    return maxSubArrLen - 1;
}

int max(int val1, int val2){
    return val1 > val2 ? val1 : val2;
}
