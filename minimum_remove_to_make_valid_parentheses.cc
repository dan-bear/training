/**
 * https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/
 * Similar to: https://leetcode.com/problems/longest-valid-parentheses/
 * #PARENTHESES #stack #linear-space-time
*/

class Solution {
public:
    string minRemoveToMakeValid(string s) {
        ///using the stack method to hold unmatched
        ///parentheses indexes.
        vector<int> vIdxOfUnmatchedBrackets;
        findUnmatchedBrackets(s, vIdxOfUnmatchedBrackets);
        return removeUnmatchedBrackets(s, vIdxOfUnmatchedBrackets);
    }
private:

    void findUnmatchedBrackets(const string& s, vector<int>& vIdxOfUnmatched){
        for(int charIdx = 0; charIdx < s.length(); charIdx++){
            if(s[charIdx] == skOpen){
                vIdxOfUnmatched.push_back(charIdx);
            }else if(s[charIdx] == skClose){
                if(!vIdxOfUnmatched.empty() && s[vIdxOfUnmatched.back()] == skOpen){
                    //An open bracket is matched.
                    vIdxOfUnmatched.pop_back();
                }else{
                    vIdxOfUnmatched.push_back(charIdx);
                }
            }
        }
    }

    string removeUnmatchedBrackets(string& s, const vector<int>& vIdxOfUnmatched){  
        /// First option. 
        /// Note: I think it's a slower one, since erasing elements
        /// is a pretty costly op. Also, codewise, I prefer this 
        /// one.
        int numOfRemovedElemes = 0;
        for(int idx : vIdxOfUnmatched){
            s.erase(idx - numOfRemovedElemes, 1);
            numOfRemovedElemes++;
        }
        return s;        


        /// Second option (more straight forward option):
        
        // /// Note: could have start with empty string and use
        // /// push_back, but I prefer to allocatting in advance
        // /// when possible.
        // string res(s.length() - vIdxOfUnmatched.size(), ' ');
        // int currUnmatchedIdx = 0;
        // int resFrontIdx = 0;
        // for(int idx = 0; idx < s.length(); idx++){
        //     if(currUnmatchedIdx == vIdxOfUnmatched.size() || idx != vIdxOfUnmatched[currUnmatchedIdx]){
        //         res[resFrontIdx] = s[idx];
        //         resFrontIdx++;
        //     }else{
        //         currUnmatchedIdx += 1;
        //     }
        // }
        // return res;

    }

    static constexpr char skOpen = '(';
    static constexpr char skClose = ')';
};
