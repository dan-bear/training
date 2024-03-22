/**
 * https://leetcode.com/problems/kth-largest-element-in-an-array/
 * #heap #sort
 */
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        ///return sortBasedFindKthLargest(nums, k);
        return heapBasedFindKthLargest(nums, k);
    }
private:
    int heapBasedFindKthLargest(vector<int>& nums, int k){
        make_heap(nums.begin(), nums.end());

        while(k > 1){
            pop_heap(nums.begin(), nums.end());
            nums.pop_back();
            k--;
        }
        return nums[0];
    }

    int sortBasedFindKthLargest(vector<int>& nums, int k){
        sort(nums.begin(), nums.end());
        return nums[nums.size() - k];
    }
};
