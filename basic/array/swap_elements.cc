/**
 * Replace the elements between two given indexes.
 * @note before replacement, check the given indexes are valid
 * so the execution won't cause an invalid memory access. If
 * one of the indexes is invalid, just return from the function.
 * @param array an integer array.
 * @param arrayLen the length of the array.
 * @param idx1 the index of the first element to swap.
 * @param idx2 the index of the second element to swap.
 */
void swapElements(int array[], int arrayLen, int idx1, int idx2){
    int lastIdx = arrayLen - 1;
    int firstIdx = 0;
    //Don't touch the array if the indexes are not in range.
    if(idx1 >= firstIdx && idx2 >= firstIdx && idx1 <= lastIdx && idx2 <= lastIdx){
        int saveIdx1Element = array[idx1]
        array[idx1] = array[idx2];
        array[idx2] = saveIdx1Element;
    }
}
