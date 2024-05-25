/**
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii
 * #dp #DP 
 */
class Solution {
public:
    /**
     * dp[i] = max profit in days 0 to i.
     * dp[0] = 0;
     * dp[1] = max(0, price[1] - price[0]).
     * dp[2] = max(dp[1], prices[2] - min(prices[0 : 2])).
     * dp[i] = max(dp[i - 1], prices[i] - min(prices[0 : i])).
     *
     * ep[i] = max profit in days i to n - 1.
     * ep[n - 1] = 0
     * ep[n - 2] = max(ep[n - 1], max(prices[n - 2 + 1, n]) - prices[n - 2])
     * ep[i] = max(ep[i + 1], max(prices[i + 1, n]) - prices[i])
     *
     * maxProfit = max(max(dp[i] + ep[i + 1] : for i in range 0 : n - 2), dp[n - 1])
     */
    int maxProfit(vector<int>& prices) {
        vector<int> dpTable = createDpTable(prices);
        vector<int> epTable = createEpTable(prices);
        int res = calcMaxProfit(dpTable, epTable);
        return res;
    }
private:
    int calcMaxProfit(const vector<int>& dpTable, const vector<int>& epTable){
        int maxProfit = dpTable[dpTable.size() - 1];
        for(int idx = 0; idx < dpTable.size() - 1; idx++){
            maxProfit = max(maxProfit, dpTable[idx] + epTable[idx + 1]);
        }
        return maxProfit;
    }



    vector<int> createDpTable(const vector<int>& prices){
        vector<int> minTillDayIdx = calcMinTillIdx(prices);
        vector<int> dpTable(prices.size(), 0);
        for(int dayIdx = 1; dayIdx < prices.size(); dayIdx++){
            dpTable[dayIdx] = max(dpTable[dayIdx - 1], 
                                  prices[dayIdx] - minTillDayIdx[dayIdx - 1]);
        }
        return dpTable;
    }

    vector<int> createEpTable(const vector<int>& prices){
        vector<int> maxFromDayIdx = calcMaxFromIdx(prices);
        vector<int> epTable(prices.size(), 0);
        for(int dayIdx = prices.size() - 2; dayIdx >= 0; dayIdx--){
            epTable[dayIdx] = max(epTable[dayIdx + 1], 
                                  maxFromDayIdx[dayIdx + 1] - prices[dayIdx]);
        }
        return epTable;
    }


    vector<int> calcMinTillIdx(const vector<int>& nums){
        vector<int> minTillIdx(nums.size(), 0);
        minTillIdx[0] = nums[0];
        for(int idx = 1; idx < nums.size(); idx++){
            minTillIdx[idx] = min(nums[idx], minTillIdx[idx - 1]);
        }
        return minTillIdx;
    }

    vector<int> calcMaxFromIdx(const vector<int>& nums){
        vector<int> maxFromIdx(nums.size(), 0);
        int lastIdx = nums.size() - 1;
        maxFromIdx[lastIdx] = nums[lastIdx];
        for(int idx = lastIdx - 1; idx >= 0; idx--){
            maxFromIdx[idx] = max(nums[idx], maxFromIdx[idx + 1]);
        }
        return maxFromIdx;
    }

};
