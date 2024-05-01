# https://leetcode.com/problems/nearest-exit-from-entrance-in-maze
# #bfs #BFS #queue

class Solution:    
    def nearestExit(self, maze: List[List[str]], entrance: List[int]) -> int:
        self.WALL = '+'
        self.EMPTY = '.'
        steps = deque()
        steps.append(entrance)
        maze[entrance[0]][entrance[1]] = self.WALL
        currentDistance = 0
        dirs = [[1, 0], [0, 1], [-1, 0], [0, -1]]
        while steps:
            currentDistance += 1
            numOfSteps = len(steps)
            for _ in range(numOfSteps):
                step = steps.popleft()
                for direction in dirs:
                    nextStep = [step[0] + direction[0], step[1] + direction[1]]
                    if self.isValidStep(maze, nextStep):
                        if self.isExitStep(maze, nextStep):
                            return currentDistance
                        else:
                            maze[nextStep[0]][nextStep[1]] = self.WALL
                            steps.append(nextStep)
        
        return -1

    def isValidStep(self, maze: List[List[str]], step: List[int]) -> bool:
        res = (0 <= step[0] < len(maze)) and\
              (0 <= step[1] < len(maze[0])) and \
              maze[step[0]][step[1]] == self.EMPTY
        return res

    def isExitStep(self, maze: List[List[str]], step: List[int]) -> bool:
        res = step[0] == 0 or\
              step[1] == 0 or\
              step[0] == len(maze) - 1 or\
              step[1] == len(maze[0]) - 1
        return res
