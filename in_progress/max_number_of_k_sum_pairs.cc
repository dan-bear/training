/**
 * https://leetcode.com/problems/max-number-of-k-sum-pairs
 * #hash #HASH #map #MAP #hash-map
 */
#include <map>
class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        // unordered_map<int, int> histogram;
        // fillHistogram(nums, histogram);
        // int kPairs = countPairs(histogram, k);
        // return kPairs;
        return otherSolution(nums, k);
    }
private:
    int otherSolution(const vector<int>& nums, int k){
        unordered_map<int, int> histogram;
        int opCount = 0;
        for(int idx = 0; idx < nums.size(); idx++){
            if(histogram.find(k - nums[idx]) != histogram.end()){
                if(histogram[k - nums[idx]] > 0){
                    histogram[k - nums[idx]]--;    
                    opCount++;
                }
            }else{
                if(histogram.find(nums[idx]) != histogram.end()){
                    histogram[nums[idx]]++;
                }else{
                    histogram[nums[idx]] = 1;
                }
            }
        }
        return opCount;
    }


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
};


