/**
 * https://leetcode.com/problems/kids-with-the-greatest-number-of-candies
 * @param candies an array with the number of candies for each kid.
 * @param candiesSize the length of the candies array.
 * @param extraCandies the number of extra candies to give.
 * @param returnSize an output parameter to tell the caller the length
 * of the allocated array holding the result.
 * @return an allocated boolean array telling whether kid[i] can have the
 * maximal number of candies if it is given the extra candies.
 *
 * Note: The returned array must be malloced, assume caller calls free().
 * SOLUTION STARTS HERE
 */
int getMaxElem(int* nums, int numsLen);
int max(int x0, int x1);
bool* kidsWithCandies(int* candies, int candiesSize, int extraCandies, int* returnSize) {
    bool* pRes = (bool*)malloc(candiesSize * sizeof(bool));

    int maxCandies = getMaxElem(candies, candiesSize);
    int minimalCandiesNeeded = maxCandies - extraCandies;
    for(int candIdx = 0; candIdx < candiesSize; candIdx++){
        pRes[candIdx] = candies[candIdx] >= minimalCandiesNeeded;
    }

    //Don't free it, the user needs it.
    *returnSize = candiesSize;
    return pRes;
}

int getMaxElem(int* nums, int numsLen){
    //assumes numsLen >= 1.
    int maxElem = nums[0];
    for(int idx = 0; idx < numsLen; idx++){
        maxElem = max(maxElem, nums[idx]);
    }
    return maxElem;
}

int max(int x0, int x1){
    return x0 > x1 ? x0 : x1;
}
