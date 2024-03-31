/**
 * Implement the function int power(int x, unsigned int n)
 * that calculates the power of x raised by n (x^n).
 * Use recursion and do in in Theta(log(n)) Space and Time complexity.
 */
///Solution:
int power(int x, unsigned int n){
    if(n == 0){
        return 1;
    }else if(n % 2 == 1){
        return x * power(x, n - 1);
    }else{ ///n % 2 == 0
        int res = power(x, n / 2);
        return res * res;
    }
}
