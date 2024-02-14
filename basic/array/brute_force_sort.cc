/**
 * sort an array of integers in ascending order.
 * 
 * @param array an array with integers.
 * @param arrayLen the length of the array.
 * 
 * Hint: implement the next two functions and use them:
 *   
 *   First function returns the index of the maximal element
 *   in range: array[firstIdx],...,array[lastIdx].
 *   int findIdxOfMaxElementInRange(int array[], int firstIdx, int lastIdx);
 *   
 *   Second function swaps two element in an array.
 *   void swapElements(int array[], int idx1, int idx2);
 */

//Forward declaration.
int findIdxOfMaxElementInRange(int array[], int firstIdx, int lastIdx);
void swapElements(int array[], int idx1, int idx2);

//The sorter.
void bruteForceSort(int array[], int arrayLen)
{
    int lastIdx = arrayLen - 1;
    int firstIdx = 0;
    for (int currLastIdx = lastIdx; currLastIdx >= 0; currLastIdx--) {
        int idxOfMaxElement =
          findIdxOfMaxElementInRange(array, firstIdx, currLastIdx);
        // put the maximal value at its place.
        swapElements(array, idxOfMaxElement, currLastIdx);
    }
}

int findIdxOfMaxElementInRange(int array[], int firstIdx, int lastIdx)
{
    int maxElement = array[firstIdx];
    int maxElementIdx = firstIdx;
    for (int idx = firstIdx; idx <= lastIdx; idx++) {
        if (array[idx] > maxElement) {
            maxElement = array[idx];
            maxElementIdx = idx;
        }
    }
    return maxElementIdx;
}

void swapElements(int array[], int idx1, int idx2)
{
    int elementInIdx1 = array[idx1];
    array[idx1] = array[idx2];
    array[idx2] = elementInIdx1;
}
