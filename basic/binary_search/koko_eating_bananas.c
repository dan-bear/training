/**
 * https://leetcode.com/problems/koko-eating-bananas
 * #binary_search
 */
///SOLUTION
int upperVal(int val, int divisor);
int maxElem(int* arr, int len);
bool canEatAll(int* piles, int pilesSize, int hours, int eatRate);

int minEatingSpeed(int* piles, int pilesSize, int h) {
    int minEatRate = 1;
    int maxEatRate = maxElem(piles, pilesSize);
    int res = maxEatRate;
    while(minEatRate <= maxEatRate){
        int midEatRate = (minEatRate + maxEatRate) / 2;
        if(canEatAll(piles, pilesSize, h, midEatRate)){
            res = midEatRate;
            maxEatRate = midEatRate - 1;
        }else{
            minEatRate = midEatRate + 1;
        }
    }
    return res;
}


int upperVal(int val, int divisor){
    int ceilAddition = val % divisor == 0 ? 0 : 1;
    int res = (val / divisor) + ceilAddition;
    return res;
}

int maxElem(int* arr, int len){
    int max = arr[0];
    for(int idx = 0; idx < len; idx++){
        max = max < arr[idx] ? arr[idx] : max;
    }
    return max;
}

bool canEatAll(int* piles, int pilesSize, int hours, int eatRate){
    int timeToEat = 0;
    for(int pileIdx = 0;
        pileIdx < pilesSize && timeToEat <= hours;
        pileIdx++){
        
        timeToEat += upperVal(piles[pileIdx], eatRate);
    }
    return timeToEat <= hours;
}
