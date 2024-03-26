/**
 * https://leetcode.com/problems/maximum-subsequence-score
 * #heap #sort
 */
using u64 = long long;
class Solution {
public:
     /// num1 = [1, 3, 3, 2]
     /// num2 = [2, 1, 3, 4]
     /// pairs = [{1,2}, {3,1}, {3,3}, {2,4}]
     /// ordered by nums2 element in descending order:
     /// = [{2,4}, {3,3}, {1,2}, {3,1}]
     /// k = 3.
     /// when {1,2} is reached, it's known that 2 is
     /// is the smallest, because of the decending
     /// order, so it's easy to calculate the first
     /// result.
     /// What's the next step? one of the pairs needs
     /// to be removed, the pair with the minimal nums1
     /// element should be the one to remove since the
     /// target is the maximal value.
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<pair<u64, u64>> zipped = zip(nums1, nums2);
        sortPairsInSecondElementDescendingOrder(zipped);
        return maxStoreFromOrderedPairs(zipped);
    }

private:
    u64 maxScoreFromOrderedPairs(const vector<u64, u64>& pairs){
        u64 result = 0;
        vector<u64> firstElemsMinHeap;
        u64 heapSum = 0;
        for(const pair<u64, u64>& p : pairs){
            heapSum += p.first;
            minHeapPush(firstElemsMinHeap, p.first);
            if(firstElemsMinHeap.size() == k){
                result = max(heapSum * p.second, result);
                heapSum -= firstElemsMinHeap.front();
                minHeapPop(firstElemsMinHeap);    
            }
        }
        return result;
    }

    void minHeapPush(vector<u64>& minHeap, u64 val){
        minHeap.push_back(val);
        push_heap(minHeap.begin(),
                  minHeap.end(),
                  [](u64 x, u64 y){return x > y;});
    }

    void minHeapPop(vector<u64>& minHeap){
        pop_heap(minHeap.begin(),
                 minHeap.end(),
                 [](u64 x, u64 y){return x > y;});
        minHeap.pop_back();
    }

    vector<pair<u64, u64>> zip(const vector<int>& v1, const vector<int>& v2){
        vector<pair<u64, u64>> res;
        for(int idx = 0 ; idx < v1.size(); idx++){
            res.push_back({static_cast<u64>(v1[idx]),
                           static_cast<u64>(v2[idx])});
        }
        return res;
    }

    void sortPairsInSecondElementDescendingOrder(vector<pair<u64,u64>>& pairs){
        sort(pairs.begin(),
             pairs.end(),
             [](const pair<u64, u64>& p1, const pair<u64, u64>& p2){
                return p1.second > p2.second;
             });

        ///Another option using std ranges (From cpp20).
        // ranges::sort(pairs,
        //              [](const pair<u64, u64>& p1, const pair<u64, u64>& p2){
        //                 return p1.second > p2.second;
        //              });
    }
};


