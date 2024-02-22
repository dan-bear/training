/**
 * Given two sorted arrays and its lengthes, merge them 
 * into a thired array (mergeArr) such that the merge
 * result is also sorted but contains all the elements
 * both from array1 and array2.
 *
 * Note: assume the mergeArr length is arr1Len + arr2Len 
 * thus, it's not given as a parameter.
 */
void mergeSortedArrays(int array1[],
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

    if (idx1 == arr1Len) {
        // keep copying from array2
        while (idx2 < arr2Len) {
            mergeArr[mergeIdx] = array2[idx2];
            idx2++;
            mergeIdx++;
        }
    } else {
        // keep copying from array1
        while (idx1 < arr1Len) {
            mergeArr[mergeIdx] = array1[idx1];
            idx1++;
            mergeIdx++;
        }
    }

    //Node: do we actually need the if else above? i.e.
    //      can we replace lines 30 to 44 with:
    // while (idx1 < arr1Len) {
    //     mergeArr[mergeIdx] = array1[idx1];
    //     idx1++;
    //     mergeIdx++;
    // }
    // while (idx2 < arr2Len) {
    //     mergeArr[mergeIdx] = array2[idx2];
    //     idx2++;
    //     mergeIdx++;
    // }
    // The answer is yes, but make sure you understand why!

           
    // Note: a cleaner version for the tail part when
    // pointers are already tought.
    // int* copyFrom = idx1 == arr1Len ? array2 : array1;
    // int copyIdx = idx1 == arr1Len ? idx2 : idx1;
    // int copyTill = idx1 == arr1Len ? arr2Len : arr1Len;
    // while(copyItr < copyTill){
    //     mergeArr[mergeIdx] = copyFrom[copyIdx];
    //     copyIdx++;
    //     mergeIdx++;
    // }
}
