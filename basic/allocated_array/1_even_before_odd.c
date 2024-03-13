/**
 * Implement the function:
 * void evenBeforeOdd(int* arr, int len)
 * @param arr an array with integers.
 * @param len the number of elements in the array.
 * The function changes the array so all the EVEN-INDEXED
 * elements appear before the ODD-INDEXED elements while
 * preserving the order of the even and odd indexed elements
 * withing themselves.
 * Example1:
 * arr = [10, 13, 11, 12]
 * after the function is called the array elements are:
 * arr = [10, 11, 13, 12]
 * @note that the [10, 11, 12, 13] is an invalid solution 
 * since 13's index is smaller than 10's index in the array
 * (that's the meaning of order preserving).
 * 
 * Example2:
 * arr = [20, 30, 40, 50, 60, 70, 80]
 * after calling the function the arr changes to:
 * arr = [20, 40, 60, 80, 30, 50, 70]
 * 
 * @note try to implement it in 
 * Time complexity = Theta(len)
 * Space complexity = Theta(len)
 */
/// Solution:
#include <stdlib.h>
void evenBeforeOdd(int* arr, int len)
{
    /// step0: calculate the number of odd and even indexes
    ///        and allocate arrays to store the elements in.
    int numOfOddIdxs = len / 2;
    int numOfEvenIdxs = len - numOfOddIdxs;

    int* evenArr = (int*)malloc(numOfEvenIdxs * sizeof(int));
    int* oddArr = (int*)malloc(numOfOddIdxs * sizeof(int));

    /// step1: filling the evenArr and offArr with the
    ///        array's elements.
    int evenArrFrontIdx = 0;
    int oddArrFrontIdx = 0;
    for (int idx = 0; idx < len; idx++) {
        if (idx % 2 == 0) {
            evenArr[evenArrFrontIdx] = arr[idx];
            evenArrFrontIdx++;
        } else {
            oddArr[oddArrFrontIdx] = arr[idx];
            oddArrFrontIdx++;
        }
    }

    /// step2: write back to the array, so all the even
    ///        indexed elements appear before the odd indexed
    ///        elements.
    for (int idx = 0; idx < numOfEvenIdxs; idx++) {
        arr[idx] = evenArr[idx];
    }
    for (int idx = 0; idx < numOfOddIdxs; idx++) {
        arr[numOfEvenIdxs + idx] = oddArr[idx];
    }

    /// Step3: free the memory use for storing the even and
    ///        odd arrays, as they are not needed anymore.
    free(evenArr);
    free(oddArr);
}
