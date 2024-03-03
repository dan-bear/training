/**
 * https://leetcode.com/problems/greatest-common-divisor-of-strings/
 * #String #STRING #string #STR #str #GCD #gcd #concat #CONCAT
 * Method: concat two strings.
 */
class Solution {
public:
    ///
    ///str1 and str2 has a common gcd <=> str1 + str2 = str2 + str1.
    /// => : is straight forward.
    /// <= : str1 is repeatable by a substring of str1.
    ///      that' always true since str1 is a substring of itself.
    ///      and repeatig str1 once gives us str1.
    ///      Let's call repS1 the shortest substrig such that
    ///      repS1^k = str1. So, str1 + str2 = repS1^k + str2
    ///      and str2 + str1 = str2 + repS1^k. Now, the same
    ///      claim holds for str2, so str2 = repS2^m and
    ///      repS2^m + repS1^k = repS1^k + repS2^m.
    ///      If repS1 != repS2 the above equality cannot hold
    ///      thus, repS1 = repS2 and it means str1 and str2 has
    ///      a gcd.
    ///
    ///How to find the gcd?
    ///assume str1.length() >= str2.length().
    ///gcd.length() divides str1.length().
    ///gcd.length() divides str2.legth().
    ///So in practie the gcd of str1.length() and str2.length()
    ///is the length of the str1 and str2 gcd. That's the reason
    ///this question is called gcd of strings.   
    
    string gcdOfStrings(string str1, string str2) {
        string res;
        if(str1 + str2 == str2 + str1){
            int gcd = findGcd(str1.length(), str2.length());
            res = str1.substr(0, gcd);
        }
        return res;
    }
private:
    int findGcd(int x0, int x1){
        ///return std::gcd(x0, x1);
        ///Wanted to remind myself the gcd algorithm.
        if(x0 < x1){
            swap<int>(x0, x1);
        }
        /// x1 >= x0
        /// r_-2 = x1.
        /// r_-1 = x0
        /// r_-2 = r_-1 * q0 + r0
        /// r_-1 = r0 * q1 + r1
        /// r0 = r1 * q2 + r2
        /// r1 = r2 * q3 + r3
        /// ...
        /// r_n-2 = r_n-1 * qn + rn.
        /// If rn == 0, it means r_n-1 is the gcd.
        int currentReminder = x0;
        int previousReminder = x1;
        while(currentReminder != 0){
            int reminder = previousReminder % currentReminder;
            previousReminder = currentReminder;
            currentReminder = reminder;
        }
        return previousReminder;
    }

    template<typename T>
    void swap(T& x0, T& x1){
        T temp = x0;
        x0 = x1;
        x1 = temp;
    }
};
