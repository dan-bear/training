/**
 * https://leetcode.com/problems/koko-eating-bananas
 * #binary_search
 */
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int minEatRate = 1;
        int maxEatRate = ranges::max(piles);
        int res = maxEatRate;
        while(minEatRate <= maxEatRate){
            int midEatRate = (minEatRate + maxEatRate) / 2;
            if(canEatAll(piles, h, midEatRate)){
                res = midEatRate;
                maxEatRate = midEatRate - 1;
            }else{
                minEatRate = midEatRate + 1;
            }
        }
        return res;
    }

private:
    bool canEatAll(const vector<int>& piles, int hours, int eatRate){
        unsigned int timeToEat = 0;
        for(int pileSize : piles){
            timeToEat += static_cast<unsigned int>(ceil(pileSize, eatRate));
        }
        return timeToEat <= static_cast<unsigned int>(hours);
    }

    int ceil(int val, int divisor){
        int ceilAddition = val % divisor == 0 ? 0 : 1;
        int res = (val / divisor) + ceilAddition;
        return res;
    }

};
