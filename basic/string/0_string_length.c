/**
 * Implement the function: int stringLength(char* str)
 * @param str a null-terminated string.
 * @return the number of chars in the string without the
 * null terminator.
 * Example: str = abcd\0 the function returns 4.
 * 
 * @note complexity constraints: 
 *       time: Theta(str length)
 *       space: Theta(1)
 */
///SOLUTION
int stringLength(char* str)
{
    int idx = 0;
    while (str[idx]) {
        idx++;
    }
    return idx;
}
