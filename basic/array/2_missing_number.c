/**
 * https://leetcode.com/problems/missing-number
 * Please visit the leet-code link above to see the question
 * description and examples.
 *
 * The function to implement:
 * int missingNumber(int nums[], int numsSize) 
 * when nums is an array of integers and numsSize is the array
 * length.
 */

//forward declaration.
int calcArithmeticSeriesSum(int firstElement, int numOfElements, int difference);
int sumArray(int array[], int len);

int missingNumber(int nums[], int numsSize) {
    int completeSum =  calcArithmeticSeriesSum(1, numsSize, 1);
    int missingSum = sumArray(nums, numsSize);
    int missing = completeSum - missingSum;
    return missing;
}

int calcArithmeticSeriesSum(int firstElement, int numOfElements, int difference){
    int lastElement = firstElement + (numOfElements - 1) * difference;
    int pairSum = firstElement + lastElement;
    // Note the casting.
    int sum = (int)(pairSum * ((double)numOfElements / 2.0));
    return sum;
}

int sumArray(int nums[], int numsLen){
    int sum = 0;
    for(int idx = 0; idx < numsLen; idx++){
        sum += nums[idx];
    }
    return sum;
}
