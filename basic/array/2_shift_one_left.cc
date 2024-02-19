/**
 * The function gets an array and its length and shift 
 * all its element one index to the left in a cyclic
 * manner (i.e. the 0 element is shifted to the len - 1 
 * index).
 * For example: array = {1, 2, 3, 4}
 * After calling shiftOneLeft the array changes to: {2, 3, 4, 1}.
 *
 * Note: a more efficient solution would be to use
 *       mem copy, but it is not covered in a basic
 *       course.
 */
void shiftOneLeft(int array[], int arrayLen){
    int nextElement = array[0];
    for(int idx = arrayLen - 1; idx >= 0; idx--){
        int saveCurrentElement = array[idx];
        array[idx] = nextElement;
        nextElement = saveCurrentElement;
    }
}
