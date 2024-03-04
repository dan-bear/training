/**
 * See question description here:
 * https://leetcode.com/problems/reverse-vowels-of-a-string
 * #two-pointers #2ptr #str #string #STR #STRING
 */
int calcLength(char* s);
bool isVowel(char c);
void swapChars(char* s, int idx1, int idx2);
///SOLUTION
char* reverseVowels(char* s) {
    int leftIdx = 0;
    int rightIdx = calcLength(s) - 1;
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

int calcLength(char* s){
    int len = 1;
    char* pCurrChar = s;
    while(*pCurrChar != '\0'){
        len += 1;
        pCurrChar++;
    }
    ///Note: wanted to calculate the length including the
    ///      null terminator. Since len is not increased
    ///      when pCurrChar reaches '\0' instead of 
    ///      increasing len after the while, len is just 
    ///      initialized to 1 and not to 0.
    return len;
}

char toLower(char c){
    if(c < 'a'){
        c += ('a' - 'A');
    }
    return c;
}

bool isVowel(char c){
    ///Option1:
    c = toLower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

void swapChars(char* s, int idx1, int idx2){
    char temp = s[idx1];
    s[idx1] = s[idx2];
    s[idx2] = temp;
}
