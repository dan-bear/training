/**
 * Find two element in an array that sum up to target and
 * write their indexes in the result array.
 * 
 * @param array an array with integers.
 * @param arrayLen the length of the array.
 * @param target the target value.
 * @param resultOut an array of size 2 used as an output
 * parameter to save the indexes of the elements.
 * 
 * Example:
 * array = {1, 3, 2, 4}
 * target = 5
 * So {0, 3} or {1, 2} should be the content of resultOut
 * since array[0] + array[3] == array[1] + array[2] == 5. 
 * It does not matter which pair is saved in the resultOut
 * array.
 * 
 * @note if there are no two elements that sums up to target
 * the content of resultOut should not be changed.
 */
void twoSum(int array[], int arrayLen, int target, int resultOut[2])
{
    int lastIdx = arrayLen - 1;
    for (int firstIdx = 0; firstIdx < lastIdx; firstIdx++) {
        for (int secondIdx = firstIdx + 1; secondIdx < lastIdx; secondIdx++) {
            if (array[firstIdx] + array[secondIdx] == target) {
                resultOut[0] = firstIdx;
                resultOut[1] = secondIdx;
                break;
            }
        }
    }
}
