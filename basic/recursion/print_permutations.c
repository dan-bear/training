/**
 * Implement the function:
 * void printAllPermutations(char* str) 
 * where:
 * 1: str is a null terminated string.
 * 2: The function prints all the possible permutations of
 *    the letters in str (each permutation in a new line).
 *    For example: str = {'a', 'b', 'c', '\0'}
 *    Then the function prints the next strings:
 *    abc
 *    acb
 *    bac
 *    bca
 *    cab
 *    cba
 *    The order of the printing does not matter, but each
 *    permutation should be printed once.
 * 
 * Complexity constraints:
 * time: O(len(str)!)
 * space: O(len(str))
 */
///SOLUTION:
void printAllPermutationsAux(char* str, int currentIdx);
void printAllPermutations(char* str){
    printAllPermutationsAux(str, 0);
}

void printAllPermutationsAux(char* str, int currentIdx){
    if(str[currentIdx] == '\0'){
        printf(" %s\n", str);
        return;
    }
    int idx = currentIdx;
    while(str[idx] != '\0'){
        swap(str, currentIdx, idx);
        printAllPermutationsAux(str, currentIdx + 1);
        swap(str, currentIdx, idx);
        idx++;
    }
}
