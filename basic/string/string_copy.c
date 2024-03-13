/**
 * Implement the function:
 * char* stringCopy(char* dst, char* src)
 * @param dst a pointer to memory where the data can be
 * copied into.
 * @param src a pointer to a null terminated string that
 * needs to be copied.
 * @return dst, a pointer to where the data was copied to.
 * 
 * @note the dst should contain the null-terminator symbol.
 * Example:
 * 
 * @note dst points to a memory location that can be
 * accessed by this method, it's the caller responsibility 
 * to allocate the space prior to calling this function.
 */
///SOLUTION
char* stringCopy(char* dst, char* src)
{
    int idx = 0;
    while(src[idx]){
        dst[idx] = src[idx];
        idx++;
    }
    ///don't forget the null-terminator.
    dst[idx] = '\0';
    return dst;
}
