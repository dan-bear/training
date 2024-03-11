/**
 * Implement the function:
 * int calcNumOfDifferentVals(int* array, int arrLen)
 * The function calculates the number of different values
 * in an array.
 * Example1:
 * array = [1, 0, -3, 2, -3, 1, -3, 2, 7, 0, 7]
 * The number of different elements is 5 (1, 0, -3, 2, 7).
 * Example2:
 * array = [100, 100, 100, 100]
 * The number of different elements is 1, since the array
 * contains only the value 100.
 * @param array an array with integers.
 * @param arrLen the number of elements in the array.
 * @return how many different elements are there in the array.
 * 
 */
///SOLUTION
#include <stdlib.h>
int compareInt(const void* pIntVal1, const void* pIntVal2);
int calcNumOfDifferentVals(int* array, int arrLen)
{
    /// complexity: Time(arrLen) = arrLen * log(arrLen)
    ///             Space(arrLen) = arrLen.
    qsort(array, arrLen, sizeof(int), compareInt);
    
    int numOfDifferentVals = 1;
    int previousVal = array[0];
    for (int idx = 1; idx < arrLen; idx++) {
        if (array[idx] != previousVal) {
            numOfDifferentVals++;
            previousVal = array[idx];
        }
    }
    return numOfDifferentVals;
}

int compareInt(const void* pIntVal1, const void* pIntVal2){
    return *((int*)pIntVal1) - *((int*)pIntVal2);
}

/// A print based test.
// #include <stdio.h>
// int main()
// {
//     int nums[] = {9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0, 0};
//     printf("%d", calcNumOfDifferentVals(nums, 20));
//     return 0;
// }
