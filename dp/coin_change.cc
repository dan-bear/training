/**
 * https://leetcode.com/problems/coin-change
 * #dp #DP
 */
class Solution {
public:
    /**
     * Edge cases:
     * 1: summing up coins exceeds int max val (int overflow).
     * 2: The coins vector is empty.
     * 3: The amount is 0 => in this case 0 coins are needed.
     * 
     * Algorithmm:
     * dp[i] the minimum number of coins needed to
     * reach amount = i.
     * dp[0] = 0.
     * dp[i] is initialized with (amount + 1) for every 1 <= i <= amount.
     * (It helps to reduce the number of branching during the iteration).
     * dp[i] = for coin in coins:
     *             if coin <= i: 
     *                 dp[i] = min(1 + dp[i - coin], dp[i])
     *             ///Note: if coin == i, dp[i - coin] = dp[0] = 0.
     * the result is in dp[amount] if dp[amount] <= amount else -1.
     * 
     * To optimize the memory, the number of dp cells is
     * min(max(coins), amount + 1). Since the algorithm 
     * never looks back more than max(coins) cells (to avoid
     * memory copy, modulo arithmetic can be used).
     * 
     * Note: this algorithm is incorrect in case coins 
     *       might be negative.
     */
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for(int val = 1; val <= amount; val++){
            for(int coin : coins){
                if(val >= coin){
                    dp[val] = min(dp[val], dp[val - coin] + 1);
                }
            }
        }
        return dp[amount] <= amount ? dp[amount] : -1;
    }
};
