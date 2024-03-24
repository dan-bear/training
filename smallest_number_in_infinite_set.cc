/**
 * https://leetcode.com/problems/smallest-number-in-infinite-set
 * #heap #min_heap
 */
class SmallestInfiniteSet {
private:
    vector<int> m_minHeap;
    int m_minVal{1};
    static bool sReverseOrderComp(int x, int y){return x > y;}

public:
    SmallestInfiniteSet() {
    }
    
    int popSmallest() {
        int res = 0;
        if(m_minHeap.empty()){
            res = m_minVal;
            m_minVal++;
        }else{
            res = m_minHeap.front();
            pop_heap(m_minHeap.begin(), 
                     m_minHeap.end(), 
                     sReverseOrderComp);
            m_minHeap.pop_back();
        }
        return res;
    }
    
    void addBack(int num) {
        if(num < m_minVal && 
           find(m_minHeap.begin(), m_minHeap.end(), num)
                == m_minHeap.end()){
            m_minHeap.push_back(num);
            push_heap(m_minHeap.begin(), m_minHeap.end(), sReverseOrderComp);
        }
    }
};

/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet* obj = new SmallestInfiniteSet();
 * int param_1 = obj->popSmallest();
 * obj->addBack(num);
 */
