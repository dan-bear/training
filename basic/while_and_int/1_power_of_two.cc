/**
 * The function gets an integer (negative or positive) and
 * returns whether its a power of 2 or not.
 * https://leetcode.com/problems/power-of-two
 */
bool isPowerOfTwo(int n) {
    bool bRes = true;
    if(n == 1){
        bRes = true;
    }else if(n <= 0){
        bRes = false;
    }else{
        while(n > 1 && bRes){
            if(n % 2 != 0){
                bRes = false;
            }
            n /= 2;
        }
    }
    return bRes;
}
