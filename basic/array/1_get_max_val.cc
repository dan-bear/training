/**
 * The method finds the maximal value in a non-empy
 * array and returns its value.
 * Note - assume arrayLen > 0 (the array is not empty).
 */
int getMaxVal(int array[], int arrayLen){
    int currentMax = array[0];
    for(int idx = 0; idx < arrayLen; idx++){
        if(array[idx] > currentMax){
            currentMax = array[idx];
        }  
    }
    // this var is not needed, but makes the code
    // more experssive.
    int maxVal = currentMax;
    return maxVal;
}
