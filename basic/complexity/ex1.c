void f1(n){ 
    int x = n*n;
    int counter = 0;
    ///This loop runs (log_2(x) + 1) times since x is divided by
    ///2 at each loop. For example: x = 16
    ///loop1: x = 16
    ///loop2: x = 8
    ///loop3: x = 4
    ///loop4: x = 2
    ///loop5: x = 1
    ///next time x = 0 and the loop stops.
    ///So, the time complexity of this loop is Theta(log_2(x)).
    ///Since x is n^2, the time complexity of this loop is
    ///Theta(log_2(n^2)) and since log_2(n*n) = log_2(n) + log_2(n)
    ///log_2(n^2) = 2*log_2(n) and 2*log_2(n) is in Theta(log_2(n))
    ///as the constant does not matter. Thus, the time complexity
    ///of this loop as a fuction of n is Theta(log_2(n)).
    ///Note, the base of the log does not matter, since one
    ///can move from base to base by multiplying with a 
    ///constant: for every a,c,n > 0: 
    ///log_a(n) = log_c(n) / log_c(a).
    ///Thus, the concise way to write the time complexity is
    ///Theta(log(n)).
    ///For the space complexity, the space needed is independent
    ///of the value of x, so the space complexity of the loop
    ///is Theta(1).
    ///To sum up (for this loop):
    ///Time(n) = Theta(log(n))
    ///Space(n) = Theta(1)
    while(x > 0){
        x /= 2;
        counter++;
    }
    ///Since counter start from zero, and the loop runs
    ///log_2(x) times, the value of counter is log_2(x).
    ///So, the next loop that decreases the counter by 1
    ///at each step stops after log_2(x) times. So, its time
    ///complexity is Theta(log_2(x)) times. It was 
    ///explained above that Theta(log_2(x)) = Theta(log(n)).
    ///For the space complexity, the space needed is independent
    ///of the value of counter, so the space complexity of
    ///the loop is Theta(1).
    while (counter > 0){
        counter--;
    }

    ///There were two loops, each onn took Theta(log(n)) 
    ///time, since 2 * log(n) is in Theta(log(n)) the 
    ///time complexity of all the function is Theta(log(n)).
    ///The space complexity of each loop is Theta(1) so
    ///the space complexity of the function is Theta(1)/

    ///Solution:
    ///T(n) = Theta(n)
    ///S(n) = Theta(1) 
}
