# https://leetcode.com/problems/shortest-path-in-binary-matrix/
# #meta #backtracing #bfs #queue

class Solution:
    def __init__(self):
        self.minLen = - 1
        self.dirs = [[1, 1], [1, -1], [-1, -1], [-1, 1], [1, 0], [0, 1], [-1, 0], [0, -1]]
        self.gridIdxDim = -1
        self.invalidSymbol = 2
    
    def shortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:
        return self.backtrackingShortestPathBinaryMatrix(grid)
        #return self.bfsShortestPathBinaryMatrix(grid)

    def bfsShortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:
        self.gridIdxDim = len(grid) - 1
        if grid[self.gridIdxDim][self.gridIdxDim] != 0 or grid[0][0] == 1:
            return -1

        distance = 1
        bfsQueue = deque()
        bfsQueue.append([0, 0])
        while bfsQueue:
            numOfCoordinates = len(bfsQueue)
            for _ in range(numOfCoordinates):
                coordinate = bfsQueue.popleft()
                row = coordinate[0]
                col = coordinate[1]
                
                if row == col == self.gridIdxDim:
                    return distance
                        
                for direction in self.dirs:
                    if self.isValidDir(grid, row, col, direction):
                        bfsQueue.append([row + direction[0], col + direction[1]])
                        grid[row + direction[0]][col + direction[1]] = self.invalidSymbol
            
            distance += 1
        
        #could not reach the last position.
        return -1

    def backtrackingShortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:
        invalidPathLen = pow(len(grid), 2) + 1 #+1 is needed when grid is [[0]] 
        self.minLen = invalidPathLen
        self.gridIdxDim = len(grid) - 1
        if grid[self.gridIdxDim][self.gridIdxDim] != 0 or grid[0][0] == 1:
            self.minLen = -1
        else:
            self.recursiveTraverse(grid, 0, 0, 1)
            if self.minLen == invalidPathLen:
                self.minLen = -1

        return self.minLen


    def recursiveTraverse(self, grid : List[List[int]], row : int, col : int, pathLen : int):
        if(col == row == self.gridIdxDim):
            self.minLen = min(self.minLen, pathLen)
        else:
            for direction in self.dirs:
                if self.isValidDir(grid, row, col, direction):
                    grid[row + direction[0]][col + direction[1]] = self.invalidSymbol
                    self.recursiveTraverse(grid,\
                                           row + direction[0],\
                                           col + direction[1],\
                                           pathLen + 1)
                    grid[row + direction[0]][col + direction[1]] = 0

    def isValidDir(self, grid: List[List[int]], row: int, col: int, direction: List[int]) -> bool:
        return (0 <= row + direction[0] <= self.gridIdxDim and\
                0 <= col + direction[1] <= self.gridIdxDim and\
                grid[row + direction[0]][col + direction[1]] == 0)
