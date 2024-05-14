/**
 * #https://leetcode.com/problems/online-stock-span
 * #stack #STACK
 */
class StockSpanner {
public:
    StockSpanner() {
        
    }
    
    ///Simplest solution:
    // int next(int price) {
    //     int count = 0;
    //     for(vector<int>::reverse_iterator rItr = m_prices.rbegin(); 
    //         rItr != m_prices.rend();
    //         rItr++){
    //             if(*rItr <= price){
    //                 count++;
    //             }else{
    //                 break;
    //             }
    //     }
    //     int res = count + 1;
    //     m_prices.push_back(price);
    //     return res; 
    // }

    ///An optimized solution:
    int next(int price){
        int span = 1;
        while(!m_pricesAndSpans.empty() &&
               m_pricesAndSpans.top().first <= price){
            ///Accumulate the span since it's consecutive.
            span += m_pricesAndSpans.top().second;
            m_pricesAndSpans.pop();
        }
        m_pricesAndSpans.push(pair<int,int>(price, span));
        return span;
    }

private:
    vector<int> m_prices;
    stack<pair<int, int>> m_pricesAndSpans;
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */
