/**
 * Implement the function:
 * bool checkDistinctVals(int* array, int arrLen)
 * The function checks whether all the array's elements
 * are distinct, that means that no elements appear more 
 * than once.
 * Example1:
 * array = [1, 0, 2, 4, 3, 5, 7] the function returns true
 * since no element appears more than once.
 * Example2:
 * array = [1, 2, 3, 3, 3, 4] the function returns false
 * since 3 appears more than once.
 * 
 * @param array an array with integers.
 * @param arrLen the number of elements in the array.
 * @return whether each element appears only once in the
 * array.
 * 
 */
///SOLUTION
#include <stdbool.h>
int compareInt(const void* pIntVal1, const void* pIntVal2);
bool checkDistinctVals(int* array, int arrLen){
    ///Complexity: T(arrLen) = arrLen*log(arrLen).
    ///            S(arrLen) = arrLen.
    qsort(array, arrLen, sizeof(int), compareInt);
    bool bRes = true;
    for(int idx = 1; idx < arrLen && bRes; idx++){
        bRes = (array[idx] != array[idx - 1]);
    }
    return bRes;
}

int compareInt(const void* pIntVal1, const void* pIntVal2){
    return *((int*)pIntVal1) - *((int*)pIntVal2);
}

/// A print based test.
// #include <stdio.h>
// int main()
// {
//     int nums1[] = {9, 9, 8, 8, 7, 7, 6, 6};
//     int nums2[] = { 1, 4, 3, 6, 2 };
//     printf("%d\n", checkDistinctVals(nums1, 8));
//     printf("%d\n", checkDistinctVals(nums2, 5));
//     return 0;
// }
