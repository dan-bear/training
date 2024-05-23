/**
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii
 * #array
 */
class Solution {
public:
    /**
     * A dp algorithm
     * What the same day gives us?
     * 3 2 0 : If you can sell-buy and buy-sell in the same day,
     *         there is no difference between:
     *         1: Buy on day[0], sell on day[2]
     *         2: Buy on day[0], sell on day[1], buy on day[1], sell on day[2].
     *         However if one can make a single transaction every day,
     *         the only way to get the max profit is by buing on day[0]
     *         and sell on day[2].
     */
    int maxProfit(vector<int>& prices) {
        int profit = 0;
        int diff = 0;
        for(int dayIdx = 1; dayIdx < prices.size(); dayIdx++){
            diff = prices[dayIdx] - prices[dayIdx - 1];
            if(diff > 0){
                profit += diff;
            }
        }
        return profit;
        
        
        /**
         * Dp solution that does not use the buy-sell, sell-buy on the same
         * day ability.
         */
        // vector<vector<int>> dp(skNumOfStates, vector<int>(prices.size(), 0));
        // int dayIdx = 0;
        // dp[skStockHeld][dayIdx] = -1 * prices[0];
        // dp[skNoStock][dayIdx] = 0;

        // for(dayIdx = 1; dayIdx < prices.size(); dayIdx++){
        //     dp[skStockHeld][dayIdx] = 
        //         max(dp[skNoStock][dayIdx - 1] - prices[dayIdx]/*Buy today*/,
        //             dp[skStockHeld][dayIdx - 1]/*Dont sell today*/);
        //     dp[skNoStock][dayIdx] =
        //         max(dp[skStockHeld][dayIdx - 1] + prices[dayIdx]/*Sell today*/,
        //             dp[skNoStock][dayIdx - 1]/*Dont buy today*/);
        // }
        // ///Note, that the stock might be
        // return dp[skNoStock][prices.size() - 1];
    }
private:
    static constexpr int skStockHeld{0};
    static constexpr int skNoStock{1};
    static constexpr int skNumOfStates{2};
};
