/**
 * See question description here:
 * https://leetcode.com/problems/reverse-vowels-of-a-string
 * #two-pointers #2ptr #str #string #STR #STRING
 * 1: Read carfully whether capital letters are involved.
 * 2: Use string instead of array for the vowels.
 */
class Solution {
public:
    string reverseVowels(string s) {
        int leftIdx = 0;
        int rightIdx = s.length() - 1;
        while(leftIdx < rightIdx){
            bool bIsLeftVowel = isVowel(s[leftIdx]);
            bool bIsRightVowel = isVowel(s[rightIdx]);
            if(bIsLeftVowel && bIsRightVowel){
                swapChars(s, leftIdx, rightIdx);
                leftIdx++;
                rightIdx--;
            }else if(!bIsLeftVowel){
                leftIdx++;
            }else if(!bIsRightVowel){
                rightIdx--;
            }
        }
        return s;  
    }

private:
    void swapChars(string& s, int charIdx1, int charIdx2){
        char temp = s[charIdx1];
        s[charIdx1] = s[charIdx2];
        s[charIdx2] = temp;
    }
    
    
    bool isVowel(char x){
        return m_vowels.find(x) != string::npos;
        
        // Another option using an array.
        // bool res = false;
        // for(int idx = 0; idx < m_vowels.size(); idx++){
        //     if(x == m_vowels[idx]){
        //         res = true;
        //         break;
        //     }
        // }
        // return res;
    }
    string m_vowels = "aeiouAEIOU";
    //array<char, 10> m_vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
};
