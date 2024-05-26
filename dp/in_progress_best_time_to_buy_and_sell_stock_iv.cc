/**
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv
 * #dp #DP
 */
class Solution {
public:
    /** 
     * The previous profits are used (embodied) to decrease the 
     * stock prices. So, the way to update the minBuyPrice is: 
     * minBuy[transIdx = 0] = min(minBuy[0], prices[dayIdx] - 0)
     * buy[transIdx = 1] = min(minBuy[1], prices[dayIdx] - maxProfits[0])
     * buy[transIdx = 2] = min(minBuy[2], prices[dayIdx] - maxProfits[1]))
     * buy[transIdx = k - 1] = min(minBuy[k - 1], 
     *                             prices[dayIdx] - maxProfits[k - 2])
     * The max profit update rule stays the same:
     * maxProfit[transIdx] = 
     *     max(maxProfit[transIdx], prices[dayIdx] - minBuy[transIdx]).
     */
    int maxProfit(int k, vector<int>& prices) {
        ///Note: to avoid the edge case of:
        ///      minBuyPrice[0] = 
        ///          min(minBuyPrice[0], prices[0] - maxProfits[0 - 1])
        ///      minBuyPrices and maxProfits size is k + 1 and their first
        ///      element is set to prices[0] and 0 respectively.
        vector<int> minBuyPrices(k + 1, prices[0]);
        vector<int> maxProfits(k + 1, 0);
        int numOfDays = prices.size();
        for(int dayIdx = 1; dayIdx < numOfDays; dayIdx++){
            for(int transIdx = 1; transIdx <= k; transIdx++){   
                maxProfits[transIdx] =  
                    max(maxProfits[transIdx], 
                        prices[dayIdx] - minBuyPrices[transIdx]);

                minBuyPrices[transIdx] =
                    min(minBuyPrices[transIdx], 
                        prices[dayIdx] - maxProfits[transIdx - 1]);
            }
        }
        return maxProfits[k];
    }    
};
