///https://leetcode.com/problems/generate-parentheses
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution
{

  public:
    vector<string> generateParenthesis(int n)
    {
        vector<string> res;
        string workingString;
        buildParenthesis(workingString, n, n, res);
        return res;
    }

    void buildParenthesis(string& workingString,
                          int leftPare,
                          int rightPare,
                          vector<string>& resOut)
    {
        if (leftPare < 0 || rightPare < 0) {
            // do nothing.
        } else if (leftPare > rightPare) {
            // do nothing, it's an invalid embedding.
        } else if (leftPare == 0 && rightPare == 0) {
            resOut.push_back(workingString);
        } else {
            workingString.append("(");
            buildParenthesis(
              workingString, leftPare - 1, rightPare, resOut);
            workingString.pop_back();

            workingString.append(")");
            buildParenthesis(
              workingString, leftPare, rightPare - 1, resOut);
            workingString.pop_back();
        }
    }

    //     vector<string> generateParenthesis(int n)
    //     {
    //         string workingString(2 * n, skEmptyChar);
    //         int firstIdx = 0;
    //         int lastIdx = 2 * n - 1;
    //         vector<string> res;
    //         buildParenthesis(n, workingString, firstIdx, lastIdx,
    //         res); return res;
    //     }

    //   private:
    //     static constexpr char skEmptyChar = '_';
    //     static constexpr char skLeftPare = '(';
    //     static constexpr char skRightPare = ')';

    //     void buildParenthesis(int n,
    //                           string& workingStr,
    //                           int firstIdx,
    //                           int lastIdx,
    //                           vector<string>& resOut)
    //     {
    //         if (n == 0) {

    //         } else {
    //             workingStr[firstIdx] = skLeftPare;
    //             for (int charIdx = firstIdx + 1; charIdx <=
    //             lastIdx;
    //                  charIdx += 2) {
    //                 // put right parenthesis.
    //                 workingStr[charIdx] = skRightPare;

    //                 int nBetween = (charIdx - firstIdx - 1) / 2;
    //                 int nAfter = (n - 1) - nBetween;
    //                 buildParenthesis(nBetween,
    //                                  workingStr,
    //                                  firstIdx + 1,
    //                                  charIdx - 1,
    //                                  resOut);
    //                 buildParenthesis(
    //                   nAfter, workingStr, charIdx + 1, lastIdx,
    //                   resOut);

    //                 if (workingStrIsCompleted(workingStr)) {
    //                     string copy = workingStr;
    //                     resOut.push_back(copy);
    //                     // resOut.insert(resOut.begin(), copy);
    //                 }
    //                 // remove right parenthesis
    //                 // workingStr[charIdx] = skEmptyChar;
    //             }
    //         }
    //     }

    //     bool workingStrIsCompleted(const string& kWorkingStr)
    //     {
    //         bool bRes = true;
    //         for (int charIdx = 0; charIdx < kWorkingStr.length();
    //              charIdx++) {
    //             if (kWorkingStr[charIdx] == skEmptyChar) {
    //                 bRes = false;
    //                 break;
    //             }
    //         }
    //         return bRes;
    //     }
};


int
main()
{
    vector<string> res = Solution().generateParenthesis(3);
    for (int idx = 0; idx < res.size(); idx++) {
        cout << res[idx] << endl;
    }
}
