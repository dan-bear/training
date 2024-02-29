/**
 * #google #GOOGLE
 * #BT
 * https://leetcode.com/discuss/interview-question/2095524/google-onsite-interview-29th-may
 */
#include <vector>
using namespace std;
class Solution
{
  public:
    bool currentPlayerWin(vector<int> heights, vector<char> colors)
    {
        bool resCurrPlayerWin = false;
        for (int srcStackIdx = 0; srcStackIdx < m_dim;
             srcStackIdx++) {
            // note: moving stack i to j is not the same as
            // moving j to i, so the dst index starts from
            // 0. It is checked that srcIdx != dstIdx in
            // makeMove() function.
            for (int dstStackIdx = 0; dstStackIdx < m_dim;
                 dstStackIdx++) {

                // save current state.
                int srcHeight = heights[srcStackIdx];
                int dstHeight = heights[dstStackIdx];
                char srcColor = colors[srcStackIdx];
                char dstColor = colors[dstStackIdx];

                if (makeMove(
                      heights, colors, srcStackIdx, dstStackIdx)) {
                    // now pass the turn to the other player.
                    // and check whether it can win or not.
                    if (!currentPlayerWin(heights, colors)) {
                        resCurrPlayerWin = true;
                        break;
                    } else {
                        // recover current state for another move.
                        colors[srcStackIdx] = srcColor;
                        heights[srcStackIdx] = srcHeight;
                        colors[dstStackIdx] = dstColor;
                        heights[dstStackIdx] = dstHeight;
                    }
                }
            }
        }
        return currentPlayerWin;
    }

  private:
    bool makeMove(vector<int>& heights,
                  vector<char>& colors,
                  int srcStackIdx,
                  int dstStackIdx)
    {
        bool canMakeMove =
          (srcStackIdx != dstStackIdx) &&
          ((heights[srcStackIdx] > 0 &&
            heights[srcStackIdx] == heights[dstStackIdx]) ||
           (colors[srcStackIdx] != m_noColor &&
            colors[srcStackIdx] == colors[dstStackIdx]));
        if (canMakeMove) {
            colors[dstStackIdx] = colors[srcStackIdx];
            heights[dstStackIdx] += heights[srcStackIdx];
            colors[srcStackIdx] = m_noColor;
            heights[srcStackIdx] = 0;
        }
        return canMakeMove;
    }

    int m_dim = 12;
    char m_g = 'g';
    char m_g = 'b';
    char m_g = 'y';
    char m_g = 'w';
    char m_noColor = 'n';
};
