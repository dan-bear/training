/** https://leetcode.com/problems/zigzag-conversion/ */

/**
 * for row_idx in [1,...,r-2]
 * start1 = row_idx
 * start2 = 2*r - 2 - rowIdx
 *
 * for row_idx = 0/r-1:
 * start1 = row_idx
 * no start2
 *
 * distance = 2r - 2 for r > 1, otherwise distance = 1.
 *
 */
#include <string>
#include <iostream>
using namespace std;

class Solution
{
  public:
    string convert(string s, int numRows)
    {
        // Avoid the string::append to be more cpu efficiet.
        int sLen = s.length();
        string zigzagStr(sLen, ' ');
        int appendCharIdx = 0;
        for (int rowIdx = 0; rowIdx < numRows; rowIdx++) {
            appendCharIdx = fillZigzagRow(
              s, zigzagStr, appendCharIdx, rowIdx, numRows);
        }
        return zigzagStr;
    }

  private:
    int fillZigzagRow(string& s,
                      string& zigzagStr,
                      int appendCharIdx,
                      int rowIdx,
                      int numRows)
    {

        int dist = numRows > 1 ? (2 * numRows) - 2 : 1;
        int start1 = rowIdx;
        int start2 = (2 * numRows) - 2 - rowIdx;
        int copyFromIdx = start1;
        int sLen = s.length();

        while (copyFromIdx < sLen && appendCharIdx < sLen) {

            zigzagStr[appendCharIdx] = s[copyFromIdx];
            appendCharIdx += 1;

            if (rowIdx != 0 && rowIdx != numRows - 1) {
                copyFromIdx = copyFromIdx == start1 ? start2 : start1;
                if (copyFromIdx == start2) {
                    start1 += dist;
                } else {
                    start2 += dist;
                }
            } else {
                start1 += dist;
                copyFromIdx = start1;
            }
        }

        return appendCharIdx;
    }   
};

int
main()
{
    Solution sol;
    std::cout << sol.convert(string("PAYPALISHIRING"), 3)
              << std::endl;
}
