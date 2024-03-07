/**
 * Please read the description here:
 * https://leetcode.com/problems/max-consecutive-ones-iii
 * #array #sliding-window
 */
///SOLUTION (note, there are two similar solutions, 
///I personally find the second a more elegent one).
int max(int val1, int val2);
int decInSingleZero(int* nums, int backIdx);
int longestOnes(int* nums, int numsSize, int k) {
    ///Soltion1:
    int numOfZerosInWindow = 0;
    int maxNumOfOnes = 0;
    int backIdx = 0;
    for(int frontIdx = 0; frontIdx < numsSize; frontIdx++){
        if(nums[frontIdx] == 0){
            numOfZerosInWindow++;
            if(numOfZerosInWindow == k + 1){
                backIdx = decInSingleZero(nums, backIdx);
                numOfZerosInWindow--;
            }
        }
        maxNumOfOnes = max(maxNumOfOnes, frontIdx - backIdx + 1);
    }
    return maxNumOfOnes;

    ///Solution2
    //int maxNumOfOnes = 0;
    //int zeroCount = 0;
    //int backIdx = 0;
    //for(int frontIdx = 0; frontIdx < numsSize; frontIdx++){
    //    if(nums[frontIdx] == 0){
    //        zeroCount++;
    //    }
    //    while(zeroCount > k){
    //    //need to move the back to reduce the number of zeros.
    //        if(nums[backIdx] == 0){
    //            zeroCount--;
    //        }
    //        backIdx++;
    //    }
    //    maxNumOfOnes = max(maxNumOfOnes, frontIdx - backIdx + 1);
    //}
    //return maxNumOfOnes;
}

int max(int val1, int val2){
    return val1 > val2 ? val1 : val2;
}

int decInSingleZero(int* nums, int backIdx){
    bool bFoundZero = false;
    while(!bFoundZero){
        bFoundZero = (nums[backIdx] == 0);
        backIdx++;
    }
    return backIdx;
}
