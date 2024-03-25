void f2(n){ 
    int x = n;
    ///x is divided by 3 at each round of the loop.
    ///loop: 0     1      2      3       4        5
    ///x:    n -> n/3 -> n/9 -> n/27 -> x/81 -> x/243
    ///So, at round i, x = n/(3^i).
    ///When the loop ends? when x*x <= n, so we are searching
    ///for round i that satisfies (n/(3^i) * n/(3^i)) <= n
    ///(n/(3^i) * n/(3^i)) <= n ||| aggregate the left side.
    /// n^2 * (1/3)^(2*i) <= n  ||| divide by n both sides.
    /// n * (1/3)^(2*i) <= 1    ||| divide by (1/3)^(2*i) 
    /// n <= 3^(2*i)            ||| take log_3 for both sides
    /// log_3(n) <= 2*i         ||| divide by 2
    /// log_3(n) / 2 <= i 
    /// So, when i >= log_3(n) / 2, the loop stops. So the 
    /// loop take Theta(log_3(n) / 2). Since constant 
    /// multiplication and log base does not matter for 
    /// complexity analysis, the concise form is:
    /// Theta(log_3(n) / 2) = Theta(log(n)).
    /// The space complexity for this loop is independent
    /// of n, so it's Theta(1).
    /// To sum up (for this loop):
    /// T(n) = Theta(log(n)) 
    /// S(n) = Theta(1).
    while(x*x > n){
        x /= 3 ;
    }
    
    ///The loop above halts when x*x <= n, in other words 
    ///when x <= n^(1/2), so the amount of memory allocated
    ///in the next line is (approximately) n^(1/2) * sizeof(char)
    ///bytes. As constant multiplication does not matter from
    ///complexity point of view, the amount of allocated
    ///space is in Theta(n^(1/2)).
    ///The time complexity of malloc is O(1) (in this course).
    ///To sum up:
    ///T(n) = Theta(1)
    ///S(n) = Theta(n^(1/2)) (i.e square root of n). 
    char* s = (char*)malloc(sizeof(char) * x);
    if(s==NULL){
        printf("error\n");
    }    
    else{
        printf("well done %d\n", n);
    }

    ///T(n) = Theta(log(n)) + Theta(1) = Theta(log(n)).
    ///S(n) = Theta(1) + Theta(n^(1/2)) = Theta(n^(1/2)).
}
