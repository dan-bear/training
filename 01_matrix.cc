/**
 * https://leetcode.com/problems/01-matrix
 */

#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

class BFSSolution
{
  public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat)
    {
        int rowDim = mat.size();
        int colDim = mat[0].size();
        vector<vector<int>> res(rowDim,
                                vector<int>(colDim, skInvalidDist));

        queue<pair<int, int>> currDistQ;
        fillQueueWithZeroCoordinates(mat, res, currDistQ);

        int currentDist = 0;
        bool isMatExhausted = false;
        while (isMatExhausted == false) {
            isMatExhausted =
              fillCurrentDistance(mat, currentDist, res, currDistQ);
            currentDist += 1;
        }

        return res;
    }

  private:
    static constexpr int skInvalidDist{ -1 };
    static constexpr int skAddedToQueue{ -2 };

    const vector<pair<int, int>> m_kDirs = { /*up*/ { -1, 0 },
                                             /*down*/ { 1, 0 },
                                             /*right*/ { 0, 1 },
                                             /*left*/ { 0, -1 } };

    void fillQueueWithZeroCoordinates(
      const vector<vector<int>>& mat,
      vector<vector<int>>& distMat,
      queue<pair<int, int>>& coordinatesQOut)
    {
        int rowDim = mat.size();
        int colDim = mat[0].size();
        for (int rowIdx = 0; rowIdx < rowDim; rowIdx++) {
            for (int colIdx = 0; colIdx < colDim; colIdx++) {
                if (mat[rowIdx][colIdx] == 0) {
                    coordinatesQOut.push(
                      pair<int, int>(rowIdx, colIdx));
                    distMat[rowIdx][colIdx] = skAddedToQueue;
                }
            }
        }
    }

    bool fillCurrentDistance(const vector<vector<int>>& mat,
                             const int currentDist,
                             vector<vector<int>>& distMatOut,
                             queue<pair<int, int>>& currDistQInOut)
    {

        bool bIsExhausted = false;
        int numOfCoordinates = currDistQInOut.size();
        if (numOfCoordinates == 0) {
            bIsExhausted = true;
        } else {
            for (int coorIdx = 0; coorIdx < numOfCoordinates;
                 coorIdx++) {
                pair<int, int> coor = currDistQInOut.front();
                currDistQInOut.pop();
                distMatOut[coor.first][coor.second] = currentDist;
                addNeighborsToQueue(coor, distMatOut, currDistQInOut);
            }
        }

        return bIsExhausted;
    }

    void addNeighborsToQueue(const pair<int, int>& coor,
                             vector<vector<int>>& distMat,
                             queue<pair<int, int>>& nextDistQOut)
    {
        int rowDim = distMat.size();
        int colDim = distMat[0].size();

        for (const pair<int, int>& dir : m_kDirs) {
            pair<int, int> neighborCoor(coor.first + dir.first,
                                        coor.second + dir.second);

            if (validCoor(neighborCoor, rowDim, colDim)) {
                if (distMat[neighborCoor.first]
                           [neighborCoor.second] == skInvalidDist) {

                    nextDistQOut.push(neighborCoor);

                    // make sure it's not added by another member.
                    distMat[neighborCoor.first][neighborCoor.second] =
                      skAddedToQueue;
                }
            }
        }
    }

    bool validCoor(const pair<int, int>& coor, int rowDim, int colDim)
    {
        return (coor.first >= 0 && coor.second >= 0 &&
                coor.first < rowDim && coor.second < colDim);
    }
};

// class DPSolution
// {
//   public:
//     vector<vector<int>> updateMatrix(vector<vector<int>>& mat)
//     {
//         m_rowDim = mat.size();
//         m_colDim = mat[0].size();
//         m_kInvalidDist =
//           m_rowDim + m_colDim; // max dist is rowDim + colDim - 2
//         vector<vector<int>> res(
//           m_rowDim, vector<int>(m_colDim, m_kInvalidDist));
//         markZerosDist(mat, res);
//         calcDistByLeftUpNeighbors(res);
//         calcDistByRightDownNeighbors(res);

//         return res;
//     }

//   private:
//     int m_kInvalidDist{ -1 };
//     int m_rowDim{ -1 };
//     int m_colDim{ -1 };

//     const pair<int, int> m_kUpNeighborDir{ -1, 0 };
//     const pair<int, int> m_kDownNeighborDir{ 1, 0 };
//     const pair<int, int> m_kLeftNeighborDir{ 0, -1 };
//     const pair<int, int> m_kRightNeighborDir{ 0, 1 };

