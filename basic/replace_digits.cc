
// Note: I decided to do it without additional power fuction
// to make it as simple as possible for beginner, But an
// additioal version with a pow function appears below.
int replaceDigits(int num, int digitIdx1, int digitIdx2){
    int currDigitIdx = 0;
    int newNum = 0;
    while(num != 0){
        int currentDigit = num % 10;
        int tenPower = 0;  
        if(currDigitIdx == digitIdx1){
            tenPower = digitIdx2;   
        }else if(currentDigitIdx == digitIdx2){
            tenPower = digitIdx1;
        }else{
            tenPower = currentDigitIdx;
        }

        int tenMultiply = 1;
        while(tenPower > 0){
            tenMultiply *= 10;
            tenPower--;
        }

        newNum += (currentDigit * tenMultiply);
        currentDigitIdx++;
        num /= 10;
    }
    return newNum;
}
// Another version with pow function.
// int myPow(int base, int exponent){
//     int result = 1;
//     int multIdx = 0;
//     while(multIdx < exponent){
//         result *= base;
//     }
//     return result;
//     // for loop style.
//     // int result = 1;
//     // for(int multIdx = 0; multIdx < exponent; multIdx++){
//     //     result *= base;
//     // }
//     // return result;
// }


// int replaceDigits(int num, int digitIdx1, int digitIdx2){
//     int currDigitIdx = 0;
//     int newNum = 0;
//     while(num != 0){
//         int currentDigit = num % 10;
//         int tenMultiply = 0;
//         if(currDigitIdx == digitIdx1){
//             tenMultiply = myPow(10, digitIdx2);   
//         }else if(currentDigitIdx == digitIdx2){
//             tenMultiply = myPow(10, digitIdx1));
//         }else{
//             tenMultiply = myPow(10, currentDigitIdx));
//         }
        
//         newNum += (currentDigit * tenMultiply);
//         currentDigitIdx++;
//         num /= 10;
//     }
//     return newNum;
// }








