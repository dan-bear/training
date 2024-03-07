/**
 * https://leetcode.com/problems/search-insert-position/
 * #binary-search #bs #BS
 */
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        ///Note: this solution just modifies the binary search
        ///return value in case target is not in the list.
        int leftIdx = 0;
        int rightIdx = nums.size() - 1;
        while (leftIdx <= rightIdx) {
            int midIdx = (leftIdx + rightIdx) / 2;
            if (nums[midIdx] == target) {
                return midIdx;
            } else {
                if (nums[midIdx] < target) {
                    leftIdx = midIdx + 1;
                } else {
                    rightIdx = midIdx - 1;
                }
            }
        }
        return rightIdx + 1;           
    }
};
