/**https://leetcode.com/problems/longest-palindromic-substring*/

/**
 * There is a class for the iterative solution and a
 * class for the dp solution.
 */
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class IterativeSolution
{
  public:
    string longestPalindrome(string s)
    {
        int longestPalLen = 0;
        int centeredAroundIdx = 0;
        int sLen = s.length();

        for (int charIdx = 0; charIdx < sLen; charIdx++) {
            int currLen = longestPlaindromAround(charIdx, s);
            if (currLen > longestPalLen) {
                longestPalLen = currLen;
                centeredAroundIdx = charIdx;
            }
        }

        string res =
          getPalindromSubStr(longestPalLen, centeredAroundIdx, s);
        return res;
    }

  private:
    int longestPlaindromAround(int charIdx, string s)
    {
        int evenPalindromLen = longestEvenPalindromAround(charIdx, s);
        int oddPalindromLen = longestOddPalindromAround(charIdx, s);
        int res = std::max<int>(evenPalindromLen, oddPalindromLen);
        return res;
    }

    int longestEvenPalindromAround(int charIdx, string s)
    {
        int radius =
          calcSymmetricRadiusAround2Indexes(charIdx, charIdx + 1, s);
        int res = 2 * radius;
        return res;
    }

    int longestOddPalindromAround(int charIdx, string s)
    {
        int radius = calcSymmetricRadiusAround2Indexes(
          charIdx - 1, charIdx + 1, s);
        int res = 1 + 2 * radius;
        return res;
    }

    int calcSymmetricRadiusAround2Indexes(int leftCharIdx,
                                          int rightCharIdx,
                                          string s)
    {
        int sLen = s.length();
        int radius = 0;
        while (leftCharIdx - radius >= 0 &&
               rightCharIdx + radius < sLen) {
            if (s[leftCharIdx - radius] == s[rightCharIdx + radius]) {
                radius += 1;
            } else {
                break; // cannot expend the palindrom any more.
            }
        }
        return radius;
    }

    string getPalindromSubStr(int longestPalLen,
                              int centerIdx,
                              string s)
    {
        int radius = longestPalLen % 2 == 0 ? longestPalLen / 2 - 1
                                            : longestPalLen / 2;

        string res = s.substr(centerIdx - radius, longestPalLen);
        return res;
    }
};

class DPSolution
{
  public:
    string longestPalindrome(string s)
    {
        int sLen = s.length();
        vector<vector<bool>> isPalDpTable(sLen,
                                          vector<bool>(sLen, false));
        for (int diagIdx = 0; diagIdx < sLen; diagIdx++) {
            int numOfRowsInDiag = sLen - diagIdx;
            for (int rowIdx = 0; rowIdx < numOfRowsInDiag; rowIdx++) {
                int colIdx = diagIdx + rowIdx;
                calcIsPalDpRule(isPalDpTable, rowIdx, colIdx, s);
                updateLongestPal(isPalDpTable, rowIdx, colIdx);
            }
        }

        string res =
          s.substr(m_startIdxOfLongestPal, m_lenOfLongestPal);
        return res;
    }

  private:
    void calcIsPalDpRule(vector<vector<bool>>& rDpTable,
                         int rowIdx,
                         int colIdx,
                         string& rS)
    {
        bool bRes = false;
        if (rowIdx == colIdx) {
            bRes = true;
        } else if (rS[rowIdx] == rS[colIdx]) {
            if (colIdx == rowIdx + 1) {
                bRes = true;
            } else if (rDpTable[rowIdx + 1][colIdx - 1] == true) {
                bRes = true;
            }
        }

        rDpTable[rowIdx][colIdx] = bRes;
    }

    void updateLongestPal(vector<vector<bool>>& rDpTable,
                          int rowIdx,
                          int colIdx)
    {
        if (rDpTable[rowIdx][colIdx] == true) {
            int palLen = colIdx - rowIdx + 1;
            if (palLen > m_lenOfLongestPal) {
                m_lenOfLongestPal = palLen;
                m_startIdxOfLongestPal = rowIdx;
            }
        }
    }

    int m_startIdxOfLongestPal{ 0 };
    int m_lenOfLongestPal{ 0 };
};

class Solution
{
  public:
    string longestPalindrome(string s)
    {
        // IterativeSolution sol;
        DPSolution sol;
        return sol.longestPalindrome(s);
    }
};

int
main()
{
    Solution sol;
    string s1("babad");
    std::cout << sol.longestPalindrome(s1) << std::endl;
    string s2("caad");
    std::cout << sol.longestPalindrome(s2) << std::endl;
    string s3("a");
    std::cout << sol.longestPalindrome(s3) << std::endl;
    string s4("bb");
    std::cout << sol.longestPalindrome(s4) << std::endl;
    return 0;
}
