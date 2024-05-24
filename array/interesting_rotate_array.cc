/**
 * https://leetcode.com/problems/rotate-array/
 * #array
 * #interesting 
 */
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k %= nums.size();
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());

        ///Note: the reverse is homomorphic in this
        ///      solution. One could also first
        ///      reverse the n - k prefix and k suffix
        ///      and then reverse all.
    }
};
