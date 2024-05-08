/**
 * https://leetcode.com/problems/n-th-tribonacci-number
 */
///SOLUTION
void shiftLeft(int* arr, int arrSize);
int sumArray(int* arr, int arrSize);
int tribonacci(int n){
    if(n == 0){
        return 0;
    }else if(n == 1 || n == 2){
        return 1;
    }else{
        int lastThree[] = {0, 1, 1};
        int lastThreeSize = 3;
        int threeSum = 0;
        for(int idx = lastThreeSize; idx <= n; idx++){
            threeSum = sumArray(lastThree, lastThreeSize);
            shiftLeft(lastThree, lastThreeSize);
            lastThree[lastThreeSize - 1] = threeSum;
        }
        return threeSum;
    }
}

int sumArray(int* arr, int arrSize){
    int sum = 0;
    for(int idx = 0; idx < arrSize; idx++){
        sum += arr[idx];
    }
    return sum;
}

void shiftLeft(int* arr, int arrSize){
    for(int idx = 0; idx < arrSize - 1; idx++){
        arr[idx] = arr[idx + 1];
    }
}
