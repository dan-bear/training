/**
 * Please read the description here:
 * https://leetcode.com/problems/determine-if-two-strings-are-close
 * #STR #string #str #STRING #sort #histogram
 */
///SOLUTION
#define NUM_OF_ASCII_CHARS 256
int compareInt(const void* pIntVal1, const void* pIntVal2);
void fillHisto(char* word, int* histo);
bool isSameArray(int* arr1, int* arr2, int arrLen);
bool checkSameLetters(int* histo1, int* histo2);
bool checkSameSortedHisto(int* histo1, int* histo2);

bool closeStrings(char* word1, char* word2) {
    ///1: If it was only swapping, same histogram
    ///   is close word.
    ///2: Transform existing when thinking of an histogram
    ///   is swapping the NON-ZERO values in the histogram.
    ///   Note: the order does not matter since the 
    ///         swap operation allows to put each
    ///         letter in its place..
    ///
    ///So, the algorithm is as follows:
    ///1: check whether the letters that appear in the
    ///   strings are the same letters. The operations
    ///   cannot help changing str1 to str2 if there is
    ///   a letter in str1 that does not exists in str2
    ///   and vice versa.
    ///2: Check whether the sorted histogram of the strings
    ///   is the same one. If so, the trasform can let us
    ///   change a letter to another letter and the swap
    ///   can promis the order.

    int histo1[NUM_OF_ASCII_CHARS] = {0};
    int histo2[NUM_OF_ASCII_CHARS] = {0};
    fillHisto(word1, histo1);
    fillHisto(word2, histo2);
    bool res = checkSameLetters(histo1, histo2);
    if(res){
        res = checkSameSortedHisto(histo1, histo2);
    }
    return res;
}

bool checkSameLetters(int* histo1, int* histo2){
    bool res = true;
    for(int idx = 0; idx < NUM_OF_ASCII_CHARS && res; idx++){
        res = ((histo1[idx] == 0 && histo2[idx] == 0) ||
               (histo1[idx] > 0 && histo2[idx] > 0));
    }
    return res;
}

bool checkSameSortedHisto(int* histo1, int* histo2){
    qsort(histo1, NUM_OF_ASCII_CHARS, sizeof(int), compareInt);
    qsort(histo2, NUM_OF_ASCII_CHARS, sizeof(int), compareInt);
    bool res = isSameArray(histo1, histo2, NUM_OF_ASCII_CHARS);
    return res;
}

void fillHisto(char* word, int* histo){
    int idx = 0;
    while(word[idx]){
        histo[word[idx]]++;
        idx++;
    }
}

bool isSameArray(int* arr1, int* arr2, int arrLen){
    bool res = true;
    for(int idx = 0; idx < arrLen && res; idx++){
        res = (arr1[idx] == arr2[idx]);
    }
    return res;
}

int compareInt(const void* pIntVal1, const void* pIntVal2){
    return *((int*)pIntVal1) - *((int*)pIntVal2);
}
