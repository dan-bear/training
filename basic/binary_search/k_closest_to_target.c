int searchInsertPlace(int* sortedNums, int numsLen, int target);

int k_closest_to_target(int arr[], int n, int target, int k){
    int insertIdx = searchInsertPlace(arr, n, target);
    int res = -1;
    
    ///code without details:
    // if(arr[insertIdx] == target){
    //     if(insertIdx >= (k - 1)){
    //         res = arr[insertIdx - (k - 1)];
    //     }else{
    //         res = arr[insertIdx + (k - 1)];
    //     }
    // }else{
    //     if(insertIdx == 0 || insertIdx < k){
    //         res = arr[insertIdx + (k - 1)];
    //     }else{
    //         res = arr[insertIdx - k];
    //     }
    // }
    // return res;

    ///code with details:
    if(arr[insertIdx] == target){
        if(insertIdx >= k - 1){
            ///There is a k-closest to its left.
            ///@note the question defines 1-closest as the
            ///closest number. So, if array is [10, 12, 14],
            ///k = 2 and target = 14, 12 should be returned.
            ///12's index is 1, 14's index is 2, that's why
            ///the if checks k - 1 and not k.
            res = arr[insertIdx - (k - 1)];
        }else{
            ///It's guaranteed there is a k closest, so the
            ///right side is checked.
            res = arr[insertIdx + (k - 1)];
        }
    }else{
        /// If target is not in the array the calculation
        /// is a little different, let's have a look in the
        /// next example:
        /// [10, 12, 14, 16]
        /// target = 9 => insert index = 0,
        ///            1 closest is 10 stored in index 0 (insertIdx + (k - 1)).
        ///            2 closest is 12 stored in index 1 (insertIdx + (k - 1))
        ///            3 closest is 14 stored in index 2 (insertIdx + (k - 1)).
        ///            4 closest is 16 stored in index 3 (insertIdx + (k - 1)).
        /// target = 11 => insert index = 1.
        ///             1 closest is 10 stored in index 0 (insertIdx - k).
        ///             2 closest is 14 stored in index 2 (insertIdx + (k - 1)).
        ///             3 closest is 16 stored in index 3 (insertIdx + (k - 1)).
        /// target = 13 => insert index = 2
        ///             1 closest is 12 stored in index 1 (insertIdx - k).
        ///             2 closest is 10 stored in index 0 (insertIdx - k).
        /// target = 15 => insert index = 3
        ///             1 closest is 14 stored in index 2 (insertIdx - k).
        ///             2 closest is 12 stored in index 1 (insertIdx - k)
        ///             3 closest is 10 stored in index 0 (insertIdx - k).
        /// target = 17 => insert index = 4,
        ///             1 closest is 16 stored in index 3 (insertIdx - k).
        ///             2 closest is 14 stored in index 2 (insertIdx - k)
        ///             3 closest is 12 stored in index 1 (insertIdx - k).
        ///             4 closest is 12 stored in index 0 (insertIdx - k).
        ///
        ///So, there is an edge case when insertIdx == 0 and
        ///when the k closest is right to the target.
        if(insertIdx == 0 || insertIdx < k){
            res = arr[insertIdx + (k - 1)];
        }else{
            res = arr[insertIdx - k];
        }
    }
    return res;
}

/**
 * The function finds where target should be inserted in 
 * a sorted array of nums so the array stays sorted after
 * the insertion.
 * @param sortedNums an array of sorted nums.
 * @param numsLen the length of the sorted nums array.
 * @param target the value that its insert position should
 * be calculated.
 * @return the index (position) where the target should be
 * inserted to.
 * Example:
 * sorted array = [0, 2, 4]
 * - target = -1 => its insert place is 0 ([-1, 0, 2, 4]).
 * - target = 0 => its insert place can be 0 or 1
 *   ([0, 0, 2, 4]), this implementation returns 0.
 * - target = 1 => its insert place is 1 ([0, 1, 2, 4]).
 * - target = 2 => its insert place can be 1 or 2 
 *   ([0, 2, 2, 4]), this implementation returns 1.
 * - target = 3 => its insert place is 2 ([0, 2, 3, 4]).
 * - target = 4 => its insert place can be 2 or 3 
 *   ([0, 2, 4, 4]), this implementation returns 2.
 * - target = 5 => its insert place is 4 ([0, 2, 4, 5]).
 * @note the function space complexity is O(log(numsLen)) 
 * since it's just a small modification of binary search.
 */
int searchInsertPlace(int* sortedNums, int numsLen, int target) {
    ///Note: this solution just modifies the binary search
    ///return value in case target is not in the list.
    int leftIdx = 0;
    int rightIdx = numsLen - 1;
    while (leftIdx <= rightIdx) {
        int midIdx = (leftIdx + rightIdx) / 2;
        if (sortedNums[midIdx] == target) {
            return midIdx;
        } else {
            if (sortedNums[midIdx] < target) {
                leftIdx = midIdx + 1;
            } else {
                rightIdx = midIdx - 1;
            }
        }
    }
    return rightIdx + 1;
}
