/**
 * https://leetcode.com/problems/find-peak-element
 * #binary earch
 */
class Solution {
public:
    ///Go to the middle:
    ///If it's a pick, cool.
    ///If it's not a pick, it means that:
    ///   1: It's a vally.
    ///   2: It's a left-right decreasing triplet.
    ///   3: It's a left-right increasing triplet.
    ///If it's a vally:
    ///    choose one of the sides, and contiue the search.
    ///If it's a left-right decreasing triplet:
    ///    continue the search in the left part.
    ///If it's a left-right increasing triplet:
    ///    continus the search in the right part.
    using i64 = long long;
    int findPeakElement(vector<int>& nums) {
        int leftIdx = 0;
        int rightIdx = nums.size() - 1;
        i64 lowestVal = numeric_limits<i64>::lowest();
        int midIdx = -1;
        while(leftIdx <= rightIdx){
            midIdx = (leftIdx + rightIdx) / 2;  
            i64 midVal = static_cast<i64>(nums[midIdx]);
            i64 leftVal = midIdx > 0 ? static_cast<i64>(nums[midIdx - 1]) : lowestVal;
            i64 rightVal = midIdx < nums.size() - 1 ? static_cast<i64>(nums[midIdx + 1]) : lowestVal;
            if(midVal > leftVal && midVal > rightVal){
                break;
            }else if(midVal < leftVal){
                rightIdx = midIdx - 1;
            }else{
                leftIdx = midIdx + 1;
            }
        }
        return midIdx;
    }
};
