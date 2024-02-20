/**
 * https://leetcode.com/problems/reverse-words-in-a-string
 * #string #str #STRING #STR
 */

class Solution {
public:
    string reverseWords(string s) {
        cleanTrailingSpaces(s);
        flipString(s);
        flipWords(s);
        return s;
        
    }

private:
    void flipWords(string& s){
        int wordFirstCharIdx = 0;
        int wordLastCharIdx = 0;
        while(wordFirstCharIdx < s.length()){
            wordLastCharIdx = findWordLastCharIdx(s, wordFirstCharIdx);
            flipWord(s, wordFirstCharIdx, wordLastCharIdx);
            wordFirstCharIdx = wordLastCharIdx + 2; //skip the space!
        }
    }


    void flipWord(string& s, int wordFirstCharIdx, int wordLastCharIdx){
        while(wordFirstCharIdx < wordLastCharIdx){
            swap(s, wordFirstCharIdx, wordLastCharIdx);
            wordFirstCharIdx++;
            wordLastCharIdx--;
        }
    }

    int findWordLastCharIdx(const string& s, int wordFirstCharIdx){
        char space = ' ';
        int wordLastCharIdx = wordFirstCharIdx;
        while(s[wordLastCharIdx] != space && wordLastCharIdx < s.length()){
            wordLastCharIdx++;
        }
        //Found a space or exceeded the last index in the string.
        wordLastCharIdx--;
        return wordLastCharIdx;
    }


    void flipString(string& s){
        int firstIdx = 0;
        int lastIdx = s.length() - 1;
        while(firstIdx < lastIdx){
            swap(s, firstIdx, lastIdx);
            firstIdx++;
            lastIdx--;
        }
    }
  
    void cleanTrailingSpaces(string& s){
        char space = ' ';
        int charIdx = 0;
        
        while(charIdx < s.length()){
            bool bIncIdx = true;
            if(s[charIdx] == space){
                if(charIdx == 0 || s[charIdx - 1] == space){
                    s.erase(charIdx, 1);
                    bIncIdx = false; //leave the idx here due to removal.
                }
            }
            charIdx = bIncIdx ? charIdx + 1 : charIdx;
        }
        //unfortunately if there are trailing spaces after the
        //last char, one space will be left.
        if(s[s.length() - 1] == space){
            s.erase(s.length() - 1);
        }
    }

    void swap(string& s, int idx1, int idx2){
        char char1 = s[idx1];
        char char2 = s[idx2];
        s[idx1] = char2;
        s[idx2] = char1;
    }

};
