/**
 * https://leetcode.com/problems/can-place-flowers
 * #arrays #arr
 */
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int numOfFlowers = 0;
        for(int idx = 0 ; idx < flowerbed.size(); idx++){
            if(flowerbed[idx] == 0){
                if(idx == 0){
                    if((flowerbed.size() > 1 && flowerbed[idx + 1] == 0) || flowerbed.size() == 1){
                        numOfFlowers += 1;
                        flowerbed[0] = 1;
                    }
                }else if(idx == flowerbed.size() - 1 && flowerbed[idx - 1] == 0){
                    //note that idx - 1 exists otherwise it means idx = 0 and array
                    //size is 1, that was already checked in the previous condition.
                    numOfFlowers += 1;
                    flowerbed[idx] = 1;
                }else if(flowerbed[idx - 1] == 0 && flowerbed[idx + 1] == 0){
                    numOfFlowers += 1;
                    flowerbed[idx] = 1;
                }
            }
        }
        return numOfFlowers >= n;
    }
};
