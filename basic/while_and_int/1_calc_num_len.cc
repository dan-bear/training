int calcNumLength(int num){
    int length = 0;
    if(num == 0){
       length = 1;
    }else{
        while(num != 0){
            length += 1;
            num /= 10;
        }
    }
    return length;
}