//     void markZerosDist(const vector<vector<int>>& mat,
//                        vector<vector<int>>& distOut)
//     {
//         for (int rowIdx = 0; rowIdx < m_rowDim; rowIdx++) {
//             for (int colIdx = 0; colIdx < m_colDim; colIdx++) {
//                 if (mat[rowIdx][colIdx] == 0) {
//                     distOut[rowIdx][colIdx] = 0;
//                 }
//             }
//         }
//     }

//     struct CalcDistParams
//     {
//         int m_firstCol;
//         int m_lastCol;
//         int m_firstRow;
//         int m_lastRow;
//         int m_colDir;
//         int m_rowDir;
//         const pair<int, int>& m_firstNeighborDir;
//         const pair<int, int>& m_secondNeighborDir;
//     };

//     void calcDistByLeftUpNeighbors(vector<vector<int>>& distInOut)
//     {
//         CalcDistParams params{ 0,
//                                m_colDim - 1,
//                                0,
//                                m_rowDim - 1,
//                                1,
//                                1,
//                                m_kUpNeighborDir,
//                                m_kLeftNeighborDir };
//         calcDistByNeighbors(params, distInOut);
//     }

//     void calcDistByRightDownNeighbors(vector<vector<int>>& distInOut)
//     {
//         CalcDistParams params{
//             m_colDim - 1, 0,  m_rowDim - 1,       0,
//             -1,           -1, m_kDownNeighborDir, m_kRightNeighborDir
//         };
//         calcDistByNeighbors(params, distInOut);
//     }

//     void calcDistByNeighbors(const CalcDistParams& params,
//                              vector<vector<int>>& distOut)
//     {
//         for (int colIdx = params.m_firstCol;
//              colIdx <= params.m_lastCol && colIdx >= 0;
//              colIdx += params.m_colDir) {
//             for (int rowIdx = params.m_firstRow;
//                  rowIdx <= params.m_lastRow && rowIdx >= 0;
//                  rowIdx += params.m_rowDir) {
//                 if (distOut[rowIdx][colIdx] == m_kInvalidDist) {
//                     int dist =
//                       calcDistance(rowIdx,
//                                    colIdx,
//                                    distOut,
//                                    params.m_firstNeighborDir,
//                                    params.m_secondNeighborDir);

//                     distOut[rowIdx][colIdx] = dist;
//                 }
//             }
//         }
//     }

//     int calcDistance(int rowIdx,
//                      int colIdx,
//                      const vector<vector<int>>& distMat,
//                      const pair<int, int>& firstDir,
//                      const pair<int, int>& secondDir)
//     {
//         pair<int, int> firstDirNeighborCoor(rowIdx + firstDir.first,
//                                             colIdx + firstDir.second);

//         int firstNeighborDist =
//           isValidCoor(firstDirNeighborCoor)
//             ? distMat[firstDirNeighborCoor.first]
//                      [firstDirNeighborCoor.second]
//             : m_kInvalidDist;

//         pair<int, int> secondDirNeighborCoor(
//           rowIdx + secondDir.first, colIdx + secondDir.second);

//         int secondNeighborDist =
//           isValidCoor(secondDirNeighborCoor)
//             ? distMat[secondDirNeighborCoor.first]
//                      [secondDirNeighborCoor.second]
//             : m_kInvalidDist;

//         int previouslyCalcedDist = distMat[rowIdx][colIdx];

//         int dist = min(min(firstNeighborDist, secondNeighborDist) + 1,
//                        previouslyCalcedDist);
//         return dist;
//     }

//     bool isValidCoor(pair<int, int> coor)
//     {
//         return (coor.first >= 0 && coor.second >= 0 &&
//                 coor.first < m_rowDim && coor.second < m_colDim);
//     }
// };

class Solution
{
  public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat)
    {
        BFSSolution sol;
        //DPSolution sol; DOES NOT WORK...
        return sol.updateMatrix(mat);
    }
};

int
main()
{
    Solution sol;
    vector<vector<int>> mat({ vector<int>({ 0 }),
                              vector<int>({ 0 }),
                              vector<int>({ 0 }),
                              vector<int>({ 0 }),
                              vector<int>({ 0 }) });

    vector<vector<int>> res = sol.updateMatrix(mat);
    return 0;
}
