#include <stdio.h>

/**
 * Print all the digits of a number GREATER THaN 0,
 * the printing should satisfy the next pattern:
 * 1: The digits are separated by space.
 * 2: The order of the digits to print is from right to
 *    left (units digit, tens digit, hundreds digit and so
 *    on).
 * Example:
 *          num = 12345
 *          print should be: 5 4 3 2 1
 *
 * Note1: assume the input number is always > 0, you do not
 *       need to check it.
 *
 *
 */
void printAllDigits(int num)
{

    while (num > 0) {
        int lastDigit = num % 10;
        printf("%d ", lastDigit);
        num /= 10; // same as num = num / 10;
    }
  
    // Note this function does not return a value, so the
    // return statement is not needed.
}

// usage example:
int mai()
{
    printAllDigits(1);
    printAllDigits(12);
    printAllDigits(123);
    printAllDigits(31415926);

    return 0;
}
