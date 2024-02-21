/**
 * Please read the description here:
 * https://leetcode.com/problems/merge-strings-alternately
 * #str #string #STR #STRING
 * #malloc #memory-allocation #allocation #alloc
 */

int calcStrNumOfChars(char* str);
char * mergeAlternately(char * word1, char * word2){
    int word1NumOfChars = calcStrNumOfChars(word1);
    int word2NumOfChars = calcStrNumOfChars(word2);
    int resLen = word1NumOfChars + word2NumOfChars + 1;//+1 for '\0'
    char* pRes = malloc(resLen);
    //Put a null terminator as the result's last char.
    char nullTerminator = '\0';
    pRes[resLen - 1] = nullTerminator;

    int copyFromIdx = 0;
    int insertIdx = 0;
    while(copyFromIdx < word1NumOfChars && copyFromIdx < word2NumOfChars){
        pRes[insertIdx] = word1[copyFromIdx];
        insertIdx++;
        pRes[insertIdx] = word2[copyFromIdx];
        insertIdx++;
        copyFromIdx++;
    }
    while(copyFromIdx < word1NumOfChars){
        pRes[insertIdx] = word1[copyFromIdx];
        insertIdx++;
        copyFromIdx++;
    }
    while(copyFromIdx < word2NumOfChars){
        pRes[insertIdx] = word2[copyFromIdx];
        insertIdx++;
        copyFromIdx++;
    }
    return pRes;
}


int calcStrNumOfChars(char* str){
    int len = 0;
    char nullTerminator = '\0';
    while(str[len] != nullTerminator){
        len++;
    }
    return len;
}
