/**
 * https://leetcode.com/problems/max-number-of-k-sum-pairs
 * #hash #HASH #map #MAP #hash-map
 */
#include <map>
class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        unordered_map<int, int> histogram;
        fillHistogram(nums, histogram);
        int kPairs = countPairs(histogram, k);
        return kPairs;
        ///Another solution, that runs a little faster.
        //return singleFunctionSolution(nums, k);
    }
private:
    
    void fillHistogram(const vector<int>& nums, unordered_map<int, int>& histogram){
        for(int elem: nums){
            /// could have also used histogram.count(elem) == 0
            if(histogram.find(elem) == histogram.end()){
                histogram[elem] = 1;
            }else{
                histogram[elem]++;
            }   
        }
    }

    int countPairs(unordered_map<int, int>& histogram, int k){
        int pairsCount = 0;
        for(auto& [num, count] : histogram){
            if(num == k - num){
                pairsCount += (count / 2);
            }else{
                int complementNumCount = histogram.count(k - num) ? histogram[k - num] : 0;
                pairsCount += min(complementNumCount, count);
            }
            count = 0;//avoid double counting.
        }
        return pairsCount;
    }

    int singleFunctionSolution(const vector<int>& nums, int k){
        unordered_map<int, int> histogram;
        int opCount = 0;
        for(int idx = 0; idx < nums.size(); idx++){
            if(histogram.count(k - nums[idx]) && histogram[k - nums[idx]] > 0){
                ///pair with nums[idx].
                histogram[k - nums[idx]]--;    
                opCount++;
            }else{
                ///cannot pair nums[idx] now, but maybe later.
                if(histogram.count(nums[idx])){
                    histogram[nums[idx]]++;
                }else{
                    histogram[nums[idx]] = 1;
                }
            }
        }
        return opCount;
    }
};


