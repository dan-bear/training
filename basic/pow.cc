int myPow(int base, int exponent){
    int result = 1;
    while(exponent > 0){
        result *= base;
        exponent--;
    }
    return result;
    // for loop style.
    // int result = 1;
    // for(int multIdx = 0; multIdx < exponent; multIdx++){
    //     result *= base;
    // }
    // return result;
}
