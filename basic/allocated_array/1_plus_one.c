/**
 * https://leetcode.com/problems/plus-one/
 * 
 * Implement the function int* plusOne(int* digits, int digitsSize, int* returnSize)
 * The function parameters are:
 * 1: digits - an array of digits representing a number when the
 *    most siginificant digits is in index 0. For example, 123 is 
 *    represented as [1, 2, 3].
 *    Note: digits[idx] belongs to the set {0,1,2,3,4,5,6,7,8,9}.
 * 2: digitsSize - the number of digits in the digits array.
 * 3: returnSize - an output parameter for the number of integers allocated
 *                 in the result, this way, the caller can know what's the
 *                 length of your result and work with it. Just like you
 *                 need digitsSize in order to work with digits.
 * The function returns an array of digits that represent the result of
 * adding 1 to the give number represented in digits.
 * Example1: digits = {1, 2, 3}
 *           result = {1, 2, 4}
 * Example2: digits = {4, 3, 2, 1}
 *           result = {4, 3, 2, 2}
 * Example1: digits = {9}
 *           result = {1, 0}
 *
 * Note: The returned array must be malloced, assume caller calls free().
 *
 */
///Forward declaration.
bool isMaxNumOfGivenLen(int* digits, int digitsSize);
int calcNumOfDigitsInRes(int digitsSize, bool bIsMaxNumOfGivenLen);

///SOLUTION:
int* plusOne(int* digits, int digitsSize, int* returnSize) {
    bool bIsMaxNumOfGivenLen = isMaxNumOfGivenLen(digits, digitsSize);
    int numOfDigitsInRes = calcNumOfDigitsInRes(digitsSize, bIsMaxNumOfGivenLen);

    int* pPlusOneRes = (int*)malloc(numOfDigitsInRes * sizeof(int));

    int carry = 1;
    int resIdx = numOfDigitsInRes - 1;
    for(int idx = digitsSize - 1; idx >= 0; idx--){
        int currDigit = (carry + digits[idx]) % 10;
        carry = (carry + digits[idx]) / 10;//0 or 1.
        pPlusOneRes[resIdx] = currDigit;
        resIdx--;
    }
    //If carry == 1, it means we moved from 99...9 to 100...0
    //so 1 should be written:
    if(carry == 1){
        pPlusOneRes[0] = 1;
    }

    //don't forget the output parameter.
    *returnSize = numOfDigitsInRes;
    return pPlusOneRes;
}

bool isMaxNumOfGivenLen(int* digits, int digitsSize){
    int maxDigit = 9;
    bool bMaxNumOfGivenLen = true;
    for(int idx = 0; idx < digitsSize; idx++){
        if(digits[idx] != maxDigit){
            bMaxNumOfGivenLen = false;
            break;
        }
    }
    return bMaxNumOfGivenLen;
}

int calcNumOfDigitsInRes(int digitsSize, bool bIsMaxNumOfGivenLen){
    int numOfDigitsInRes = -1;
    if(bIsMaxNumOfGivenLen){
        numOfDigitsInRes = digitsSize + 1;
    }else{
        numOfDigitsInRes = digitsSize;
    }
    //Another option for the if-else above:
    //int numOfDigitsInRes = bIsMaxNumOfGivenLen ? digitsSize + 1 : digitSize;
    return numOfDigitsInRes;
}
