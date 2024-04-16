# https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero
# #bfs #graph #directed #edge_manipulation
class Solution:
    def minReorder(self, n: int, connections: List[List[int]]) -> int:
        #step0: multiply the edges and add weights, the current
        #       direction weight is 1, the opposite direction side
        #       is 0.
        #step1: start a bfs traversal from 0.
        #       if 0 -> i is in the original connections, it means
        #       that the edge should be flipped, in the previous
        #       step, its weight is 1, so just count the weight.
        #       otherwise, it means the original connection has the
        #       the edge 0 <- i, so the weight of 0 -> i is 0 which
        #       corresponds to fact that 0 <- i should not be flipped.

        edgeHash = self.calcBedirectedGraph(connections)
        
        flipCount = 0
        visitedNodes = [False for _ in range(n)]
        visitedNodes[0] = True
        bfsQueue = deque()
        bfsQueue.append(0)
        while bfsQueue:
            currentNode = bfsQueue[0]
            bfsQueue.popleft()
            for connection in edgeHash[currentNode]:
                if not visitedNodes[connection[0]]:
                    visitedNodes[connection[0]] = True
                    bfsQueue.append(connection[0])
                    flipCount += connection[1]

        return flipCount            

    def calcBedirectedGraph(self, connections: List[List[int]]) -> dict:
        edgeHash = dict()
        for connection in connections:
            srcNode = connection[0]
            dstNode = connection[1]
            self.addEdge(edgeHash, srcNode, dstNode, 1)
            self.addEdge(edgeHash, dstNode, srcNode, 0)
        
        return edgeHash

    def addEdge(self, edgeHash, srcNode, dstNode, weight):
        if srcNode not in edgeHash:
            edgeHash[srcNode] = [[dstNode, weight]]
        else:
            edgeHash[srcNode].append([dstNode, weight])
