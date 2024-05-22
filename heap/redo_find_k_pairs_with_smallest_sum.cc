/**
 * #heap
 * https://leetcode.com/problems/find-k-pairs-with-smallest-sum
 *
 * Simplest algorithm:
 * 1: create all pairs from nums1 and nums2.
 * 2: sort the pairs based on the sum  attribute.
 * 3: Add the first k elements to the result vector and returnn it.
 * Time and space complexity:
 * (nums1.size() * nums2.size()) * log(nums1.size() * nums2.size())
 *
 * More efficient algorithm:
 * In general, use the fact that nums1 nums2 are sorted, such that
 * at any given iteration you can maintain a set of K pairs,
 * choose the smallest one and then add the next pair to the set.
 *
 * How to choose the smallerst K pair in the first place using
 * the fact that nums are sorted?
 * 
 * 
 * 1: Start with the pairs (i, 0) for i in
 *    range(0, min(k, nums1.size())) and add them to a min-heap.
 *    Note: at this point, for every pair (i, j) the min-heap 
 *          hold a pair (i + 1, 0) <= (i + 1, j).
 *          so there is no point in adding (i + 1, j) to the
 *          heap. But it's possible that (i, j + 1) is a 
 *          smaller pair than the ones already in the heap.
 * 3: repeat k times:
 *     3.1: pick the minimal index pair: (i, j).
 *     3.2: remove it from the heap.
 *     3.3: add (nums1[i], nums2[j]) to the result.
 *     3.4: if j < min(k, nums2.size()) - 1, add (i, j + 1) to
 *          the heap.
 */
class Solution {
private:
    priority_queue<vector<int>, vector<vector<int>>,
                   bool (*)(const vector<int>&, const vector<int>&)>
                   minHeap{Solution::sCmp};

    static bool sCmp(const vector<int>& idxPairAndSum1,
                     const vector<int>& idxPairAndSum2){
        return idxPairAndSum1[2] > idxPairAndSum2[2];
    }
    
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {

        int maxIdx1 = min(static_cast<unsigned long>(k), nums1.size() - 1);
        int maxIdx2 = min(static_cast<unsigned long>(k), nums2.size() - 1);
        
        for(int idx = 0; idx <= maxIdx1; idx++){
            minHeap.push(vector<int>({idx, 0, nums1[idx] + nums2[0]}));
        }

        vector<vector<int>> res;
        for(int _ = 0; _ < k; _++){
            const vector<int> pairAndSum = minHeap.top();
            minHeap.pop();

            res.push_back(
                vector<int>({nums1[pairAndSum[0]], nums2[pairAndSum[1]]}));
            
            if(pairAndSum[1] < maxIdx2){
                minHeap.push(vector<int>({pairAndSum[0],
                                          pairAndSum[1] + 1,
                                          nums1[pairAndSum[0]] +
                                          nums2[pairAndSum[1] + 1]}));
            }
        }
        return res;
    }   
};
