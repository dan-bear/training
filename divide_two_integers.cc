// https://leetcode.com/problems/divide-two-integers/
//
// current problem: I did not deal with the integer overflow.
//
// Derived exercises:
// A: implement absolute value without mult.
// B: implement modulo.
// C: implement mult.
//
// 1: no multi
// 2: no division
// 3: no mod
// 4: truncate toward zero: positive values => smaller, negative values => bigger
// 5: the quotient after dividing the dividend by the divisor.
// 6: divisor != 0
// 7: dividend is 10 and divisor is 3 => output is 3.
// 8: dividend is -10 and divisor is 3 => output -3.
// 9: dividend is -10 and divisor is -3 => output is 3
// 10: dividend is 10 and devisor is -3 => output -3. 
//
// second idea, implement integer multiplication using + and -.
class Solution {
public:
    int divide(int dividend, int divisor) {
        int absDivisor = absValue(divisor);
        int absDividend = absValue(dividend);
        int quotient = 0;
        int currentValue = 0;
        while(currentValue < absDividend){
            currentValue += absDivisor;
            quotient += 1;
        }
        if(currentValue > absDividend){
            quotient -= 1;
        }
        int dividendSign = dividend > 0 ? 1 : -1;
        int divisorSign = divisor > 0 ? 1 : -1;
        if(divisorSign != dividendSign){
            // flip sign
            quotient = 0 - quotient;
        }

        return quotient;
    }
private:

    int absValue(int val){
        int res = val > 0 ? val : 0 - val;
        return res;
    }

    // pos, pos: 3, 4
    // 0 + 3 + 3 + 3 + 3
    // neg, pos: -3, 4
    // 0 + -3 + -3 + -3 + -3
    // pos, neg: 3, -4
    // 0 + -4 + -4 + -4
    // neg, neg: -3, -4
    // how to take an absolute value of a negative number?
    // 0 - (number)
    // take the abs of both,
    // run the positive positive case
    // 0 - (-3) - (-3) - (-3) -(-3)
    int mult(int val1, int val2){
        if(val1 == 0 || val2 == 0){
            return 0;
        }
        // both negative.
        if(val1 < 0 && val2 < 0){
            val1 = 0 - val1;
            val2 = 0 - val2;
        }
        int numOfAddIters = 0;
        int addedValue = 0; 
        if (val1 > 0){
            numOfAddIters = val1;
            addedValue = val2;
        }else{
            numOfAddIters = val2;
            addedValue = val1;
        }
        int res = 0;
        for(int idx = 0; idx < numOfAddIters; idx++){
            res += addedValue;
        }
        return res;      
    }
};
