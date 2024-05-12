/**
 * https://leetcode.com/problems/merge-intervals
 * #intervals #interval #greedy #sort
 */
class Solution {
public:
    ///Basic cases:
    ///1: empty intervals => empty itervals.
    ///2: monotonic: [1, 2], [3, 4], [5, 5] => return all
    ///3: contained: permutations of [1, 4], [2, 3], [1,1] => return [1, 4]
    ///4: intersected: [1, 4], [2, 5] => return [1, 5] 

    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sortByAlphabeticalOrder(intervals);
        vector<vector<int>> res;
        vector<int> currInter = intervals[0]; 
        for(const vector<int>& inter : intervals){
            ///currInter[0] <= inter[0] due to sorting.
            ///inter[0] <= inter[1] due to problem definition.
            if(currInter[1] < inter[0]){
                res.push_back(currInter);
                currInter[0] = inter[0];
                currInter[1] = inter[1];
            }else if(currInter[1] < inter[1]){
                currInter[1] = inter[1];
            }
        }
        res.push_back(currInter);
        return res;
    }
private:

    void sortByAlphabeticalOrder(vector<vector<int>>& intervals){   
        ranges::sort(intervals, 
                     [](const vector<int>& inter1,
                        const vector<int>& inter2){
                            if(inter1[0] < inter2[0]){
                                return true;
                            }else if(inter1[0] == inter2[0]){
                                return inter1[1] < inter2[1];
                            }else{
                                return false;
                            }});
    }
};
