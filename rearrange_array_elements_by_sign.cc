/**
 * https://leetcode.com/problems/rearrange-array-elements-by-sign
 * 
 * Why it cannot be done in place and in O(n) time?
 * Let's say it can be one in O(n) time and O(1) space.
 * Can we build a sorting algorithm in better than
 * nlog(n) time?
 */
class Solution {
public:
    
    vector<int> rearrangeArray(vector<int>& nums) {
        
        // One iteration solution.
        vector<int> rearrangedArr(nums.size(), 0);
        int posIdx = 0;
        int negIdx = 1;
        for(int idx = 0; idx < nums.size(); idx++){
            if(nums[idx] < 0){
                rearrangedArr[negIdx] = nums[idx];
                negIdx += 2;
            }else{
                rearrangedArr[posIdx] = nums[idx];
                posIdx += 2;
            }
        }
        return rearrangedArr;



        // Two iterations solution.
        // vector<int> rearrangedArr(nums.size(), 0);
        // int posIdx = moveToPosElem(nums, 0);
        // int negIdx = moveToNegElem(nums, 0);
        
        // for(int currIdx = 0; currIdx < nums.size(); currIdx++){
        //     if(currIdx % 2 == 0){
        //         rearrangedArr[currIdx] = nums[posIdx];
        //         posIdx = moveToPosElem(nums, posIdx + 1);
        //     }else{
        //         rearrangedArr[currIdx] = nums[negIdx]; 
        //         negIdx = moveToNegElem(nums, negIdx + 1);  
        //     }
        // }
        // return rearrangedArr;
    }

private:

    // int moveToPosElem(const vector<int>& nums, int startIdx){
    //     int resIdx = startIdx;
    //     while(resIdx < nums.size()){
    //         if(nums[resIdx] >= 0){
    //             break;
    //         }
    //         resIdx++;
    //     }
    //     return resIdx;
    // }
    
    // int moveToNegElem(const vector<int>& nums, int startIdx){
    //     int resIdx = startIdx;
    //     while(resIdx < nums.size()){
    //         if(nums[resIdx] < 0){
    //             break;
    //         }
    //         resIdx++;
    //     }
    //     return resIdx;
    // }                    
};
