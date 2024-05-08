/**
 * https://leetcode.com/problems/n-th-tribonacci-number
 * #dp
 */
class Solution {
public:
    int tribonacci(int n) {
        if(n == 0){
            return 0;
        }else if(n == 1 || n == 2){
            return 1;
        }else{
            vector<int> lastThree = {0, 1, 1};
            int threeSum = 0;
            for(int idx = lastThree.size(); idx <= n; idx++){
                threeSum = accumulate(lastThree.begin(), lastThree.end(), 0);
                shiftLeft(lastThree);
                lastThree[lastThree.size() - 1] = threeSum;
            }
            return threeSum;
        }
    }

private:
    void shiftLeft(vector<int>& vec){
        for(int idx = 0; idx < vec.size() - 1; idx++){
            vec[idx] = vec[idx + 1];
        }
    }

};
