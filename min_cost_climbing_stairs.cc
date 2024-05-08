/**
 * https://leetcode.com/problems/min-cost-climbing-stairs
 * #dp #DP
 */
class Solution {
public:
    ///price[i] = minimal price to reach ith floor.
    ///price[0] = cost[0]
    ///price[1] = cost[1]
    ///price[2] = min(price[0], price[1]) + cost[2]
    ///price[k] = min(price[k - 1], [price[k - 2]]) + cost[k]
    int minCostClimbingStairs(vector<int>& cost) {
        vector<int> price(cost.size(), 0);
        price[0] = cost[0];
        price[1] = cost[1];
        for(int idx = 2; idx < price.size(); idx++){
            price[idx] = min(price[idx - 2], price[idx - 1]) + cost[idx];
        }
        return min(price[price.size() - 1], price[price.size() - 2]);

        ///another solution without additional price array
        // for(int idx = 2; idx < cost.size(); idx++){
        //     cost[idx] += min(cost[idx - 1], cost[idx - 2]);
        // }
        // return min(cost[cost.size() - 1], cost[cost.size() - 2]);
    }
};
