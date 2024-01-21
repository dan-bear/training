/** https://leetcode.com/problems/counting-bits */
class Solution {
public:
    //a[0] = 0 
    //a[1] = 1 = 1 + a[1 - 2^0]

    //a[2] = 1 + a[0] = 1 + a[x- 2^1]
    //a[3] = 1 + a[1] = 1 + a[x - 2^2]

    //a[4] = 1 + a[0] = 1 + a[x - 2^2]
    //a[5] = 1 + a[1] = 1 + a[x - 2^2]
    //a[6] = 1 + a[2] = 1 + a[x - 2^2]
    //a[7] = 1 + a[3] = 1 + a[x - 2^2]

    //a[i] = 1 + a[i - 2^floor(log_2(i))]
    vector<int> countBits(int n) {
        vector<int> res(n + 1, 0);
        for(int idx = 1; idx <= n ; idx++){
            res[idx] = 1 + res[idx - pow(2, floor(log2(idx)))];
            //Another way to think about it.
            //res[idx] = res[idx / 2] + idx % 2;
        }
        return res;
    }
};
