/**
 * Implement the function 
 * char* stringConcat(char* dst, char* src)
 * @param dst the destination string.
 * @param src the source string
 * @return a pointer to the destination string.
 * The function copies the src string to the end
 * of the dst string and returns the dst string start
 * address.
 * 
 * @note it's assumed that the memory area where src is
 * copied into (after the dest string) is available, the 
 * caller is responsible for it, since this method is about
 * to write to it.
 * 
 * Example:
 * dst = hello'\0'
 * src = world'\0'
 * After the function completes:
 * dst = helloworld'\0'.
 * 
 * @note Another option (but that's not what is 
 * implemented in the standard library) is to malloc a
 * new string, copy the destination and source data and
 * return it. This way the user's responsibility is just to
 * free the concatenated string after it uses it. 
 * 
 */
///Solution:
int stringLength(char* str);
char* stringConcat(char* dst, char* src){
    int dstLen = stringLength(dst);
    int idx = 0;
    while(src[idx]){
        dst[dstLen + idx] = src[idx];
        idx++;
    }
    ///place the null terminator.
    dst[dstLen + idx] = '\0';
    return dst;
}

int stringLength(char* str)
{
    int idx = 0;
    while (str[idx]) {
        idx++;
    }
    return idx;
}
