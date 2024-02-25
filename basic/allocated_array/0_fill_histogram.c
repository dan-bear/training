/**
 * A histogram allows to count the number of time each
 * letter appears in a string.
 * Implement the function:
 * void fillHistogram(char* pChars, int histogram[NUM_OF_LETTERS])
 * - pChars is the address where chars representing only
 *   small english letters ('a' to 'z') are continuously 
 *   stored and the last char is the null terminator ('\0').
 *   For example, pChars can be 1024:
 *   address  | value
 *   1024     |   'h'
 *   1025     |   'a'
 *   1026     |   'l'
 *   1027     |   'l'
 *   1028     |   'o'
 *   1029     |   'w'
 *   1030     |   'o'
 *   1031     |   'r'
 *   1032     |   'l'
 *   1033     |   'd'
 *   1034     |   '\0'
 * 
 * - histogram[] as an array of size NUM_OF_LETTERS (see the
 *   definition below) where each idx corresponds to an 
 *   english letter with respect to the english alphabet 
 *   order. What means that: 0 corresponds to 'a',
 *                           1 corresponds to 'b',
 *                           2 corresponds to 'c',
 *                           ...
 *                           25 corresponds to 'z'
 *   The function should fill the histogram such that 
 *   the number of times each letter appears in pChars 
 *   (WHILE IGNORING THE NULL TERMINATOR CHAR ('\0')) is
 *   written in the corresponding element in the histogram.
 *   Using the example above where pChars, points to
 *   "helloworld" the histogram array should be filled as
 *    follows (the corresponding letters are added for 
 *    clarity):
 *        a b c d e f g h i j k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
 *   idx: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 
 *   val: 0 0 0 1 1 0 0 1 0 0 0  3  0  0  2  0  0  1  0  0  0  0  1  0  0  0 
 * 
 * 
 * 
 * 
 * @note:
 * - you can assume the histogram's elements are already
 *   initialized to 0.
 * - you can assume there are only 'a'-'z' chars in pChars 
 *   expect from the null-terminator char that tells when
 *   the chars end.
 */

///SOLUTION
#define NUM_OF_LETTERS 'z' - 'a' + 1
void fillHistogram(char* pChars, int histogram[NUM_OF_LETTERS])
{
    char firstLetter = 'a';
    while (*pChars) {
        histogram[*pChars - firstLetter]++;
        pChars++;
    }

    // //Option 2:
    // char firstLetter = 'a';
    // int charIdx = 0;
    // while(pChars[charIdx]){
    //     histogram[pChars[charIdx] - firstLetter]++;
    //     charIdx++;
    // }

    // // Option 2.5:
    // char firstLetter = 'a';
    // int charIdx = 0;
    // int histoIdx = 0;
    // while(pChars[charIdx]){
    //     histoIdx = pChars[charIdx] - firstLetter;
    //     histogram[histoIdx]++;
    //     charIdx++;
    // }

    // //Like first solution but without dereference operator (*):
    // char firstLetter = 'a';
    // while(pChars[0]){
    //     histogram[pChars[0] - firstLetter]++;
    //     pChars++;
    // }
}


//usage example:
#include <stdio.h>

void printArr(int arr[], int len);
int main(){
    int histogram[NUM_OF_LETTERS] = { 0 };
    char* pString = "helloworld";
    fillHistogram(pString, histogram);
    printArr(histogram, NUM_OF_LETTERS);
    return 0;
}


void printArr(int arr[], int len)
{
    for (int idx = 0; idx < len; idx++) {
        printf("%d ", arr[idx]);
    }
    printf("\n");
}
