/**
 * Rearrange an integer array so all the positive elements
 * (element >= 0) appears before the strictly-negative
 * elements (element < 0).
 * 
 * For example:
 * array = {-1, 1, -2, 2, -3}
 * One of the possible arrangements of the array after the
 * function is executed is {1, 2, -2, -1, -3}.
 * Another valid solution is {2, 1, -3, -1, -2}.
 * @note the order within the positive elements and the 
 * negative elements does not matter, so there might be
 * many array arrangements that satisfy the condition.
 * 
 * @param array an array with integers.
 * @param arrayLen the length of the array.
 */
void positiveBeforeNegative(int array[], int arrayLen){
    int positiveIdx = 0;
    int negativeIdx = arrayLen - 1;
    while(positiveIdx < negativeIdx){
        if(array[positiveIdx] < 0 && array[negativeIdx] >= 0){
            // Cool, let's switch them.
            int temp = array[positiveIdx];
            array[positiveIdx] = array[negativeIdx];
            array[negativeIdx] = temp;
            // Move the indexes for the next round:
            positiveIdx++;
            negativeIdx--;
        }else{
            if(array[positiveIdx] >= 0){
                // element is in place, just move the index.
                positiveIdx++;
            }
            if(array[negativeIdx] < 0){
                // element is in place, just move the index.
                negativeIdx--;
            }
        }
    }
}
