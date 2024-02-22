/**
 * NOTE: the null-terminator char is the char '\0' whose numeric
 * value in the ascii table is 0.
 * 
 * Implement the function int calcStrLen(char* pWord)
 * The function gets the pWord which is the address where
 * chars that end with the null-terminator char are stored
 * CONTINUOUSLY!!!!!!. 
 * For example, pWord can be 1024:
 * address  | value
 * 1024     |   'h'
 * 1025     |   'a'
 * 1026     |   'l'
 * 1027     |   'l'
 * 1028     |   'o'
 * 1029     |   ' '
 * 1030     |   'w'
 * 1031     |   'o'
 * 1032     |   'r'
 * 1033     |   'l'
 * 1034     |   'd'
 * 1035     |   '\0'
 * The function should calculate the number of chars without
 * the null-terminaor char. In the example above the function
 * should return 11, since there are 11 chars in "hello world".
 *
 * HINT: how can you stop the iteration without knowing the
 *       number of chars in advance?
 *
 */

///SOLUTION:
int calcStrLen(char* pWord){
    int idx = 0;
    char nullTerminator = '\0';
    while(pWord[idx] != nullTerminator){
        idx++;
    }
    return idx;
    /// Note: make sure your understand the next version.
    /// Version2:
    // int length = 0;
    // char nullTerminator = '\0';
    // while(*pWord != nullTerminator){
    //     pWord++;
    //     length++;
    // }
    // return length;

    /// Version3:
    // int length = 0;
    // char nullTerminator = '\0';
    // while(pWord[0] != nullTerminator){
    //     pWord++;
    //     length++;
    // }
    // return length;
}


