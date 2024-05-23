/**
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii
 * #array
 * Note: It's possible to buy-sell and sell-buy one the same day.
 *       that's an important detail.
 */
///SOLUTION
int maxProfit(int* prices, int pricesSize) {
    int profit = 0;
    int diff = 0;
    for(int dayIdx = 1; dayIdx < pricesSize; dayIdx++){
        diff = prices[dayIdx] - prices[dayIdx - 1];
        if(diff > 0){
            profit += diff;
        }
    }
    return profit;      
}
