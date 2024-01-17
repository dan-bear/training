/**
 * https://leetcode.com/problems/repeated-substring-pattern
 */
  
class FullSearchSolution {
public:
    bool repeatedSubstringPattern(const string& s) {
        bool res = false;
        for(int patternLen = 1; patternLen <= s.length() / 2 && !res; patternLen += 1){
            res = repeatedSubstringPatternOfGivenLength(s, patternLen);
        }
        return res;
    }

private:
    bool repeatedSubstringPatternOfGivenLength(const string& s, int patternLen){
        for(int compareIdx = 0; compareIdx < s.length(); compareIdx += patternLen){
            for(int baseIdx = 0; baseIdx < patternLen; baseIdx += 1){
                if(compareIdx + baseIdx >= s.length() ||
                 s[baseIdx] != s[compareIdx + baseIdx]){
                    return false;
                }
            }
        }
        return true;
    }
};


class ConcatSolution{
public:
    bool repeatedSubstringPattern(string s) {
        string selfConcate = s + s;
        selfConcate.erase(0, 1);
        selfConcate.erase(selfConcate.length() - 1, 1);
        bool res = selfConcate.find(s) != string::npos;
        return res; 
    }
};

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        //FullSearchSolution sol;
        ConcatSolution sol;
        return sol.repeatedSubstringPattern(s);
    }
};
