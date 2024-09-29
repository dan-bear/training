/**
 * https://leetcode.com/problems/roman-to-integer/
 */
class Solution {
public:
    static const std::unordered_map<char, int> romanToIntVal;

    int romanToInt(string s) {
        //return romanToIntFirstApproach(s);
        return romanToIntSecondApproach(s);
    }

private:
    //first approach:
    int romanToIntFirstApproach(string s) {
        int intFormat = 0;
        for(int charIdx = 0; charIdx < s.size(); charIdx++){
            int val = calcValue(s, charIdx);
            if(val != romanToIntVal.at(s[charIdx])){
                charIdx++;
            }
            intFormat += val;
        }
        return intFormat;
    }
    
    int calcValue(string s, int charIdx){
        char let = s[charIdx];
        if(charIdx < s.size() - 1){
            char nextLet = s[charIdx + 1];
            int div = romanToIntVal.at(nextLet) / romanToIntVal.at(let);
            // means a 4.. or 9.. state was reached, for example XV, or XC 
            // V / X = 5 and C/X = 10
            if(div == 5 || div == 10){
                return romanToIntVal.at(nextLet) - romanToIntVal.at(let);
            }
        }
        return romanToIntVal.at(let);
    }

    int romanToIntSecondApproach(string s){
        int intFormat = 0;
        int prevVal = 0;
        for(char c : s){
            int currVal = romanToIntVal.at(c);
            if(prevVal < currVal){
                // 4.. or 9.. case - for example XC or XL ,we added 10 in the
                // previous iteration but should have added 40 or 90, so to 
                // fix it one needs to add 30 or 80, i.e. 50 - 2*10 or 100 * 2*10
                intFormat += (romanToIntVal.at(c) - 2*prevVal);
            }else{
                intFormat += romanToIntVal.at(c);
            }
            prevVal = currVal;
        }
        return intFormat;
    }
};

const std::unordered_map<char, int> Solution::romanToIntVal = {
    {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
    {'C', 100}, {'D', 500}, {'M', 1000}};
    
