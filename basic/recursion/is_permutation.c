void swap(char* str, int idx1, int idx2);
int findCharInStr(char c, char* str);
/**
 * The idea of the solution:
 * Take the first char in str1 and search it in str2.
 * if it's not found: return false.
 * if it's found: swap the char found in str2 with the char
 * in str2[0] and start again, but now with the substrings:
 * str1[1...len(str1)-1] and str2[1...len(str2)-1]. This
 * "restart" is done by calling the isPermutation with the
 * substrings (recursive calls).
 * The recursion needs to halt when str1[0] = '\0'.
 */
bool isPermutation(char str1[], char str2[])
{
    /// Start by checking the halting condition:
    if (str1[0] == '\0') {
        if (str2[0] == '\0') {
            /// Both str1 and str2 were consumed, it means
            /// they are permutation of each other.
            return true;
        } else {
            /// str1 is consumed, but there are still letters
            /// in str2, so s1 and s2 are not permutations of
            /// each other.
            return false;
        }
    }
    int charIdxInStr2 = findCharInStr(str1[0], str2);
    if (charIdxInStr2 < 0) {
        /// The char is not found, so the strings are not
        /// permutations of each other.
        return false;
    }
    /// swap with the first character in str2.
    swap(str2, 0, charIdxInStr2);
    /// using pointer arithmetic to move on to the substrings
    /// str1[1...len(str1)-1] and str2[1...len(str2)-1].
    return isPermutation(str1 + 1, str2 + 1);
}

void swap(char* str, int idx1, int idx2)
{
    char temp = str[idx1];
    str[idx1] = str[idx2];
    str[idx2] = temp;
}

int findCharInStr(char c, char* str)
{
    int idx = 0;
    while (str[idx] != '\0' && str[idx] != c) {
        idx++;
    }
    if (str[idx] == c) {
        return idx;
    } else {
        /// it means that str[idx] == '\0'
        return -1; /// invalid index.
    }
}
