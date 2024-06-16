
/**
 * https://leetcode.com/discuss/interview-question/5304104/Google-or-Interview-Question
 * 
 * #google
 * #dp #DP
 * 
 * Given an array bombs, where each element is the i-th bomb's explosion radius,
 * one can perform the following operation until all the bombs are gone:
 * Choose two bombs at indices i and j which won't explode each other if 
 * detonated, explode them and add the two explosion radii to the total. After
 * the explosion, all bombs in the range [i - bombs[i], i + bombs[i]] 
 * and [j - bombs[j], j + bombs[j]] are removed.
 * Note that once a bomb is removed, it won't be detonated.
 * Return the maximum total explosion radii that can achieved by repeating the
 * operation till all bombs are detonated or removed.
 * Sample Case:
 * Bombs = [3, 1, 1, 1, 3]
 * Expected answer = 6 by picking first and last last bomb.
 * 
 * Solution:
 * 
 * Notes: the order of bombing in the optimal solution just
 *        does not matter.
 * 
 * 3: dp[j] best radius in bombs[0 : j]
 *    For bomb j, it can be used together with bomb i such
 *    that (j - i) > max(bomb[i], bomb[j]). Or, it can be
 *    exploded by a bomb i such that (j - i) < bomb[i].
 *    So, the optimal solution is:
 *    for any i in range(0, j - 1):
 *        if (j - i) > max(bomb[i], bomb[j]):
 *            dp[j] = max(dp[j], dp[i] + bomb[j])
 *        else if (j - i) < bomb[i]:
 *            dp[j] = max(dp[j], dp[i])
 *    
 *    dp[bombs_len - 1]  contains the answer.
 *
 *    Complexity - O(n^2) time and O(n) space.
 * 
 */
#include <vector>
using namespace std;
int maxRadius(const vector<int>& bombs){
    vector<int> dp(bombs.size(), 0);
    dp[0] = bombs[0];
    for (int bombIdx = 1; bombIdx < bombs.size(); bombIdx++){
        for (int prevBombIdx = 0; prevBombIdx < bombIdx; prevBombIdx++){
            if(bombIdx - prevBombIdx > max(bombs[bombIdx], bombs[prevBombIdx])){
                dp[bombIdx] =
                  max(dp[bombIdx], bombs[bombIdx] + dp[prevBombIdx]);
            }else if(bombIdx - prevBombIdx < bombs[prevBombIdx]){
                dp[bombIdx] = max(dp[bombIdx], dp[prevBombIdx]);
            }
        }
    }
    return dp[bombs.size() - 1];
}
