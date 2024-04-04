/**
 * A palindrome is a sequence of symbols that stays 
 * the same if read from left to right and from right to left.
 * Examples:
 * 1: "dad"
 * 2: "314413"
 * 3: %#!tryrt!#%
 * Counter example:
 * 1: "example"
 * 2: "31415"
 * 
 * Implement the function bool isPalindrome(char* str) where:
 * 1: str is a null terminated string.
 * 2: the function returns true if the given str is a
 *    palindrome and false otherwise. 
 * 
 * 1: The solution need to be recursive.
 * 2: You can (and it's recommended) to implement helper
 *    functions.
 * 3: The complexity constraints are:
 *    Time: O(len(str)), Space: O(len(str)).
 */
#include <stdbool.h>
///SOLUTION:
int stringLenWithoutNullTerm(char* str);
bool isPalindromeAux(char* str, int strLen);
bool isPalindrome(char* str){
    int lenWithoutNullTerminator = stringLenWithoutNullTerm(str);
    return isPalindromeAux(str, lenWithoutNullTerminator);
}

bool isPalindromeAux(char* str, int strLen){
    if(strLen <= 1){
        return true;
    }
    if(str[0] != str[strLen - 1]){
        return false;
    }
    return isPalindromeAux(str + 1, strLen - 2);
}

int stringLenWithoutNullTerm(char* str){
    int idx = 0;
    while(str[idx]){
        idx++;
    }
    return idx;
}
