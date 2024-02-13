int getMaxDigit(int num){
    int maxDigit = 0;
    while(num != 0){
        if(num % 10 > maxDigit){
            maxDigit = num % 10;
        }
        num /= 10;
    }
    return maxDigit;
}
