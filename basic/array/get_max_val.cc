//Assume arrayLen > 0.
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
