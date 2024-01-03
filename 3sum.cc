///https://leetcode.com/problems/3sum
class Solution
{
  public:
    vector<vector<int>> threeSum(vector<int>& nums)
    {
        set<vector<int>> tripletsSet;

        sort(nums.begin(), nums.end());
        for (int firstIdx = 0; firstIdx < nums.size(); firstIdx++) {
            calcTwoSumComplement(nums, firstIdx, tripletsSet);
        }

        // from set to vector.
        vector<vector<int>> tripletsVecRes(tripletsSet.begin(),
                                           tripletsSet.end());
        return tripletsVecRes;
    }

    void calcTwoSumComplement(const vector<int>& sortedNums,
                               const int firstIdx,
                               set<vector<int>>& tripletsSetOut)
    {
        int complement = -sortedNums[firstIdx];
        int leftIdx = firstIdx + 1;
        int rightIdx = sortedNums.size() - 1;

        while (leftIdx < rightIdx) {
            int twoSum = sortedNums[leftIdx] + sortedNums[rightIdx];

            if (twoSum == complement) {
                tripletsSetOut.insert(
                  vector<int>{ sortedNums[firstIdx],
                               sortedNums[leftIdx],
                               sortedNums[rightIdx] });

                leftIdx++;
                rightIdx--;
            } else if (twoSum < complement) {
                // need a greater value and nums is ordered.
                leftIdx++;
            } else {
                // need a smaller value and nums is ordered.
                rightIdx--;
            }
        }
    }
};
