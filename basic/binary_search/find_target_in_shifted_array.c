int findIdxOfSmallestElem(int* arr, int len);
int binarySearch(int* arr, int len, int target);
int max(int x0, int x1);

int findTargetInShiftedArr(int* arr, int len, int target)
{
    int idxOfSmallestElement = findIdxOfSmallestElem(arr, len);

    int firstSubArrLen = idxOfSmallestElement;
    int secondSubArrStartIdx = idxOfSmallestElement;
    int secondSubArrLen = len - firstSubArrLen;
    // Assume binarySearch returns -1 if the target does not
    // appear in the array.
    int targetIdxInFirstSubArr = binarySearch(arr, firstSubArrLen, target);
    int targetIdxInSecondSubArr = binarySearch(
      arr + secondSubArrStartIdx, secondSubArrLen, target);
    // Note, second sub array starts from secondSubArrStartIdx
    // so it needs to be shifted as the binary search
    // returns the index relative to its start index:
    if(targetIdxInSecondSubArr >= 0){
        targetIdxInSecondSubArr += secondSubArrStartIdx;
    }
    
    int res = max(targetIdxInFirstSubArr, targetIdxInSecondSubArr);
    return res;
}

int findIdxOfSmallestElem(int* arr, int len)
{
    int res = -1;
    int leftIdx = 0;
    int rightIdx = len - 1;
    while (leftIdx < rightIdx) {
        int midIdx = (leftIdx + rightIdx) / 2;
        if (arr[midIdx] > arr[rightIdx]) {
            leftIdx = midIdx + 1;
        } else { // arr[midIdx] < arr[rightIdx]
            // It's possible that midIdx is the index of the
            // smallest value, thus rightIdx = midIdx and not
            // midIdx - 1 like in binary search.
            rightIdx = midIdx;
        }
    }
    // Here leftIdx == rightIdx and that's where the smallest
    // value should be.
    res = leftIdx;
    return res;
}

int binarySearch(int* arr, int len, int target)
{
    int resTargetIdx = -1;
    int leftIdx = 0;
    int rightIdx = len - 1;
    while (leftIdx <= rightIdx) {
        int midIdx = (leftIdx + rightIdx) / 2;
        if (arr[midIdx] == target) {
            resTargetIdx = midIdx;
            break;
        } else {
            if (arr[midIdx] < target) {
                leftIdx = midIdx + 1;
            } else {
                rightIdx = midIdx - 1;
            }
        }
    }
    return resTargetIdx;
}

int max(int x1, int x2)
{
    return x1 > x2 ? x1 : x2;
}

// Here there is a simple print based test.
// #include <stdio.h>
// int main()
// {
//     int arrays[4][4] = {
//         { 1, 2, 3, 4 }, { 4, 1, 2, 3 }, { 3, 4, 1, 2 }, { 2, 3, 4, 1 }
//     };

//     int targets[] = { 0, 1, 2, 3, 4, 5 };
//     /// Test by printing.
//     for (int arrIdx = 0; arrIdx < 4; arrIdx++) {
//         for (int targetIdx = 0; targetIdx < 6; targetIdx++) {
//             printf("targetVal = %d , targetIdx = %d\n",
//                    targets[targetIdx],
//                    findTargetInShiftedArr(
//                      arrays[arrIdx], 4, targets[targetIdx]));
//         }
//         printf("\n");
//     }

//     return 0;
// }
