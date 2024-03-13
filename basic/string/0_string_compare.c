/**
 * Implement the function int stringCompare(char* str1, char* str2)
 * @param str1 a null-terminated string.
 * @param str2 a null-terminated string.
 * @return 1 if str1 > str2
 * @return -1 if str1 < str2
 * @return 0 if str1 == str2.
 *
 * @note complexity constraints:
 *       time: Theta(max(len(str1), len(str2)))
 *       space: Theta(1)
 */
/// Solution:
int stringCompare(char* str1, char* str2)
{
    int idx = 0;
    while (str1[idx] && str2[idx]) {
        if (str1[idx] < str2[idx]) {
            return -1;
        } else if (str1[idx] > str2[idx]) {
            return 1;
        }
        idx++;
    }

    if (!str1[idx] && str2[idx]) {
        /// str1 was consumed before str2, so str1 < str2.
        return -1;
    }
    if (str1[idx] && !str2[idx]) {
        /// str2 was consumed before str1, so str1 > str2.
        return 1;
    }
    // equal strings!
    return 0;
}

/// Some printing.
// int main(){
//     char* s1 = "abcd";
//     char* s2 = "abc";
//     char* s3 = "ad";
//     printf("%d\n", stringCompare(s1, s2));
//     printf("%d\n", stringCompare(s2, s1));
//     printf("%d\n", stringCompare(s1, s3));
//     printf("%d\n", stringCompare(s3, s1));
//     printf("%d\n", stringCompare(s2, s3));
//     printf("%d\n", stringCompare(s3, s2));
//     printf("%d\n", stringCompare(s3, s3));
//     printf("%d\n", stringCompare(s2, s2));
//     printf("%d\n", stringCompare(s1, s1));

//     return 0;
// }
