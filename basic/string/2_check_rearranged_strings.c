/**
 * Implement the function:
 * bool checkRearrangedStrings(char* str1, char* str2)
 * @param str1 a string thats ends with null terminator ('\0').
 * @param str2 a string thats ends with null terminator ('\0').
 * @return whether str1 letters can be rearranged to form
 * str2.
 * Example1: str1 = "ab#r$cccc"
 *           str2 = "#crcabc$c"
 * str1's chars can be rearranged to get str2.
 * Example2: str1 = "abc"
 *           str2 = "a$c"
 * str1's chars cannot be rearranged to get str2.
 * 
 * #str #string #STR #STRING
 * 
 */
///Solution:
#define NUM_OF_ASCII_CHARS 256
void fillHisto(char* str, int* histo);
bool checkSameHisto(int* histo1, int* histo2);
bool checkRearrangedStrings(char* str1, char* str2)
{
    int histo1[NUM_OF_ASCII_CHARS] = { 0 };
    int histo2[NUM_OF_ASCII_CHARS] = { 0 };
    fillHisto(str1, histo1);
    fillHisto(str2, histo2);
    bool res = checkSameHisto(histo1, histo2);
    return res;
}

void fillHisto(char* str, int* histo){
    int idx = 0;
    while(str[idx]){
        histo[str[idx]]++;
        idx++;
    }
}
bool checkSameHisto(int* histo1, int* histo2){
    bool res = true;
    for (int idx = 0; idx < NUM_OF_ASCII_CHARS && res; idx++){
        res = (histo1[idx] == histo2[idx]);
    }
    return res;
}
