/**
 * https://leetcode.com/problems/non-overlapping-intervals
 * #sort #greedy #intervals #SORT #GREEDY #INTERVALS
 */
class Solution {
public:
    ///Example: [[1, 2], [2, 3], [3, 4], [1, 3]].
    ///Sort by the end values.
    ///[[1, 2], [2, 3], [1, 3], [3, 4]] or
    ///[[1, 2], [1, 3], [2, 3], [3, 4]]
    ///if inter[i][1] > inter[i + 1][0] => remove inter[i + 1].
    ///It's a sort + greedy approach.
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sortByIntervalEndVal(intervals);
        int removeCount = 0;
        int currentInterIdx = 0;
        for(int otherInterIdx = 1; otherInterIdx < intervals.size(); otherInterIdx++){
            if(isIntersecting(intervals[currentInterIdx], intervals[otherInterIdx])){
                removeCount++;
            }else{
                currentInterIdx = otherInterIdx;
            }
        }
        return removeCount;
    }
private:
    bool isIntersecting(const vector<int>& leftInterval, const vector<int>& rightInterval){
        return leftInterval[1] > rightInterval[0];
    }
    
    void sortByIntervalEndVal(vector<vector<int>>& intervals){
        ranges::sort(intervals, [](const vector<int>& inter1,
                                   const vector<int>& inter2){
            return inter1[1] < inter2[1];
        });
    }
};
