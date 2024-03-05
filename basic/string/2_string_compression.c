/**
 * Please read the question description here:
 * https://leetcode.com/problems/string-compression
 * 
 */
///SOLUTION

///Forward declaration:
char fromDigitToChar(int digit);
int calcNumLen(unsigned int num);
char* fromUnsignedIntToStr(unsigned int num);
int writeCountToStr(char* chars, int position, int currCount);

int compress(char* chars, int charsSize) {
    int currChar = chars[0];
    int currCount = 1;
    int frontIdx = 0;

    for(int charIdx = 1; charIdx < charsSize; charIdx++){
        if(chars[charIdx] == currChar){
            currCount++;
        }else{
            chars[frontIdx] = currChar;
            frontIdx++;
            if(currCount > 1){
                frontIdx += writeCountToStr(chars, frontIdx, currCount);
            }
            currChar = chars[charIdx];
            currCount = 1;
        }
    }

    ///As usual, we need another round for the last
    ///chars sequence
    chars[frontIdx] = currChar;
    frontIdx++;
    if(currCount > 1){
        frontIdx += writeCountToStr(chars, frontIdx, currCount);
    }
    
    return frontIdx;
}

int writeCountToStr(char* chars, int position, int currCount){
    char* pStrCount = fromUnsignedIntToStr(currCount);
    int charIdx = 0;
    while(pStrCount[charIdx]){
        chars[position] = pStrCount[charIdx];
        charIdx++;
        position++;
    }
    free(pStrCount);
    return charIdx;
}

char* fromUnsignedIntToStr(unsigned int num){
    ///+1 since null terminator is needed.
    int numStrLen = calcNumLen(num) + 1;
    char* pRes = (char*)malloc(sizeof(char) * numStrLen);
    pRes[numStrLen - 1] = '\0';
    for(int charIdx = numStrLen - 2; charIdx >= 0; charIdx--){
        pRes[charIdx] = fromDigitToChar(num % 10);
        num /= 10;
    }
    return pRes;
}

int calcNumLen(unsigned int num){
    int count = 0;
    while(num > 0){
        count++;
        num /= 10;
    }
    //count is 0 in case num = 0.
    return count == 0 ? 1 : count;
}

char fromDigitToChar(int digit){
    char res =  (char)digit + '0';
    return res;
}
