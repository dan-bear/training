

#include <stdlib.h>
#include <stdio.h>

void printArr(int arr[], int len)
{
    for (int idx = 0; idx < len; idx++) {
        printf("%d ", arr[idx]);
    }
    printf("\n");
}

int min(int x, int y)
{
    return (x <= y ? x : y);
}

void copyArr(int sourceArr[], int destArr[], int len){
    for (int idx = 0; idx < len; idx++){
        destArr[idx] = sourceArr[idx];
    }
}


void merge(int array1[],
           int arr1Len,
           int array2[],
           int arr2Len,
           int mergeArr[])
{
    int idx1 = 0;
    int idx2 = 0;
    int mergeIdx = 0;
    while (idx1 < arr1Len && idx2 < arr2Len) {
        if (array1[idx1] <= array2[idx2]) {
            mergeArr[mergeIdx] = array1[idx1];
            idx1++;
        } else {
            mergeArr[mergeIdx] = array2[idx2];
            idx2++;
        }
        mergeIdx++;
    }

    int* copyFrom = idx1 == arr1Len ? array2 : array1;
    int copyItr = idx1 == arr1Len ? idx2 : idx1;
    int copyTill = idx1 == arr1Len ? arr2Len : arr1Len;
    while (copyItr < copyTill) {
        mergeArr[mergeIdx] = copyFrom[copyItr];
        copyItr++;
        mergeIdx++;
    }
}

void mergeSortInterval(int array[],
                       int arrLen,
                       int intervalLen,
                       int mergeMem[])
{

    int firstRunLen = intervalLen / 2;
    int secondRunLen = min(arrLen - firstRunLen, firstRunLen);
    merge(array,
          firstRunLen,
          array + firstRunLen,
          secondRunLen,
          mergeMem);
    
    //copy the mergeMem to the array.
    copyArr(mergeMem, array, firstRunLen + secondRunLen);
}

void mergeSort(int array[], int arrLen)
{
    int arraySizeByte = sizeof(int) * arrLen;
    int* pMergeMem = (int*)malloc(arraySizeByte);

    // the interval length is a power of two and in the last
    // merge, it should be greater or equal to the array
    // length, thus the loop can stop when intervalLen
    // crosses arrLen * 2.

    for (int intervalLen = 2; intervalLen < 2 * arrLen; intervalLen *= 2) {
        for (int startIdx = 0; startIdx < arrLen; startIdx += intervalLen) {
            mergeSortInterval(array + startIdx,
                              arrLen - startIdx,
                              intervalLen,
                              pMergeMem);
        }
    }


    free(pMergeMem);
}

void printBasedTesting(int arrLen)
{
    
    int arrSizeBytes = sizeof(int) * arrLen;
    int* pArr = (int*)malloc(arrSizeBytes);
    // fill the array with arrLen - 1, arrLen - 2, ..., 0
    for (int idx = 0; idx < arrLen; idx++){
        pArr[idx] = (arrLen - 1) - idx;
    }
    printArr(pArr, arrLen);
    mergeSort(pArr, arrLen);
    printArr(pArr, arrLen);

    free(pArr);
}


int main(){
    printBasedTesting(20);
    return 0;
}
