/**
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee
 * #dp #DP
 */
class Solution {
public:
    
    ///Each day a position might be holding or stock or not holding
    ///a stock. Define dp[i][holdingStock] best profit from day 0 to day i
    ///in case a stock is held on day i. dp[i][notHolding] is the best
    ///profit from day 0 to day i in case the stock is not held on day i.
    ///
    ///dp[i][holding] = 
    ///     - it's possible that I bought the stock today
    ///       if so I need to pay the price + fee, so 
    ///       the profit so far is, dp[i-1][notHoldingStock] - price - fee.
    ///     - it's possible that I did not buy it today, that I just hold it.
    ///       so dp[i][holding] = dp[i-1][holding]
    ///     - dp[i][holding] = max(dp[i-1][holding], dp[i-1][notHolding] - price[i] - fee).
    ///
    ///dp[i][notHolding] = 
    ///     - Was not holding anything the last day.
    ///       dp[i][notHolding] = dp[i - 1][notHolding]
    ///     - Selling today the stock I bought in some previous day.
    ///       dp[i][notHolding] = dp[i - 1][holding] + price[i]
    ///
    ///dp[0][holding] = buying today = -price[i] - fee.
    ///dp[0][notHolding] = 0.
    ///
    enum class Holding : int{
        kYes,
        kNo,
        kValuesNum
    };

    int maxProfit(vector<int>& prices, int fee) {
        int notHolding = 0;
        int holding = 1;
        int numOfPositions = 2;
        vector<vector<int>>dp(prices.size(), vector<int>(numOfPositions, 0));

        dp[0][holding] -= (prices[0] + fee);
        for(int idx = 1; idx < prices.size(); idx++){
            dp[idx][holding] =
             max(dp[idx - 1][holding],
                 dp[idx - 1][notHolding] - prices[idx] - fee);
            
            dp[idx][notHolding] =
             max(dp[idx - 1][notHolding],
                 dp[idx - 1][holding] + prices[idx]);
        }
        return max(dp[prices.size() - 1][notHolding],
                   dp[prices.size() - 1][holding]);
    }
};
