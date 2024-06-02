/**
 * https://leetcode.com/problems/palindrome-partitioning/
 * #dp #DP #backtrack
 */
class Solution {
public:
    vector<vector<string>> partition(string s){
        ///return fullyDpApproach(s);
        return backtrackApproach(s);
    }

private:  
    using Partition = vector<string>;
    /**
     * Example that generates the update rule:
     * aaaa:
     * dp[0][0] = ["a"]
     * dp[0][1] = ["a", "a"], ["aa"]
     * dp[0][2] = ["a", "a", "a"], ["aa", a], ["a", "aa"], ["aaa"]
     *
     * dp[0][3]: 1: Add s[3] to each element in dp[0][2] 
     *              ["a", "a", "a", "a"], ["aa", "a", "a"], ["a", "aa", "a"], ["aaa", "a"]
     *           2: if s[2:3] is a palindrome - add s[2:3] to each element at dp[0][1]
     *              ["a", "a", "aa"], ["aa", "aa"]
     *           3: if s[1:3] is a palindrome - add s[1:3] to each element at dp[0][0]
     *              ["a", "aaa"]
     *           4: if s[0:3] is a palindrome - add it to each element at dp[0][-1]
     *              ["aaaa"]
     *           so dp[0][3] is the union of all the results in step 1 to 4.
     *
     * How to determine the isPalindrom table:
     * palTbl[i][j] = true whether s[i : j] is a palindrome
     * palTbl[i][i] = true
     * palTabl[i][j < i] = true (just for the update rule)
     * palTbl[i][j > i] = true iff: palTable[i + 1][j - 1] = true and s[i] == s[j]
     * 
     */
    vector<Partition> fullyDpApproach(const string& s) {
        vector<vector<bool>> palTbl = createPalTbl(s);
        vector<vector<Partition>> dp(s.size());

        ///The base partition, is partition of "s[0]"
        dp[0].push_back(Partition(1, s.substr(0, 1)));
        for(int lastCharIdx = 1; lastCharIdx < s.size(); lastCharIdx++){
            calcPartitions(s, lastCharIdx, palTbl, dp);
        }
        return dp[s.size() - 1];
    }

    void calcPartitions(const string& s, 
                        const int lastCharIdx, 
                        const vector<vector<bool>>& palTbl,
                        vector<vector<Partition>>& dp){
        vector<Partition>& partitions = dp[lastCharIdx];
        
        int firstCharIdx = 0;
        ///The full palindrome case.
        if(palTbl[firstCharIdx][lastCharIdx]){
            partitions.push_back(
                Partition(1, s.substr(firstCharIdx, lastCharIdx + 1)));
        }

        ///Partial palindromes cases.
        for(firstCharIdx = 1; firstCharIdx <= lastCharIdx; firstCharIdx++){
            if(palTbl[firstCharIdx][lastCharIdx]){
                string addition =
                    s.substr(firstCharIdx, (lastCharIdx + 1 - firstCharIdx));
                for(Partition part : dp[firstCharIdx - 1]){
                    part.push_back(addition);
                    partitions.push_back(part);
                }        
            }
        }
    }

    vector<vector<bool>> createPalTbl(const string& s){
        vector<vector<bool>> palTbl(s.size(), vector<bool>(s.size(), true));
        int colIdx = -1;
        for(int diagIdx = 1; diagIdx < s.size(); diagIdx++){
            for(int rowIdx = 0; rowIdx < s.size() - diagIdx; rowIdx++){
                colIdx = diagIdx + rowIdx;
                palTbl[rowIdx][colIdx] = 
                    (s[rowIdx] == s[colIdx] && palTbl[rowIdx + 1][colIdx - 1]);
            }
        }
        return palTbl;
    }


    vector<Partition> backtrackApproach(const string& s){
        Partition partition;
        vector<Partition> res;
        vector<vector<bool>> palTbl = createPalTbl(s);
        backtrackApproachAux(s, 0, palTbl, partition, res);
        return res;

    }

    void backtrackApproachAux(const string& s, 
                              const int firstCharIdx,
                              const vector<vector<bool>>& palTbl,
                              Partition& rPart,
                              vector<Partition>& rRes){
        if(s.size() == firstCharIdx){
            rRes.push_back(rPart);
        }else{
            for(int charIdx = firstCharIdx; charIdx < s.size(); charIdx++){
                if(palTbl[firstCharIdx][charIdx]){
                    rPart.push_back(
                        s.substr(firstCharIdx, charIdx - firstCharIdx + 1));
                    backtrackApproachAux(s, charIdx + 1, palTbl, rPart, rRes);
                    rPart.pop_back();
                }
            }
        }
    }
};
