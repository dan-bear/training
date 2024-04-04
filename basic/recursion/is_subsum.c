
/**
 * Implement the function:
 * bool isSubsum(int* arr, int len, int target) 
 * 1: arr - an array with integers.
 * 2: len - the length of the array.
 * 3: target - a target value.
 * The function returns true if there is a sub-set of the
 * array's element such that it sums up to target and false
 * otherwise.
 * Example:
 * arr = {1,2,-1,-1,3}
 * target = 0 => the return value is true, since {2, -1, -1} 
 *               sum is 0.
 * target = 5 => the return value is true, since {2, 3} sum
 *               is 0.
 * target = 7 => the return value is false, since no subset
 *               of elements in the array that is summed to 
 *               7.
 * Complexity constraints:
 * Time(len) = O(2^len)
 * Space(len) = O(len)
 */
///Solution:
bool isSubsum(int* arr, int len, int target){
    if(target == 0){
        return true;
    }
    if(len == 0){
        return false;
    }
    ///use the current number
    if(isSubsum(arr + 1, len - 1, target - arr[0])){
        return true;
    }
    ///cannot make it with current number, let's try
    ///without it.
    return isSubsum(arr + 1, len - 1, target);
}
