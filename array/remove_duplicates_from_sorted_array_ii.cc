/**
 * https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii
 * #array #arrays #sorted_arrays
 *
 * #Note: try to search for an invariant for more elegant solution.
 */
class Solution {
public:
    /**
     * Edge cases:
     * 1: nums is empty.
     *    Note: the edge case is not implemented due to problem
     *          description.
     * 
     * placementIdx update.
     * Example, 1, 1, 1, 2, 2, 2, 3, 3
     * placementIdx = 0.
     * n[0] => placementIdx, placmentIdx = 1.
     * n[1] => placementIdx, placementIdx = 2.
     * n[2] => skip, placementIdx = 2.
     * n[3] => placementIdx, placementIdx = 3.
     * n[4] => placementIdx, placementIdx = 4.
     * n[5] => skip, placementIdx = 4.
     * n[5] => placementIdx, placementIdx = 5
     * n[6] => placementIdx, placementIdx = 6
     * The placementIdx should be returned.
     */
    static constexpr int skAppearancesBound{2};
    int removeDuplicates(vector<int>& nums) {
        ///A straight forward approach:
        // int currentNum = nums[0];
        // int currentNumCount = 0;
        // int placementIdx = 0;
        // for(int idx = 0; idx < nums.size(); idx++){
        //     if(nums[idx] == currentNum){
        //         currentNumCount++;
        //         if(currentNumCount <= skAppearancesBound){
        //             nums[placementIdx] = currentNum;
        //             placementIdx++;
        //         }
        //     }else{
        //         currentNum = nums[idx];
        //         currentNumCount = 1;
        //         nums[placementIdx] = currentNum;
        //         placementIdx++;
        //     }
        // }
        // return placementIdx;

        ///Another approach for the update, is to keep the
        ///invariant that nums[idx - 2] != nums[idx] for each
        ///idx >= 2.
        int invariantDistance = 2;
        if(nums.size() <= invariantDistance){
            return nums.size();
        }
        
        int placementIdx = invariantDistance;
        int val = 0;
        ///The commented lines can replace its corresponding lines,
        ///but it's slower.
        //for(auto itr = next(nums.begin(), placementIdx); itr != nums.end(); itr++){
        for(int idx = placementIdx; idx < nums.size(); idx++){    
            //val = *itr;
            val = nums[idx];
            if(nums[placementIdx - invariantDistance] != val){
                nums[placementIdx] = val;
                placementIdx++;
            }
        }
        return placementIdx;
    }
};
