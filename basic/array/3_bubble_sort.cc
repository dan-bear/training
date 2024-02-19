/**
 * Implement a function that runs the bubble sort algorithm.
 * Function signature: void bubbleSort(int array[], int len)
 * @note it's assumed the bubble sort algorithm is known, if
 * not, please visit https://www.geeksforgeeks.org/bubble-sort/
 */


//Forward declaration.
void bubbleIteration(int array[], int len);

void bubbleSort(int array[], int len){
    for (int currentLen = len; currentLen > 0; currentLen--){
        bubbleIteration(array, currentLen);
    }

    // Question, does the next code works? if not, explain
    // why. If it does, which of the solution is "better"
    // performance wise?
    
    // for (int iteration = 0; iteration < len; iteration++) {
    //     bubbleIteration(array, len);
    // }
}

void swap(int array[], int idx1, int idx2){
    int elemInIdx1 = array[idx1];
    int elemInIdx2 = array[idx2];
    array[idx1] = elemInIdx2;
    array[idx2] = elemInIdx1;
}

void bubbleIteration(int array[], int len){
    for (int idx = 0; idx < len - 1; idx++){
        if(array[idx] > array[idx + 1]){
            swap(array, idx, idx + 1);
        }
    }
}
