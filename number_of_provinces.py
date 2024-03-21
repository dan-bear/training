#https://leetcode.com/problems/number-of-provinces
#dfs #graph #recurssion
class Solution:
    def findCircleNum(self, isConnected: List[List[int]]) -> int:
        reachedState = [False] * len(isConnected)
        count = 0
        for idx in range(len(isConnected)):
            if not reachedState[idx]:
                count += 1
                reachedState[idx] = True
                self.expend(isConnected, reachedState, idx)
        return count

    def expend(self, 
               isConnected: List[List[int]],
               reachedState: List[bool],
               rowIdx: int):
        for colIdx in range(len(isConnected[rowIdx])):
            if isConnected[rowIdx][colIdx]:
                if not reachedState[colIdx]:
                    reachedState[colIdx] = True
                    self.expend(isConnected, reachedState, colIdx)
