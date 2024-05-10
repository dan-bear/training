/**
 * https://leetcode.com/problems/summary-ranges
 * #two_pointers #string
 */
class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> res;
        if(nums.size() == 0){
            return res;
        }
        int firstIdx = 0;
        int lastIdx = 0;
        while(lastIdx < nums.size()){
            if(lastIdx != 0 && nums[lastIdx] != 1 + nums[lastIdx - 1]){
                res.push_back(createInterval(nums, firstIdx, lastIdx - 1));
                firstIdx = lastIdx;
            }
            lastIdx++;
        }
        ///Need to add the last interval.
        res.push_back(createInterval(nums, firstIdx, lastIdx - 1));
        return res;
    }

private:
    string createInterval(const vector<int>& nums, int firstIdx, int lastIdx){
        string res;
        if(firstIdx == lastIdx){
            res += to_string(nums[firstIdx]);
        }else{
            res += to_string(nums[firstIdx]);
            res += string("->");
            res += to_string(nums[lastIdx]);
        }
        return res;
    }
};
