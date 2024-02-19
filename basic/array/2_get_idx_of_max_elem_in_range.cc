/**
 * The function gets an array and two indexes firstIdx, secondIdx 
 * and returns an INDEX of the maximal value in the
 * sub array {array[firstIdx] ... array[secondIdx]}.
 * @note:
 *  1: Assumption: firstIdx <= secondIdx.
 *  2: Assumption: 0 <= firstIdx and secondIdx < array length.
 *  3: If there are several elements with maximal value,
 *     it does not matter which of their indexes is returned.
 *     For example, arr = {1, 3, 5, 2, 5, 0} and the function
 *     is called with firstIdx = 1, secondIdx 5, the function
 *     can return either 2 or 4 (since array[2] == array[4] = 5
 *     which is the maximal value).
 * 4: The range is inclusive, i.e. we are interested in all the
 *    element in range [firstIdx, secondIdx].
 */

int findIdxOfMaxElemInRange(int array[], int firstIdx, int secondIdx){
    int maxElem = array[firstIdx];
    int idxOfMaxElem = firstIdx;
    for(int idx = firstIdx; idx <= secondIdx; idx++){
        if(array[idx] > maxElem){
            maxElem = array[idx];
            idxOfMaxElem = idx;
        }
    }
    return idxOfMaxElem;

}
