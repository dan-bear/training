void flipArray(int array[], int arrayLen){
    int firstIdx = 0;
    int lastIdx = arrayLen - 1;
    int leftValue = 0;
    int rightValue = 0;
    while(firstIdx < lastIdx){
        // Swap the values.
        leftValue = array[firstIdx];
        rightValue = array[lastIdx];
        array[firstIdx] = rightValue;
        array[lastIdx] = leftValue;
        
        // move the indexes.
        firstIdx++;
        lastIdx--;
    }  

}
