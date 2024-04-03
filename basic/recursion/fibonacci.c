
/**
 * The Fibonacci sequence is:
 * a[0] = 0
 * a[1] = 1
 * a[2] = a[0] + a[1] = 2
 * a[3] = a[1] + a[2] = 3
 * a[4] = a[2] + a[3] = 5
 * a[5] = a[3] + a[4] = 8
 * ...
 * a[n] = a[n - 1] + a[n - 2]
 * 
 * Implement the function int fibo(int n) where:
 * 1: n is an index of element in Fibonacci sequence.
 * 2: The function returns the value of a[n] in the
 *    Fibonacci sequence.
 * 
 * 1: The solution need to be recursive.
 * 2: You can implement helper functions.
 */

int fibo(int n){
    if(n == 0){
        return 0;
    }
    if(n == 1){
        return 1;
    }
    return fibo(n - 1) + fibo(n - 2);
}
