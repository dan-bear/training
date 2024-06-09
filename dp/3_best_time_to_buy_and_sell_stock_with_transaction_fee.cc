/**
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee
 * #dp #DP
 */
class Solution {
public:
    /**
     * At each day you can be in one of two states:
     * 1: Holding a stock
     * 2: Not holding a stock.
     * When moving from not-holding a stock to holding a stock, one has
     * to pay today's stock price and a fee.
     * When moving from holding a stock to not-holding a stock, one
     * gets today's price minus a fee.
     * dp[i][0] = max profit such that at day i, a stock is held.
     * dp[i][1] = max profit such that at day i, a stock is not held.
     * the result is dp[numOfDays][1]
     * dp[0][0] = - fee - price[0]
     * dp[0][1] = 0
     * dp[i][0] = max(dp[i - 1][1] - fee - price[i] (buy today, pay the fee),
     *                dp[i - 1][0] (do nothing today))
     * dp[i][1] = max(dp[i - 1][0] + price[i] (sell today),
     *                dp[i - 1][1] (do nothing today))
     */
    using State = array<int, 2>;
    int maxProfit(vector<int>& prices, int fee) {
        vector<State> dp(prices.size(), State({0, 0}));
        dp[0][0] = (-1 * fee) - prices[0];
        for(int dayIdx = 1; dayIdx < prices.size(); dayIdx++){
            dp[dayIdx][0] = max(dp[dayIdx - 1][1] - fee - prices[dayIdx],
                                dp[dayIdx - 1][0]);
            dp[dayIdx][1] = max(dp[dayIdx - 1][0] + prices[dayIdx],
                                dp[dayIdx - 1][1]);
        }
        return dp[prices.size() - 1][1];

        ///I think this version should be slower, since the cache access
        ///is less local (the distance between dp[0][i] and dp[1][i] is greater).
        // vector<vector<int>> dp(2, vector<int>(prices.size(), 0));
        // dp[0][0] = (-1 * fee) - prices[0];
        // for(int dayIdx = 1; dayIdx < prices.size(); dayIdx++){
        //     dp[0][dayIdx] = max(dp[1][dayIdx - 1] - fee - prices[dayIdx],
        //                         dp[0][dayIdx - 1]);
        //     dp[1][dayIdx] = max(dp[0][dayIdx - 1] + prices[dayIdx],
        //                         dp[1][dayIdx - 1]);
        // }
        // return dp[1][prices.size() - 1];
    }
};
