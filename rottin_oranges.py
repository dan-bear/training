# https://leetcode.com/problems/rotting-oranges
# #bfs #BFS #queue
# An empty cell never becomes rotten.
# Add all the rotten oranges to a queue.
# For every rotten orange - add the fresh oranges
# near it to the queue.
# once the queue is empty: check whether there are
# fresh oranges left.

class Solution:
    def orangesRotting(self, grid: List[List[int]]) -> int:
        rottenQ = deque()
        freshCount = self.addRotensToQueueAndCountFresh(grid, rottenQ)
        time = 0
        dirs = [[1, 0],[0, 1],[-1, 0],[0, -1]]
        while rottenQ:
            time += 1
            rottenLayerCount = len(rottenQ)
            for _ in range(rottenLayerCount):
                rottenPosition = rottenQ.popleft()
                for direction in dirs:
                    newPosition = [sum(entry) for entry in zip(rottenPosition, direction)]
                    if self.isFresh(grid, newPosition):
                        self.markAsRotten(grid, newPosition)
                        rottenQ.append(newPosition)
                        freshCount -= 1
                
        if time > 0:
            time -= 1
        
        res = -1 if freshCount > 0 else time
        return res
    

    def addRotensToQueueAndCountFresh(self, grid, rottenQ) -> int:
        freshCount: int = 0
        for rowIdx in range(len(grid)):
            for colIdx in range(len(grid[0])):
                if grid[rowIdx][colIdx] == 1:
                    freshCount += 1
                if grid[rowIdx][colIdx] == 2:
                    rottenQ.append([rowIdx, colIdx])

        return freshCount

    def markAsRotten(self, grid, position):
        grid[position[0]][position[1]] = 2

    def isFresh(self, grid, position):
        res: bool = self.isValidPosition(grid, position) and\
                    grid[position[0]][position[1]] == 1
        
        return res

    def isValidPosition(self, grid, position):
        res: bool = position[0] >= 0 and\
                    position[1] >= 0 and\
                    position[0] < len(grid) and\
                    position[1] < len(grid[0])
        return res
