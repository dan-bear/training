/**
 * https://leetcode.com/problems/shortest-path-in-binary-matrix/
 * #meta #bfs #backtracking
 */
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        m_gridLastIdx = grid.size() - 1;
        if(grid[0][0] == skViableStepSymbol &&
           grid[m_gridLastIdx][m_gridLastIdx] == skViableStepSymbol){
            //exceeds the time limit in the 49th test.
            //backTrackShortestPath(grid, 0, 0, 1);
            
            //excceeds the time limit in the 64th test.
            bfsShortestPath(grid);
        }
        m_minLen = m_minLen == numeric_limits<int>::max() ? skNoPathRetVal : m_minLen;
        return m_minLen;
    }

private:
    static constexpr int skNoPathRetVal{-1};
    static constexpr int skVisitedSymbol{2};
    static constexpr int skViableStepSymbol{0};
    int m_minLen{numeric_limits<int>::max()};
    int m_gridLastIdx{-1};
    vector<pair<int, int>> m_dirs = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1},
                                  {1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    
    void bfsShortestPath(vector<vector<int>>& grid){
        queue<pair<int, int>> coordinates;
        coordinates.push({0, 0});
        int length = 1;
        int row = -1;
        int col = -1;
        while(!coordinates.empty()){
            int numOfCoordinates = coordinates.size();
            for(int step = 0; step < numOfCoordinates; step++){
                row = coordinates.front().first;
                col = coordinates.front().second;
                coordinates.pop();
                grid[row][col] = skVisitedSymbol;

                if(row == m_gridLastIdx && col == m_gridLastIdx){
                    ///found it, time to finish.
                    m_minLen = length;
                    return;
                }
                
                for(const pair<int,int>& dir : m_dirs){
                    if(isValidStep(grid, row, col, dir)){
                        coordinates.push({row + dir.first, col + dir.second});
                    }
                }
            }
            length += 1;
        }
    }

    void backTrackShortestPath(vector<vector<int>>& grid, int row, int col, int pathLen){
        if(row == m_gridLastIdx && col == m_gridLastIdx){
            m_minLen = min(m_minLen, pathLen);
        }else{
            for(const pair<int, int>& dir : m_dirs){
                if(isValidStep(grid, row, col, dir)){
                    grid[row][col] = skVisitedSymbol;
                    backTrackShortestPath(grid, row + dir.first, col + dir.second, pathLen + 1);
                    grid[row][col] = skViableStepSymbol;
                }
            }
        }
    }

    bool isValidStep(const vector<vector<int>>& grid,
                     int row,
                     int col,
                     const pair<int, int>& dir){
        return ((row + dir.first >= 0 && row + dir.first <= m_gridLastIdx) &&
                (col + dir.second >= 0 && col + dir.second <= m_gridLastIdx) &&
                (grid[row + dir.first][col + dir.second] == skViableStepSymbol));
    }
};
