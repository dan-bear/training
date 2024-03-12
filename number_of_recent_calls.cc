/** 
 * https://leetcode.com/problems/number-of-recent-calls
 * #queue
 */
class RecentCounter {
public:
    RecentCounter() {}

    int ping(int t) {
        m_pingTimes.push(t);
        while(m_pingTimes.front() + skTimeInterval < t){
            m_pingTimes.pop();
        }
        return m_pingTimes.size();
    }
private:
    queue<int> m_pingTimes;
    static constexpr int skTimeInterval{3000};
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
