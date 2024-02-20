/**
 *
 */

class Solution {
public:
    
    /**
     * Note: the best solution in my idea is to:
     * 1: calculate the sum of 1, 2, ... , nums.size() 
     *    using arithmetic sequence sum formula.
     * 2: Sum the element in the given nums vector.
     * 3: The missing number is the difference between
     *    the sum in step 1 and the sum in step 2.
     * Here the solution using the idea of swapping 
     * elements to their place, it a wit idea so I decided
     * to implement it.
     */
    int missingNumber(vector<int>& nums) {
        
      int swapIdx = 0;
        while(swapIdx < nums.size()){
            if(nums[swapIdx]== nums.size() || nums[swapIdx] == swapIdx){
                swapIdx++;
            }else{
                swap(nums, swapIdx, nums[swapIdx]);
            }
        }

        int missing = -1;
        for(int idx = 0 ; idx < nums.size(); idx++){
            if(nums[idx] != idx){
                missing = idx;
                break;
            }
        }
        //it's possible that only nums.size() is missing,
        //if that's the case, missing == -1 since 
        //nums[idx] = idx for idx in {0, ..., nums.size() - 1}.
        missing = missing == -1 ? nums.size() : missing;
        return missing;
    
    }

    private:
        void swap(vector<int>& nums, int idx1, int idx2){
            int elem1 = nums[idx1];
            int elem2 = nums[idx2];
            nums[idx1] = elem2;
            nums[idx2] = elem1;
        }
};
