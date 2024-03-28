/**
 * https://leetcode.com/problems/total-cost-to-hire-k-workers
 * #heap #min_heap
 */
class Solution {
public:
    ///min heap of left candidate.
    ///min heap of right candidate.
    ///compare the min in each heap.
    ///break ties and if it's the same candidate
    ///(due to intersection) remove from both sides.

    long long totalCost(vector<int>& costs, int k, int candidates) {
        vector<int> leftMinHeap = initLeftMinHeap(costs, candidates);
        vector<int> rightMinHeap = initRightMinHeap(costs, candidates);
        int frontIdx = leftMinHeap.size();
        int backIdx = costs.size() - 1 - rightMinHeap.size();
        long long hireCost = 0;
        for(int hireIdx = 0; hireIdx < k; hireIdx++){
            hireCost += hire(costs, leftMinHeap, rightMinHeap, frontIdx, backIdx); 
        }
        return hireCost;
    }

private:
    long long hire(const vector<int>& costs,
                   vector<int>& leftMinHeap,
                   vector<int>& rightMinHeap,
                   int& frontIdx,
                   int& backIdx){
        long long res = 0;
        if(rightMinHeap.empty() && leftMinHeap.empty()){
            res = 0;
        }else if(rightMinHeap.empty()){
            res = hireFromLeftMinHeap(costs, leftMinHeap, frontIdx, backIdx);
        }else if(leftMinHeap.empty()){
            res = hireFromRightMinHeap(costs, rightMinHeap, frontIdx, backIdx);
        }else if(leftMinHeap.front() <= rightMinHeap.front()){
            res = hireFromLeftMinHeap(costs, leftMinHeap, frontIdx, backIdx);
        }else{
            res = hireFromRightMinHeap(costs, rightMinHeap, frontIdx, backIdx);
        }
        return res;
    }

    long long hireFromLeftMinHeap(const vector<int>& costs,
                   vector<int>& leftMinHeap,
                   int& frontIdx,
                   int& backIdx){
        long long res = leftMinHeap.front();
        minHeapPop(leftMinHeap);
        if(frontIdx <= backIdx){
            minHeapPush(leftMinHeap, costs[frontIdx]);
            frontIdx++;
        }
        return res;
    }


    long long hireFromRightMinHeap(const vector<int>& costs,
                   vector<int>& rightMinHeap,
                   int& frontIdx,
                   int& backIdx){
        long long res = rightMinHeap.front();
        minHeapPop(rightMinHeap);
        if(frontIdx <= backIdx){
            minHeapPush(rightMinHeap, costs[backIdx]);
            backIdx--;
        }
        return res;
    }

    vector<int> initLeftMinHeap(const vector<int>& costs, int cands){
        vector<int> leftMinHeap;
        bool bIsRightSide = false;
        int numOfCosts = calcNumOfCostsInHeap(costs.size(), cands, bIsRightSide);
        for(int idx = 0; idx < numOfCosts; idx++){
            minHeapPush(leftMinHeap, costs[idx]);
        }
        return leftMinHeap;
    }

    vector<int> initRightMinHeap(const vector<int>& costs, int cands){
        vector<int> rightMinHeap;
        bool bIsRightSide = true;
        int numOfCosts = calcNumOfCostsInHeap(costs.size(), cands, bIsRightSide);
        for(int idx = 0; idx < numOfCosts; idx++){
            minHeapPush(rightMinHeap, costs[(costs.size() - 1) - idx]);
        }
        return rightMinHeap;
    }

    int calcNumOfCostsInHeap(int costsSize, int cands, bool bIsRightSide){
        int numOfCosts = 0;
        if(costsSize / 2 >= cands){
            numOfCosts = cands;
        }else{
            if(costsSize % 2 == 0 || bIsRightSide){
                numOfCosts = costsSize / 2;
            }else{
                numOfCosts = costsSize / 2 + 1;
            }
        }
        return numOfCosts;
    }


    void minHeapPush(vector<int>& minHeap, int val){
        minHeap.push_back(val);
        push_heap(minHeap.begin(), minHeap.end(),
                  [](int x, int y){return x > y;});
    }

    void minHeapPop(vector<int>& minHeap){
        pop_heap(minHeap.begin(), minHeap.end(),
                 [](int x, int y){return x > y;});
        minHeap.pop_back();
    }
};
