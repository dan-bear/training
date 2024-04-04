/**
 * Implement a binary search using recursion.
 * the function signature:
 * int binarySearch(int* arr, int len, int target)
 * where:
 * 1: arr - is a sorted array of integers.
 * 2: len - the array's length.
 * 3: target - the value to find.
 * 4: The function returns an index where target appears 
 *    or -1 if target does not exist in the given array. 
 *
 * Complexity constraints:
 * Time complexity: O(log(len))
 * Space complexity: O(log(len))
 * 
 * You may implement auxilary functions, as long as the 
 * main logic is recursive.
 * 
 */
///SOLUTION
int recursiveBinarySearch(int* arr, int startIdx, int endIdx, int target);
int binarySearch(int* arr, int len, int target){
    return recursiveBinarySearch(arr, 0, len - 1, target);
}

int recursiveBinarySearch(int* arr,
                          int startIdx,
                          int endIdx,
                          int target){
    if(startIdx > endIdx){
        return -1;
    }
    int midIdx = (startIdx + endIdx) / 2;
    if(arr[midIdx] == target){
        return midIdx;
    }
    if(arr[midIdx] < target){
        ///need to search the right part.
        return recursiveBinarySearch(arr, midIdx + 1, endIdx, target);
    }
    ///need to search to left part.
    return recursiveBinarySearch(arr, startIdx, midIdx - 1, target);
}
