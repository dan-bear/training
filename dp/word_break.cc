/**
 * https://leetcode.com/problems/word-break
 * #dp #DP
 * #backtracking
 */
class Solution {
public:
    /**
     * Edge cases:
     * 1: The problem constraints prevent this edge case, but what happens if
     *    s is the empty word? Mathematically speaking it can be separated 
     *    by choosing no word from the dictionary.
     * 2: The dictionary is empty and s is not the empty word, in this case
     *    the answer is no.
     * 
     *
     * Define dp[i] whether word[0 : i - 1] can be separated by the dictionary.
     * when word[0 : -1] relates to the empty word.
     * dp[0 : 0] = true (see the edge case above).
     * Run throgh the words in the dictionary and for each dictWord:
     * dp[i] = true <=> word[(i - 1) - dictWord.length() : (i - 1)] == dictWord
     *                  and dp[i - dictWord.length()] == true.
     * 
     * The space complexity is O(s.length()), the time complexity is:
     * s.length() * sum(dictWord[i].length() for i in range dict.size()) 
     *
     * A backtracking approach for this problem is for every dict-word
     * in the dictionary:
     * 1: Try to consume a substring from s using the dictWord.
     *    continue with the rest of s and the rest of the dict-word.
     * 2: Don't try to consume a substring with the dictWord,
     *    continue with the s and the rest of the dict-word.
     *
     */
    bool wordBreak(string s, vector<string>& wordDict) {
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;
        for(int idx = 1; idx <= s.size(); idx++){
            for(int wordIdx = 0; wordIdx < wordDict.size() && !dp[idx]; wordIdx++){
                dp[idx] = isSuffix(s, idx, wordDict[wordIdx]) && 
                              dp[idx - wordDict[wordIdx].size()];
            }
        }
        return dp[s.size()];
    }
private:
    bool isSuffix(const string& s, int sLen, const string& word){
        bool res = (word.size() <= sLen && isSameSuffix(s, sLen, word));
        return res;
    }

    bool isSameSuffix(const string& s, int sLen, const string& word){
        return s.compare(sLen -  word.size(), word.size(), word) == 0;
        // bool res = true;
        // for(int idx = 0; idx < word.size() && res; idx++){
        //     res = word[idx] == s[sLen - word.size() + idx]; 
        // }
        // return res;
    }
};
