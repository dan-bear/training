/**https://leetcode.com/problems/domino-and-tromino-tiling */
class Solution {
public:
    /**
     * Rotations!
     *
     * number of tilings for n = 0 is set to 1 (the empty tiling).
     * number of tiling for n = 1 is 1:
     *     1
     *     1
     * number of tiling for n = 2 is 2:
     *     1 2     1 1
     *     1 2     2 2
     * number of tiling for n = 3 is:
     * 1: Add a single vertical domino as the last column for
     *    each tiling in n = 2:
     *    1 2 3    1 1 3    
     *    1 2 3    2 2 3
     * 2: Add two horitzonal dominoes as the last two columns
     *    for each tiling in n = 1:
     *    1 2 2 
     *    1 3 3
     * 3: Add two trominos in both rotations for each column in each
     *    tilig in n = 0 column tilings.
     *    1 1 2   1 2 2
     *    1 2 2   1 1 2
     *
     * The rule also follow
     *
     * 1 2 3  1 1 3  1 2 2  1 1 2  1 2 2
     * 1 2 3  2 2 3  1 3 3  1 2 2  1 1 2
     *
     * First rule:
     * 1 2 3 4  1 1 3 4  1 2 2 4  1 1 2 3  1 2 2 4
     * 1 2 3 4  2 2 3 4  1 3 3 4  1 2 2 3  1 1 2 4
     * 
     * Second rule:
     * 1 2 3 3  1 1 3 3 
     * 1 2 4 4  2 2 4 4
     *
     * Third rule:
     * 2 2 3 3  2 1 1 3
     * 2 1 1 3  2 2 3 3 
     *
     * L L ? ... ? ? R    L ? ?     ? R R
     * L ? ? ... ? R R    L L ? ... ? ? R
     *
     * 1: 3 columns => no question mark:
     *    L L R    L R R
     *    L R R    L L R
     * 2: 4 columns => 2 question marks:
     *    L L R R  L ? ? R
     *    L ? ? R  L L R R
     *    The only way to fill the question marks is by one horizontal
     *    domino.
     * 3: 5 columns => 4 question marks:
     *    L L ? R R  L ? ? ? R
     *    L ? ? ? R  L L ? R R
     * 4: 6 columns => 6 question marks:
     *    L L ? ? R R  L ? ? ? ? R
     *    L ? ? ? ? R  L L ? ? R R
     *
     * 3: There are  
     *    
     */
    int numTilings(int n) {
        ///dp[i] is the number of tilings in 2 X (i + 1) board.
        ///dp[0] = 1 (one vertical domino)
        ///dp[1] = 2. (two vertical dominoes or two horizontal dominoes)
        ///dp[2] = 5 (dp[0] + dp[2] + 2 ways for the 2 trominos).
        ///
        ///For i >= 3, think about the ways to fill column i, given the
        ///previous state, that states are:
        ///1: The grid is full till column i - 1, so only column i should
        ///   be filled.
        ///   - So, for each tiling of 2 X (i-1) grid, a tiling for 
        ///     2 X i grid is formed by adding a vertical domino.
        ///     
        ///2: The grid is full till column i - 2, so columns i-1 and i should
        ///   be filled.
        ///   - To fill both both columns, two dominoes can be used, they can
        ///     be positioned vertically or horizontally. Note that
        ///     using 2 vertical dominoes is already counteed in the previous
        ///     case. So, for each solution for 2 X (i - 2) grid, add two
        ///     horizontal dominoes and get a solution for 2 X i grid.
        ///
        ///3:  The grid is full till column i - 3, so columns i - 2, i - 1 and
        ///    i should be filled, the only way the previous cases do not count
        ///    is using two trominos to fill the 3 last columns. There are 2
        ///    ways to fill 3 columns using 2 trominoes, thus for each tiling
        ///    for 2 X (i - 3) grid,  2 solutions are formed by adding 2
        ///    trominos. But, the two torminoes can be positioned anywhere in
        ///    the previoud solutions, they can be added anywhere in the
        ///    2 * (i - 3) tilings. So, it gives more solutions:
        ///    2 * #[2 X (i - 3) tilings] + 2 * #[2 X (i - 4) tilings] ... 2 * #[2 X 1 tilings].
        ///
        ///dp[i] = dp[i - 1] + dp[i - 2] + 2*dp[i - 3] + 2*dp[i - 4]... 2 * dp[0].
        ///dp[i - 1] = dp[i - 2] + dp[i - 3] + 2*dp[i - 4] + ... + 2 * dp[0]
        ///dp[i] - dp[i - 1] = dp[i - 1] + dp[i - 3]
        ///dp[i] = 2 dp[i - 1] + dp[i - 3].
        vector<int> dp({1, 2, 5});
        if(n <= 3){
            return dp[n - 1];
        }

        int mod = 1e9 + 7;
        for(int idx = 3; idx < n; idx++){
            int res = ((2 * dp[2]) % mod + (dp[0])) % mod;
            dp[0] = dp[1];
            dp[1] = dp[2];
            dp[2] = res;
        }
        return dp[2];
    }

    ///dp[i] = dp[i - 1] + 2 * dp[i - 2] + 2 * dp[i - 3].
    ///dp[0] = 1.
    ///dp[1] = 2
    ///dp[2] = 5
    ///dp[3] = 5 + 2*2 + 2*1 = 11
    ///dp[4] = 11 + 2*5 + 2*2 = 11 + 10 + 4 = 25
};
