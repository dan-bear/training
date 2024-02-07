/**
 * #https://leetcode.com/problems/letter-combinations-of-a-phone-number/
 * #BT #backtracking
 */

class Solution {
public:
    
    vector<string> letterCombinations(string digits) {
        
        vector<string> res;
        
        if(digits.length() != 0){
            string currentStr;
            letterCombinationAux(digits, currentStr, res);    
        }
        
        return res;
    }

private:
    void letterCombinationAux(string digits, string currentStr ,vector<string>& resOut){
        if(digits.length() == 0){
            resOut.push_back(currentStr);
        }else{
            char currentChar = digits[0];
            string digitsSuffix = digits.substr(1, digits.length() - 1);
            for(char letter : m_map[currentChar]){
                currentStr.push_back(letter);
                letterCombinationAux(digitsSuffix, currentStr, resOut);
                currentStr.pop_back();
            }
        }
    }

    vector<char> twoLetter = {'a', 'b', 'c'};
    vector<char> threeLetter = {'d', 'e', 'f'};
    vector<char> fourLetter = {'g', 'h', 'i'};
    vector<char> fiveLetter = {'j', 'k', 'l'};
    vector<char> sixLetter = {'m', 'n', 'o'};
    vector<char> sevenLetter = {'p', 'q', 'r', 's'};
    vector<char> eightLetter = {'t', 'u', 'v'};
    vector<char> nineLetter = {'w', 'x', 'y', 'z'};

    std::map<char, vector<char>> m_map{
                                  {'2', twoLetter}, {'3', threeLetter}, {'4', fourLetter},
                                  {'5', fiveLetter}, {'6', sixLetter}, {'7', sevenLetter},
                                  {'8', eightLetter}, {'9', nineLetter}};

};
