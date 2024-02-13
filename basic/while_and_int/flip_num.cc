int flipNumber(int num){
    int flippedNum = 0;
    while(num != 0){
        flippedNum *= 10;
        flippedNum += num % 10;
        num /= 10;
    }
    return flippedNum;
}
