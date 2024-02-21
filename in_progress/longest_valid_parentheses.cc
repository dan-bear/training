/**
 * https://leetcode.com/problems/longest-valid-parentheses/
 */


class Solution {
public:
    /**
     * define isValid[i][j] to be true if s[i:j] is a valid
     * parentheses and false if s[i:j] is not.
     * 1: isValid[i][i+2*k] = false since s[i:i+2k] contains
     *    odd number of parentheses.
     * 2: isValid[i][i+1] = true <=> s[i:i+1] == "()"
     * 3: isValid[i][i+2*k+1] = true if:
     *    exists d in range 0, 1, ..., k-1 such that:
     *    if s[i] = '(' and s[i+2d+1] = ')' and isValid[i+1, i+2d] and isValid[i+2d+2][i+2k+1]
     */
    int longestValidParentheses(string s) {
        vector<vector<bool>> isValidTbl = calcIsValidDpTbl(s);
        int maxPareSubStrLen = 0;
        for(int rowIdx = 0; rowIdx < isValidTbl.size(); rowIdx++){
            for(int colIdx = 0; colIdx < isValidTbl[0].size(); colIdx++){
                if(isValidTbl[rowIdx][colIdx]){
                    maxPareSubStrLen = max(maxPareSubStrLen, colIdx - rowIdx + 1);
                }
            }
        }
        return maxPareSubStrLen;
    }

private:
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
                for(int closePareIdx = rowIdx + 1; closePareIdx <= colIdx; closePareIdx++){
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
