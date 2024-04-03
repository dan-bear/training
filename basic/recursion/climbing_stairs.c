/**
 * https://leetcode.com/problems/climbing-stairs/
 */
///SOLUTION:
int climbStairs(int n) {
    if(n == 1){
        return 1;///one way to reach the top.
    }
    if(n == 2){
        return 2; ///climb 2 steps, or climb 1 step twice.
    }
    return climbStairs(n - 1) + climbStairs(n - 2);
}
