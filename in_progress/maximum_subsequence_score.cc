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
     /// order = [{2,4}, {3,3}, {1,2}, {3,1}]
     ///If k = 3.
     ///when {1,2} is reached, it's known that 2 is
     ///is the smallest, because of the decending
     ///order, so it's easy to calculate the first
     ///result.
     ///What's the next step? one of the pairs needs
     ///to be removed, the greedy solution is to
     ///remove the pair with the smallest nums1 element.
     ///since the next pair is about to contain a pair
     ///satisfying that the nums2 element is smaller than
     ///the smallest nums2 element in the current triplet.
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<pair<u64, u64>> zipped = zip(nums1, nums2);
        sortPairsInSecondElementDescendingOrder(zipped);
        u64 result = 0;
        vector<u64> firstElemsMinHeap;
        
        u64 heapSum = 0;
        for(int pairIdx = 0; pairIdx < k - 1 ; pairIdx++){
            heapSum += zipped[pairIdx].first;
            firstElemsMinHeap.push_back(zipped[pairIdx].first);
            push_heap(firstElemsMinHeap.begin(),
                      firstElemsMinHeap.end(),
                      [](u64 x, u64 y){return x > y;});
        }

        for(int pairIdx = k - 1; pairIdx < zipped.size(); pairIdx++){
            heapSum += zipped[pairIdx].first;
            firstElemsMinHeap.push_back(zipped[pairIdx].first);
            push_heap(firstElemsMinHeap.begin(),
                      firstElemsMinHeap.end(),
                      [](u64 x, u64 y){return x > y;});
            
            // u64 currVal = 0;
            // for(int idx = 0; idx < k ; idx++){
            //     currVal += firstElemsMinHeap[idx];
            // }
            u64 currVal = heapSum * zipped[pairIdx].second;

            // long long currVal = accumulate(firstElemsMinHeap.begin(),
            //                                firstElemsMinHeap.end(),
            //                                0) * p.second; 
            result = max(currVal, result);

            ///remove the minimal element from the heap.
            pop_heap(firstElemsMinHeap.begin(),
                     firstElemsMinHeap.end(),
                     [](u64 x, u64 y){return x > y;});    
            
            heapSum -= firstElemsMinHeap.back();
            firstElemsMinHeap.pop_back();
        }
        
        return result;
    }

private:
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
