/**
 * For the question description:
 * https://leetcode.com/problems/product-of-array-except-self
 * 
 * Note: The returned array must be malloced, assume caller calls free().
 */
///Solution1 (See solution2 below):
///complexity: O(numsSize) time and O(numsSize) space.
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    int multAll = 1;
    int multAllWithoutZeros = 1;
    int numOfZeros = 0;
    for(int idx = 0; idx < numsSize; idx++){
        multAll *= nums[idx];
        if(nums[idx] == 0){
            numOfZeros++;
        }else{
            multAllWithoutZeros *= nums[idx];
        }
    }

    int* pAnswer = (int*)malloc(numsSize * sizeof(int));
    for(int idx = 0; idx < numsSize; idx++){
        if(numOfZeros > 1){
            pAnswer[idx] = 0;
        }else{
            pAnswer[idx] = nums[idx] == 0 ? multAllWithoutZeros : multAll / nums[idx];
        }
    }

    *returnSize = numsSize;
    return pAnswer;
}

///Solution2:
/// Another option with the same complexity but without the zeros
/// edge case.
/// Define the prefixProd array such that prefixProd[i] is
/// the product of all the elements in indexes 0 to i-1 and
/// prefixProd[0] is 1.
/// Define the suffixProd array such that suffixProd[i] is 
/// the product of all the elements from i + 1 till len - 1
/// when suffixProd[len - 1] = 1.
/// Example: nums = [2, 3, 4, 5]
///          prefixProd = [1, 2, 6, 24]
///          suffixProd = [60, 20, 5, 1]
/// multiply prefixProd[i] with suffixProd[i] is actually
/// the product of all the number expect the i'th number.
/// since prefixProd[i] holds the product of all the
/// the elements in indexes 0...i-1 and suffixProd[i] holds
/// all the element in indexes i+1,...,len - 1.
int* productExceptSelf2(int* nums, int numsSize, int* returnSize) {
    ///One way to do it, is by allocating prefixProd and suffixProd
    ///calculating them and then to fill the answer array.

    int* pPrefixProd = (int*)malloc(sizeof(int) * numsSize);
    int* pSuffixProd = (int*)malloc(sizeof(int) * numsSize);
    int* pAnswer = (int*)malloc(sizeof(int) * numsSize);
    int leftProd = 1;
    for(int idx = 0; idx < numsSize; idx++){
        pPrefixProd[idx] = leftProd;
        leftProd *= nums[idx];
    }
    int rightProd = 1;;
    for(int idx = numsSize - 1; idx >= 0; idx--){
        pSuffixProd[idx] = rightProd;
        rightProd *= nums[idx + 1];
    }
    for(int idx = 0; idx < numsSize; idx++){
        pAnswer[idx] = pPrefixProd[idx] * pSuffixProd[idx];
    }
    free(pPrefixProd);
    free(pSuffixProd);
    *returnSize = numsSize;
    return pAnswer;

    ///However, it can be done while allocating a single array!. 
    // int* pAnswer = (int*)malloc(sizeof(int) * numsSize);
    // int leftProd = 1;
    // for(int idx = 0; idx < numsSize; idx++){
    //     pAnswer[idx] = leftProd;
    //     leftProd *= nums[idx];
    // }
    //
    /////now pAnswer holds the prefix product data.
    // int rightProduct = 1;
    // for(int idx = numsSize - 1; idx >= 0; idx--){
    //     pAnswer[idx] *= rightProduct;
    //     rightProduct *= nums[idx];
    // }
    // *returnSize = numsSize;
    // return pAnswer;
}
