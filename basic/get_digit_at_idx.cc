int getDigitAtIdx(int num, int digitIdx){
    int currentIndex = 0;
    while(currentIndex < digitIdx){
        num /= 10;
        currentIndex++;
    }
    int digitAtIdx = num % 10;
    return digitAtIdx;
    
    // Another option is to write it with a for loop.
    // for(int currentIndex = 0; currentIndex < digitIdx; currentIndex++){
    //     num /= 10;
    // }
    // int digitAtIdx = num % 10;
    // return digitAtIdx;
}
