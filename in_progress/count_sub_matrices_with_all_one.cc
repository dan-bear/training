/**
 * TODO:
 * 1: Fix brutforce approach.
 * 2: explain DP approach.
 * 3: Implement DP approach.
 * https://leetcode.com/problems/count-submatrices-with-all-one
 * #DP
 */


// #include <vector>
// #include <iostream>

// using namespace std;

class Solution
{
  public:
    int numSubmat(vector<vector<int>>& mat)
    {
        int numOfRows = mat.size();
        int numOfCols = mat[0].size();
        int numOfSubmat = 0;
        for (int rowIdx = 0; rowIdx < numOfRows; rowIdx++) {
            for (int colIdx = 0; colIdx < numOfCols; colIdx++) {
                numOfSubmat += countAllSubMatFromTopLeftPosition(
                  mat, rowIdx, colIdx);
            }
        }
        return numOfSubmat;
    }

  private:
    int countAllSubMatFromTopLeftPosition(vector<vector<int>>& mat,
                                          int rowIdx,
                                          int colIdx)
    {

        int maxNumOfRowsInSubMat = mat.size() - rowIdx;

        int numOfSubMats = 0;
        for (int subMatNumOfRows = 1;
             subMatNumOfRows < maxNumOfRowsInSubMat;
             subMatNumOfRows++) {

            numOfSubMats += calcSubMatOfGivenNumOfRows(
              mat, rowIdx, colIdx, subMatNumOfRows);
        }

        return numOfSubMats;
    }

    int calcSubMatOfGivenNumOfRows(vector<vector<int>>& mat,
                                   int rowIdx,
                                   int colIdx,
                                   int subMatNumOfRows)
    {

        int numOfSubMat = 0;
        int maxNumOfColsInSubMat = mat[0].size() - colIdx;
        for (int currentColIdx = colIdx;
             currentColIdx < colIdx + maxNumOfColsInSubMat;
             currentColIdx++) {
            
            if (findZeroInCol(mat, rowIdx, colIdx, subMatNumOfRows)) {
                break;
            }

            numOfSubMat++;
        }
        return numOfSubMat;
    }

    bool findZeroInCol(vector<vector<int>>& mat,
                       int rowIdx,
                       int colIdx,
                       int subMatNumOfRows)
    {
        bool bZeroFound = false;

        for (int currentRowIdx = rowIdx;
             currentRowIdx < rowIdx + subMatNumOfRows;
             currentRowIdx++) {
    
            if (mat[currentRowIdx][colIdx] == 0) {
                bZeroFound = true;
                break;
            }
        }

        return bZeroFound;
    }
};
