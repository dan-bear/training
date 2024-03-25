///calculate T(n) and S(n) for f3:
int g(int n, int x){ 
    ///x is multiplied by itself at each round, let's denote
    ///the first value of x with y.
    ///loop:  0     1    2    3  .... k
    ///x   :  y^1  y^2  y^3  y^4 .... y^(k+1)
    ///So, the loop stops at iteration i, when y^(i) >= n.
    ///taking log_y to both sides: i >= log_y(n).
    ///Since, y is the inital value of x, the loop stops 
    ///after log_x(n) iterations.
    ///So, T(n) = Theta(log_x(n)).
    ///Note, x is unknown, and the question is to analyze
    ///the function f3, so for now let's work with log_x(n)
    ///and avoid converting it to Theta(log(n)). 
    ///Since the used memory is independent of n, S(n) = Theta(1).
    while(n > x){
        x*=x;
    }
    /// returning a value takes Theta(1) time and Theta(1) 
    /// space.
    return x;
    /// To sum up:
    /// T(n) = Theta(log_x(n)).
    /// S(n) = Theta(1).
}

int f3(int n){
    ///As explained above, for g, T(n) = Theta(log_x(n)),
    ///since 2 is passed as x, T(n) for f3 is Theta(log_2(n))
    /// = Theta(log(n)). The space complexity of g is Theta(1)
    /// so the space complexity for g is also Theta(1).
    
    /// Note: in case the call was g(n,n) the time complexity
    /// of f3 would be Theta(log_n(n)) = Theta(1). That's
    /// the reason T(n) for g was not written as Theta(log(n))
    /// but Theta(log_x(n)), so we do not forget it when
    /// analyzing f3 complexity.
    return g(n, 2);

    ///T(n) = Theta(log(n)).
    ///S(n) = Theta(1).
}
