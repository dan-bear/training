/**
 * Please read the description here:
 * https://leetcode.com/problems/unique-number-of-occurrences
 * #sort #hash
 */
#include <stdlib.h>
///Forward declaration For solution1
void fillOccurencesArr(int* arr, int arrSize, int* occurencesArr);
bool checkOccurencesArr(int* arr, int* occurecesArr, int arrSize);

///Solution1: O(arrSize^2) time, O(arrSize) space. Without sorting.
///See solution2 below.
// bool uniqueOccurrences(int* arr, int arrSize) {
//     int* occurrencesArr = (int*)malloc(arrSize * sizeof(int));
//     fillOccurencesArr(arr, arrSize, occurrencesArr);
//     bool res = checkOccurencesArr(arr, occurrencesArr, arrSize);
//     free(occurrencesArr);
//     return res;
// }

void fillOccurencesArr(int* arr, int arrSize, int* occurrencesArr){
    for(int idx = 0; idx < arrSize; idx++){
        int occurrencesCount = 0;
        for(int jdx = 0; jdx < arrSize; jdx++){
            if(arr[idx] == arr[jdx]){
                occurrencesCount++;
            }
        }
        occurrencesArr[idx] = occurrencesCount;
    }
}

bool checkOccurencesArr(int* arr, int* occurrencesArr, int arrSize){
    bool res = true;
    for(int idx = 0; idx < arrSize && res; idx++){
        int currVal = arr[idx];
        int currValOccurrenceCount = occurrencesArr[idx];
        for(int jdx = 0; jdx < arrSize; jdx++){
            if(occurrencesArr[jdx] == currValOccurrenceCount && arr[jdx] != currVal){
                res = false;
            }
        }
    }
    return res;
}



//____________________________________________________________________________
///Forward declaration for solution2
int compareInt(const void* pIntVal1, const void* pIntVal2);
int calcNumOfDifferentVals(int* sortedArr, int arrSize); 
void fillOccurrencesOfSortedArr(int* sortedArr, int arrSize, int* occurrencesArr);
bool checkDistinctVals(int* sortedArr, int arrSize);
///Solution2: O(arrSize*log(arrSize)) time, O(arrSize) space.
bool uniqueOccurrences(int* arr, int arrSize) {
    qsort(arr, arrSize, sizeof(int), compareInt);
    int numOfDifferentVals = calcNumOfDifferentVals(arr, arrSize); 
    
    int* occurrencesArr = (int*)malloc(numOfDifferentVals * sizeof(int));
    fillOccurrencesOfSortedArr(arr, arrSize, occurrencesArr);
    
    qsort(occurrencesArr, numOfDifferentVals, sizeof(int), compareInt);
    bool res = checkDistinctVals(occurrencesArr, numOfDifferentVals);
    
    free(occurrencesArr);
    return res;
}

int calcNumOfDifferentVals(int* sortedArr, int arrSize){
    int numOfDifferentVals = 1;
    int previousVal = sortedArr[0];
    for(int idx = 1; idx < arrSize; idx++){
        if(sortedArr[idx] != previousVal){
            numOfDifferentVals++;
            previousVal = sortedArr[idx];
        }
    }
    return numOfDifferentVals;
}

void fillOccurrencesOfSortedArr(int* sortedArr, int arrSize, int* occurrencesArr){
    int occurrencesArrIdx = 0;
    int currentCount = 1;
    for(int idx = 1; idx < arrSize; idx++){
        if(sortedArr[idx] == sortedArr[idx - 1]){
            currentCount++;
        }else{
            occurrencesArr[occurrencesArrIdx] = currentCount;
            occurrencesArrIdx++;
            currentCount = 1;
        }
    }
    ///Need to update the last value, cause it's not updated in the loop
    ///since the comparison is done between sortedArr[idx] and
    /// sortedArr[idx - 1]
    occurrencesArr[occurrencesArrIdx] = currentCount;
}

bool checkDistinctVals(int* sortedArr, int arrSize){
    bool bRes = true;
    for(int idx = 1; idx < arrSize && bRes; idx++){
        bRes = (sortedArr[idx] != sortedArr[idx - 1]);
    }
    return bRes;
}


int compareInt(const void* pIntVal1, const void* pIntVal2){
    return *((int*)pIntVal1) - *((int*)pIntVal2);
}
