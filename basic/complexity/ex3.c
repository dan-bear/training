///calculate T(n) and S(n) for f3:
int g(int n, int x){ 
    ///x is multiplied by itself at each round, let's denote
    ///the first value of x with y.
    ///loop:  0     1    2    3  .... k
    ///x   :  y^1  y^2  y^4  y^8 .... y^(2^k)
    ///So, the loop stops at iteration i, when y^(2^i) >= n.
    ///taking log_y to both sides: 2^i >= log_y(n).
    ///taking log_2 to both sides: i >= log_2(log_y(n))
    ///Since, y is the inital value of x, the loop stops 
    ///after log_2(log_x(n)) iterations.
    ///So, T(n,x) = Theta(log_2(log_x(n))) = Theta(log(log_x(n)).
    ///Note, x is unknown that's why we calculate the time complexity
    ///as a function of n and x and not just a function of n.
    ///Since the used memory is independent of n and x, S(n, x) = Theta(1).
    while(n > x){
        x*=x;
    }
    /// returning a value takes Theta(1) time and Theta(1) 
    /// space.
    return x;
    /// To sum up:
    /// T(n, x) = Theta(log(log_x(n))).
    /// S(n, x) = Theta(1).
}

int f3(int n){
    ///As explained above, for g, T(n, x) = Theta(log(log_x(n))),
    ///since 2 is passed as x, T(n) for f3 is Theta(log(log_2(n)))
    /// = Theta(log(log(n))). The space complexity of g is Theta(1)
    /// so the space complexity for f3 is also Theta(1).
    
    /// Note: in case the call was g(n,n) the time complexity
    /// of f3 would be Theta(log(log_n(n))) = Theta(log(1)) = Theta(0)
    /// == Theta(1) That's the reason T(n, x) was calculated for g 
    /// and not just T(n).
    return g(n, 2);

    ///T(n) = Theta(log(log(n))).
    ///S(n) = Theta(1).
}
