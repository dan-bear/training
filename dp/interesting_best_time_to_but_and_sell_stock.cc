/**
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
 * #dp #DP
 */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minBuy = prices[0];
        int maxProfit = 0;
        for(int dayIdx = 1; dayIdx < prices.size(); dayIdx++){
            maxProfit = max(maxProfit, prices[dayIdx] - minBuy);
            ///update minBuy for next day.
            minBuy = min(minBuy, prices[dayIdx]);
        }
        return maxProfit;
    }
};
