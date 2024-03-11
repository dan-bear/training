/**
 * Implement the function:
 * bool checkDistinctChars(char* str)
 * @param str a c-string ended with null-terminator ('\0').
 * @return whether each char-symbol appears only once in the
 * string.
 * Example1: str = "abd$*&()tgi" the function returns true
 *           since no char appears more than once.
 * Example2: str = "tg!pio#pfs$p" the function returns false
 *           since 'p' appears more than once.
 *  
 * @note the implementation time and space complexity should
 * be: Time(strLength) = strLength, Space(strLength) = 1.
 * 
 * #str #string #STR #STRING
 */
#include <stdbool.h>
bool checkDistinctChars(char* str){
    ///Histogram for all the ascii table.
    int histogram[255] = { 0 };
    int idx = 0;
    while(str[idx]){
        ///Note: it's possible to write histogram[str[idx]]++
        ///      since there is an implicit conversion from
        ///      char to int in C, but it's better to cast
        ///      explicitly i.e. histogram[(int)str[idx]]++.
        histogram[str[idx]]++;
        idx++;
    }

    ///Let's check whether any char appears more than once.
    bool isDistinct = true;
    for (int charIdx = 0; charIdx < 255 && isDistinct; charIdx++){
        isDistinct = (histogram[charIdx] <= 1);
    }
    return isDistinct;
}


/// A print based test.
// #include <stdio.h>
// int main()
// {
//       printf("%d\n", checkDistinctChars("abd$*&()tgi"));
//       printf("%d\n", checkDistinctChars("tg!pio#pfs$p"));
//       return 0;
// }
