/**
 * https://leetcode.com/problems/powx-n/
 * #recursion #log(n)
 */
class Solution {
public:
    double myPow(double x, int n) {
        ///need to cast, since if n = -2^31, 2^32 cannot be represented in
        ///int, the value of  -1 * n cannot be stored (intermidiately)
        ///thuse the coversion is done before the sign check.
        long long wideN = static_cast<long long>(n);
        unsigned long long absN = n >= 0 ? 
                static_cast<unsigned long long>(wideN) :
                static_cast<unsigned long long>(-1 * wideN);
        double res = myPowAux(x, absN);
        res = n >= 0 ? res : 1 / res;
        return res;
    }
private:
    double myPowAux(double x, unsigned long long n){
        if(n == 0){
            return 1;
        }else if(n % 2){
            return x * myPowAux(x, n - 1);
        }else{
            double res = myPowAux(x, n / 2);
            return res * res;
        }
    }
};
