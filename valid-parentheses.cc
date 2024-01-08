/**
 * https://leetcode.com/problems/valid-parentheses
 */
class Solution {
public:
    
    bool isValid(string s) {
        bool bRes = true;
        vector<char> vOpenPareStack;
        
        for(char& bracket : s){
            if(getBracketType(bracket) == BracketType::kOpen){
                vOpenPareStack.push_back(bracket);
            }else{
                if(vOpenPareStack.size() > 0){
                    char lastOpenBracket = vOpenPareStack.back();
                    if(isBracketsMatch(lastOpenBracket, bracket) == false){
                        bRes = false;
                        break;
                    }
                    vOpenPareStack.pop_back();
                }else{
                    //more closing brackets than open ones.
                    bRes = false;
                    break;
                }
            }
        }

        if(vOpenPareStack.empty() == false){
            bRes = false;
        }
        
        return bRes;
    }

private:

    static constexpr char skOpenBrackets[] = {'(', '[', '{'};
    static constexpr char skCloseBrackets[] = {')', ']', '}'};
    static constexpr int skNumOfBracketsType{3};

    enum class BracketType{
        kOpen,
        kClose
    };

    BracketType getBracketType(char c){
        BracketType res = BracketType::kClose;
        for(int bracketIdx = 0; bracketIdx < skNumOfBracketsType; bracketIdx++){
            if(c == skOpenBrackets[bracketIdx]){
                res = BracketType::kOpen;
                break;
            }
        }
        return res;
    }

    bool isBracketsMatch(char openBracket, char closeBracket){
        bool bRes = false;
        for(int bracketIdx = 0 ; bracketIdx < skNumOfBracketsType; bracketIdx++){
            if(openBracket == skOpenBrackets[bracketIdx]){
                if(closeBracket == skCloseBrackets[bracketIdx]){
                    bRes = true;
                    break;
                }
            }
        }
        return bRes;
    }
};
