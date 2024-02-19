/**
 * Note: a more efficient solution would be to use
 *       mem copy, but at this stage this subject
 *       is not covered.
 */
void shiftOneLeft(int array[], int arrayLen){
    int nextElement = array[0];
    for(int idx = arrayLen - 1; idx >= 0; idx--){
        int saveCurrentElement = array[idx];
        array[idx] = nextElement;
        nextElement = saveCurrentElement;
    }
}
