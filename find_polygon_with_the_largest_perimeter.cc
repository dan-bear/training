/**
 * https://leetcode.com/problems/find-polygon-with-the-largest-perimeter/
 */
class Solution {
public:
    long long largestPerimeter(vector<int>& nums) {
        sort(nums.begin(), nums.end());
      
        long long maxPerimeter = -1;
        long long sumTillLastElement = nums[0] + nums[1];
        long long currentPerimeter = 0;
        for(int endIdx = 2; endIdx < nums.size(); endIdx++){
            currentPerimeter = 
                sumTillLastElement + static_cast<long long>(nums[endIdx]);
            if(sumTillLastElement > static_cast<long long>(nums[endIdx])){
                maxPerimeter = currentPerimeter;
            }
            sumTillLastElement = currentPerimeter;
        }
        return maxPerimeter;
    }
};
