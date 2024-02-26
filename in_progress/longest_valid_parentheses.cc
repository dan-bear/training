/**
 * https://leetcode.com/problems/longest-valid-parentheses/
 * 
 */

class Solution {
public:
        
    int longestValidParentheses(string s){
        //int res = dpLongestValidParentheses(s);
        //int res = bruteForceLongestValidParentheses(s);
        int res = stackLongestValidParentheses(s);
        return res;
    }


private:
    
    int stackLongestValidParentheses(const string& s){
        char openBracket = '(';
        char closeBracket = ')';
        
        vector<int> vIdxOfUnmatchedBrackets;
        for(int charIdx = 0; charIdx < s.lenth(); charIdx++){
            if(s[charIdx] == openBracket){
                vIdxOfUnmatchedBrackets.push_back(charIdx);
            }else{
                if(vIdxOfUnmatchedBrackets.empty() ||
                   vIdxOfUnmatchedBrackets.back() == closeBracket){
                       //cannot match current close bracket.
                       vIdxOfUnmatchedBrackets.push_back(charIdx);
                }else{
                    //cool, the open bracket is matched, it can be poped.
                    vIdxOfUnmatchedBrackets.pop_back();
                }
            }
        }
        
        int maxLen = 0;
        // Now we got all the indices of unmatched brackets.
        // by finding the maximal distance between two indexes
        // we can calculate the longest valid parentheses.
        if(vIdxOfUnmatchedBrackets.empty()){
            maxLen = s.length();
        }else{
            int currLen = 0;
            int prevUnmatchedIdx = -1;
            for(int idx = 0; idx < vIdxOfUnmatchedBrackets.size(); idx++){
                currLen = (vIdxOfUnmatchedBrackets[idx] - prevUnmatchedIdx) - 1;
                maxLen = max(maxLen, currLen);
                prevUnmatchedIdx = vIdxOfUnmatchedBrackets[idx];
            }
        }
        return maxLen;
    }

    int stackLongestValidParenthesesAux(const string& s,
                                        char openBracket,
                                        char closeBracket, 
                                        int startIdx, 
                                        int lastNotInclusiveIdx, 
                                        int dir){
        
        int maxRes = 0;
        int currLen = 0;
        for(int charIdx = startIdx; charIdx != lastNotInclusiveIdx; charIdx += dir){
            if(s[charIdx] == openBracket){
                vLastOpenBracketIdx.push_back(charIdx);
            }else{
                if(vLastOpenBracketIdx.size() > 0){
                    currLen++;
                    vLastOpenBracketIdx.pop_back();
                }else{
                    maxRes = max(maxRes, currLen);
                    currLen = 0;
                }
            }
        }
        //there might be some open brackets that were not closed.
        
        maxRes = max(maxRes, currLen);//might have exhausted the string.
        return maxRes * 2;//counted pairs.
    }

    //failed on test 228 out of 231 due to time-limit-exceeded error.
    int bruteForceLongestValidParentheses(const string& s){
        int res = 0;
        for(int firstIdx = 0; firstIdx < s.length(); firstIdx++){
            for(int lastIdx = firstIdx + 1; lastIdx < s.length(); lastIdx++){
                if(isValidParentheses(s, firstIdx, lastIdx)){
                    res = max(res, lastIdx - firstIdx + 1);
                }
            }            
        }
        return res;

    }
    
    bool isValidParentheses(const string& s, int firstIdx, int lastIdx){
        int openBrackets = 0;
        for(int idx = firstIdx; idx <= lastIdx && openBrackets >= 0; idx++){
            if(s[idx] == skOpenBracket){
                openBrackets++;
            }else{
                openBrackets--;
            }
        }
        return openBrackets == 0;
    }







    //This solution got run-time exceeded in a very long test
    //227 out of 231 tests.
    int dpLongestValidParentheses(string s) {
        vector<vector<bool>> isValidTbl = calcIsValidDpTbl(s);
        int tblDim = isValidTbl.size();
        int maxPareSubStrLen = 0;
        for(int rowIdx = 0; rowIdx < tblDim; rowIdx++){
            for(int colIdx = rowIdx + 1; colIdx < tblDim; colIdx++){
                if(isValidTbl[rowIdx][colIdx]){
                    maxPareSubStrLen = max(maxPareSubStrLen, colIdx - rowIdx + 1);
                }
            }
        }
        return maxPareSubStrLen;
    }

    vector<vector<bool>> calcIsValidDpTbl(string s){
        int sLen = s.length();
        vector<vector<bool>> isValidTbl(sLen, vector<bool>(sLen, false));
        for(int diagIdx = 0; diagIdx < sLen; diagIdx++){
            for(int rowIdx = 0; rowIdx < sLen - diagIdx; rowIdx++){
                int colIdx = rowIdx + diagIdx;
                isValidTbl[rowIdx][colIdx] = isValid(s, isValidTbl, rowIdx, colIdx);
            }
        }
        return isValidTbl;
    }


    /**
     * define isValid[i][j] to be true if s[i:j] is a valid
     * parentheses and false if s[i:j] is not.
     * 1: isValid[i][i+2*k] = false since s[i:i+2k] contains
     *    odd number of parentheses.
     * 2: isValid[i][i+1] = true <=> s[i:i+1] == "()"
     * 3: isValid[i][j] = true if:
     *    3.1: (j - i) % 2 == 1 //note it's index subtraction
     *    3.2: exists d in range {i, i+1 ,.. j} such that:
     *         s[i] = '(', s[d] = ')' isValid[i+1][d-1] and isValid[d+1][j]
     */
    bool isValid(const string& s, const vector<vector<bool>>& isValidTbl, int rowIdx, int colIdx){
        bool bRes = false;
        if(s[rowIdx] == skOpenBracket && (colIdx - rowIdx) % 2 == 1){
            if(colIdx - rowIdx == 1){
                bRes = (s[colIdx] == skCloseBracket);
            }else{
                for(int closePareIdx = rowIdx + 1; closePareIdx <= colIdx; closePareIdx+=2){
                    if(s[closePareIdx] == skCloseBracket){
                        if(closePareIdx == rowIdx + 1 || isValidTbl[rowIdx + 1][closePareIdx - 1]){
                            if(closePareIdx == colIdx || isValidTbl[closePareIdx + 1][colIdx]){
                                bRes = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
        return bRes;
    }

    static constexpr char skOpenBracket = '(';
    static constexpr char skCloseBracket = ')';
};
