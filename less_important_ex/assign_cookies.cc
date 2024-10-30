/**
 * https://leetcode.com/problems/assign-cookies
 * #2ptrs
 */
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        std::sort(g.begin(), g.end());
        std::sort(s.begin(), s.end());
        int sizeIdx = 0;
        int greedyIdx = 0;
        int count = 0;
        while(greedyIdx < g.size() && sizeIdx < s.size()){
            if(g[greedyIdx] <= s[sizeIdx]){
                count++;
                greedyIdx++;
            }
            sizeIdx++;
        }
        return count; //note - could have returned greedyIdx.
    }
};
