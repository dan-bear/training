/**
 * https://leetcode.com/problems/integer-to-roman/
 */
class Solution {
public:
    string intToRoman(int num) {
        //return sol1(num);
        //return sol2(num);
        return sol3(num);    
    }
    
private:
    string sol3(int num){
        vector<std::pair<int, string>> buildingBlocks = 
            {{1000, "M"},
             {900, "CM"},
             {500, "D"},
             {400, "CD"},
             {100, "C"},
             {90, "XC"},
             {50, "L"},
             {40, "XL"},
             {10, "X"},
             {9, "IX"},
             {5, "V"},
             {4, "IV"},
             {1, "I"}};
        string romanFormat;
        int idx = 0;
        while(idx < buildingBlocks.size()){
            if(num >= buildingBlocks[idx].first){
                romanFormat.append(buildingBlocks[idx].second);
                num -= buildingBlocks[idx].first;
            }else{
                idx++;
            }
        }
        return romanFormat;
    }


    string sol2(int num){
        vector<string> ones = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
        vector<string> tens = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
        vector<string> hundreds = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
        
        return string(num / 1000, 'M') + 
            hundreds[(num % 1000) / 100] + 
            tens[(num % 100) / 10] + 
            ones[num % 10];
    }


    string sol1(int num) {
        string romanFormat;
        if(num >= 1000){
            int numOfMs = num / 1000;
            romanFormat.append(string(numOfMs,'M'));
            num %= 1000;

        }

        if(num >= 500){
            if(num >= 900){
                romanFormat.append("CM");
                num -= 900;
            }else{
                romanFormat.append("D");
                num -= 500;
            }
        }
        
        if(num >= 100){
            if(num >= 400){
                romanFormat.append("CD");
                num -= 400;
            }else{
                romanFormat.append(string(num / 100, 'C'));
                num %= 100;
            }
        }

        if(num >= 50){
            if(num >= 90){
                romanFormat.append("XC");
                num -= 90;
            }else{
                romanFormat.append("L");
                num -= 50;
            }
        }
        
        if(num >= 10){
            if(num >= 40){
                romanFormat.append("XL");
                num -= 40;
            }else{
                romanFormat.append(string(num / 10, 'X'));
                num %= 10;
            }
        }

        if(num >= 5){
            if(num >= 9){
                romanFormat.append("IX");
                num -= 9;
            }else{
                romanFormat.append("V");
                num -= 5;
            }
        }
        
        if(num >= 4){
            romanFormat.append("IV");
        }else{
            romanFormat.append(string(num, 'I'));
        }
        return romanFormat;
    }
};
