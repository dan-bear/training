/**
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii
 * #dp #DP 
 */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        ///dpApproach(prices);

        ///Best day to buy and purchase single stock without
        ///dp.

        ///In the first day, the maxProfit is 0 and the minimal 
        ///price for buying a stock is the price inthe first day.
        ///
        ///After the first day, if the next two parameters are known:
        ///1: minPrice till today (not including).
        ///2: maxProfit till today (not including).
        ///The maxProfit is max(maxProfit till today, 
        ///                     price today - minPrice till today) 
        ///
        ///So the maxProfit update rule is know, the minBuy update
        ///rule is just min(today price, minBuy till today (not including)).
        ///
        
        // int maxProfit = 0;
        // int minBuy = prices[0];
        // for(int idx = 1; idx < prices.size(); idx++){
        //     maxProfit = max(maxProfit, prices[idx] - minBuy);
        //     minBuy = min(minBuy, prices[idx]);    
        //
        
        ///How to generalize it to two stocks?
        ///The maxProfit of one stock is calculated the same way.
        ///At each day, it's possible to get the maxProfit till
        ///this day and in the next day to use that money to
        ///purchase the stock, to the effective price of the
        ///second stock at a given day, it the minimal between
        ///the price of the second stock in the day before
        ///and the the price today - the profit from selling
        ///the stock in the previous day.
        int maxProfit1 = 0;
        int minBuy1 = prices[0];
        int maxProfit2 = 0;
        int minBuy2 = prices[0] - maxProfit1;
        for(int idx = 1; idx < prices.size(); idx++){
            maxProfit1 = max(maxProfit1, prices[idx] - minBuy1);
            maxProfit2 = max(maxProfit2, prices[idx] - minBuy2);  

            ///Updating for next day:
            minBuy1 = min(minBuy1, prices[idx]);
            ///If the stock is bought today, the minimal buying
            ///price depends on today price - the maximal profit.
            ///reached till today.
            minBuy2 = min(minBuy2, prices[idx] - maxProfit1);
        }
        return maxProfit2;
    }
private:
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
    int dpApproach(const vector<int>& prices){
        vector<int> dpTable = createDpTable(prices);
        vector<int> epTable = createEpTable(prices);
        int res = calcMaxProfit(dpTable, epTable);
        return res;
    }

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
