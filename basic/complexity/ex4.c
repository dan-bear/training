/// Analyze T(n) and S(n) for f4:
int g(int n, int x)
{
    int k = x;
    /// loop: 0   1    2    3    4    ... i
    /// k   : x  x^2  x^4  x^8  x^16  ... x^(2^i)
    /// So, the loop halts when x^(2^i) >= n
    /// taking log_x for both sides: 2^i >= log_x(n)
    /// taking log_2 for both sides i >= log_2(log_x(n)).
    /// Thus, T(n, x) = Theta(log_2(log_x(n))) = Theta(log(log_x(n))).
    /// The space complexity is Theta(1) since the memory
    /// used is independent of n and x.
    while (n > k) {
        k *= k;
    }
    ///Since k is multiplied by itself each round, when
    ///k reaches the range [n^(1/2), n-1], multiplying k by
    ///itself gives a value in the range [n, (n-1)^2], so 
    ///the returned value is somewhere in this range, one
    ///might need to relate to it when analyzing f4.
    return k;

    ///To sup up g complexity:
    ///T(n, x) = Theta(log(log_x(n)))
    ///S(n, x) = Theta(1)
    ///And the return value is in the range [n, (n-1)^2].
}

int
f4(int n)
{
    ///2 is passed as x, so the time complexity for running
    ///g is: T(n) = Theta(log(log_2(n))) = Theta(log(log(n)))
    ///and the memory needed is S(n) = Theta(1).
    int x = g(n, 2);
    
    ///As explained above x, value is somewhere in the range:
    ///[n, (n-1)^2].
    ///x is divided by 2 at each iteration, so the while
    ///loop take log_2(x) iterations till it's over:
    ///loop: 1   2    3      4    ..... i
    ///x:    x  x/2  x/2^2  x/2^3      x/2^(i-1).
    ///The loop halts when x/2^(i-1) <= 0.
    ///Thus, when i = log_2(x) + 1 x /2^(i-1) = 1 and the
    ///in the next iteration 1 / 2 = 0, so the loop halts.
    ///Since x is in the range [n, (n-1)^2] the time 
    ///complexity of the loop is in the range:
    ///[log_2(n), log_2((n-1)^2)]. log_2((n-1)^2) = 2*log_2(n-1), 
    ///so from the complexity point of view it for any x
    ///the range [n, (n-1)^2], the number of iterations is
    ///in Theta(log(n)).
    ///The memory needed is independent of n and x so,
    ///S(n) = Theta(1).
    while (x > 0) {
        x /= 2;
    }
    return x;

    ///Sum up:
    ///T(n) = Theta(log(log(n))) + Theta(log(n)) = Theta(log(n)).
    ///S(n) = Theta(1) + Theta(1) = Theta(1).
}
