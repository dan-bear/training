/**
 * https://leetcode.com/problems/sqrtx/
 * #binary_search
 */
 int mySqrt(int x) {
    long long first = 0;
    long long last = x;
    while(first <= last){
        long long middle = (last + first) / 2;
        long long squareMiddle = middle * middle;
        if(squareMiddle > x){
            last = middle - 1;
        }else if(squareMiddle < x){
            first = middle + 1;
        }else{
            return (int)middle;
        }
    }
    // x = 8:
    // first = 0, last = 8, mid = 4
    // first = 0, last = 3, mid = 1
    // first = 2, last = 3, mid = 3
    // first = 3, last = 3, mid = 3
    // first = 3, last = 2
    return (int)last;
}
