/**
 * https://leetcode.com/problems/length-of-last-word
 * #string
 */
int strLength(char* s);
int lengthOfLastWord(char* s) {
    char space = ' ';
    int sLen = strLength(s);
    int lastWordLen = 0;
    for(int charIdx = sLen - 1; charIdx >= 0; charIdx--){
        if(s[charIdx] != space){
            lastWordLen++;
        }else{
            if(lastWordLen > 0){
                ///1: lastWordLen > 0 means that a non-space char
                ///   was already found.
                ///2: s[charIdx] is space.
                ///So the last word is consumed and the loop should
                ///terminate.
                break;
            }
        }
    }
    return lastWordLen;
}

int strLength(char* s){
    int len = 0;
    while(s[len] != '\0'){
        len++;
    }
    return len;
}
