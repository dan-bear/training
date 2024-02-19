bool isPalindrome(int num){
    int flippedNum = 0;
    while (num > 0) {
        flippedNum *= 10;
        flippedNum += num % 10;
        num /= 10;
    } 
    // Note: you might notice that the code above is the
    // same implementation of int flipNum(int num). So
    // in practice it could have been written as a 
    // separate function and called from here instead of
    // being implemented here.
   
    bool bRes = (flippedNum == num);
    return bRes;
}

int printTestingFunc(){
    int num = 787;
    if (isPalindrome(num)) {
        printf("%d is a palindrome!", num);
    } else {
        printf("%d is not a palindrome!", num);
    }
}
