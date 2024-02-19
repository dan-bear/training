int sumArray(int array[], int arrayLen){
    int sum = 0;
    for(int idx = 0; idx < arrayLen; idx++){
        sum += array[idx];
    }
    return sum;
}
