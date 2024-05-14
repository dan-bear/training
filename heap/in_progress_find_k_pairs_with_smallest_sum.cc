/**
 * #heap
 * https://leetcode.com/problems/find-k-pairs-with-smallest-sum
 */
class Solution {
public:
   
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        auto cmp = [](const vector<int>& pair1, const vector<int>& pair2){
            return pair1[0] + pair1[1] > pair2[0] + pair2[1];
            };

        priority_queue<vector<int>, 
                   vector<vector<int>>,
                   decltype(cmp)> pairsMinHeap(cmp);
    
        vector<vector<int>> res;
        ///The templatedd type is: elements type, container type, compare func).
        int idx = 0;
        int jdx = 0;
        int jdxMaxVal = min(k, static_cast<int>(nums2.size())) - 1;
        int idxMaxVal = min(k, static_cast<int>(nums1.size())) - 1;
        pushKPairsToHeap(nums1, nums2, k, pairsMinHeap, idx, jdx);
        //cout << "idx = " << idx << " jdx = " << jdx << "\n";
        //cout << "pushed\n";
        while(res.size() < k){
            res.push_back(pairsMinHeap.top());
            pairsMinHeap.pop();
            if(idx <= idxMaxVal && jdx <= jdxMaxVal){
                pairsMinHeap.push(vector<int>({nums1[idx], nums2[jdx]}));
            }
            
            //cout << "res.size() = " << res.size() << "\n";
            moveToNextPair(idx, jdx, jdxMaxVal);
            //cout << "idx = " << idx << " jdx = " << jdx << "\n";
        }
        return res;
    }
private:
    
    void moveToNextPair(int& idx, int& jdx, int jdxMaxVal){
        if(jdx < jdxMaxVal){
            jdx++;
        }else{
            jdx = 0;
            idx++;
        }
    }

    void pushKPairsToHeap(const vector<int>& nums1, const vector<int>& nums2,
                          int k, auto& pairsMinHeap, int& idx, int& jdx){
        int count = 0;
        int jdxMaxVal = min(k, static_cast<int>(nums2.size())) - 1;
        while(count < k){
            pairsMinHeap.push(vector<int>({nums1[idx], nums2[jdx]}));
            count++;
            //cout << "push_pairs: idx = " << idx << " jdx = " << jdx << "\n";
            moveToNextPair(idx, jdx, jdxMaxVal);                
        }
    }
};
