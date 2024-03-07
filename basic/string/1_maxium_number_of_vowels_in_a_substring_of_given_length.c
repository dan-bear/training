/**
 * Please read the question's description here:
 * https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length
 * #str #string #STR #STRING #sliding-window
 */
///SOLUTION
bool isVowel(char c);
int max(int x, int y);
int maxVowels(char* s, int k) {
    int leftIdx = 0;
    int rightIdx = k - 1;
    int maxNumOfVowels = 0;
    int numOfVowels = 0;
    for(int idx = leftIdx; idx <= rightIdx; idx++){
        if(isVowel(s[idx])){
            numOfVowels++;
        }
    }
    maxNumOfVowels = numOfVowels;
    while(s[rightIdx] != '\0'){
        if(isVowel(s[leftIdx])){
            numOfVowels--;
        }
        leftIdx++;
        rightIdx++;
        if(isVowel(s[rightIdx])){
            numOfVowels++;
            maxNumOfVowels = max(maxNumOfVowels, numOfVowels);
        }
    }
    return maxNumOfVowels;
}

char toLower(char c){
    if(c < 'a'){
        c += 'a' - 'A';
    }
    return c;
}

bool isVowel(char c){
    c = toLower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c =='u');
}

int max(int x, int y){
    return x > y ? x : y;
}
