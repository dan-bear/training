/**
 * https://leetcode.com/problems/increasing-triplet-subsequence/
 * #greedy #greedy algorithm
 */
class Solution {
public:
    /**
     * Why the greedy solution works?
     * Given two elements nums[i] < nums[i+d] if
     * nums[i+d+t] > nums[i+d] an increasing triplet is
     * found.
     * So, the algorithm maintains minVal and medVal
     * corresponding to nums[i] and nums[i+d], the
     * question is how to update the values:
     * Once the iteration encounter nums[j].
     * if nums[j] < minVal: it means that finding an element
     * nums[t] such that  min < mid < nums[t] is the same 
     * as finding a value satisfying nums[k] < mid < nums[t]
     * since nums[k] < min, so by replacing min with nums[k]
     * the algorithm does not lose any information. But, 
     * in case there are two values nums[k+t1], nums[k+t1+t2]
     * such that nums[k] < num[k+t1] < nums[k+t2] < min, the
     * algorithm might miss it unless min is updated to nums[k].
     *
     * Same logic stands for mid, if one finds nums[j] such
     * that min < nums[j] < mid, if there is an element after
     * nums[j], nums[j + r] such that nums[j + r] > mid, 
     * replacing mid with nums[j] is fine since both:
     * min, mid, nums[j+r] and min, nums[j], nums[j+r] are
     * valid triplets. But, without replacing mid with nums[j],
     * a a triplet of the form min, nums[j], nums[j+r] that
     * satisgies nus[j+1] < mid won't be detected by the 
     * algorithm. 
     */

    bool increasingTriplet(vector<int>& nums) {
        bool bRes = false;
        int minTripletValue = std::numeric_limits<int>::max();
        int midTripletValue = std::numeric_limits<int>::max();
        for(int elem : nums){
            if(elem <= minTripletValue){
                // Got a smaller element that appears after the
                // current minimal element. 
                minTripletValue = elem;
            }else if(elem <= midTripletValue){
                // Got a smaller mid element that appears after the
                // current mid element.
                midTripletValue = elem;
            }else{
                //Cool, the current element is greater than min
                //and min < mid.
                bRes = true;
                break;
            }
        }
        return bRes;        
    }
};
