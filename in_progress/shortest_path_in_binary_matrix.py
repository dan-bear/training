# https://leetcode.com/problems/shortest-path-in-binary-matrix/
# #meta #backtracing #bfs #queue

class Solution:
    #back tracking?
    def __init__(self):
        self.min_len = - 1
        self.dirs = [[1, 1], [1, -1], [-1, -1], [-1, 1], [1, 0], [0, 1], [-1, 0], [0, -1]]
        self.gridIdxDim = -1

    
    def shortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:
        self.gridIdxDim = len(grid) - 1
        if self.gridIdxDim == 0:
            self.min_len = 1 if grid[0][0] == 0 else -1
        else:
            self.recursiveTraverse(grid, 0, 0, 1)

        return self.min_len    

    def recursiveTraverse(self, grid : List[List[int]], row : int, col : int, pathLen : int):
        if(col == row == self.gridIdxDim):
            self.min_len = min(self.min_len, pathLen)
        else:
            for direction in self.dirs:
                if self.isValidDir(grid, row, col, direction):
                    self.recursiveTraverse(grid,\
                                           row + direction[0],\
                                           col + direction[1],\
                                           pathLen + 1)

    def isValidDir(self, grid: List[List[int]], row: int, col: int, direction: List[int]) -> bool:
        return (0 <= row + direction[0] <= self.gridIdxDim and\
                0 <= col + direction[1] <= self.gridIdxDim and\
                grid[row + direction[0]][col + direction[1]] == 0)
