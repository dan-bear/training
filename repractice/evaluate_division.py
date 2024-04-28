#https://leetcode.com/problems/evaluate-division
# #graph #dfs #directed_graph #weights #hash_table

#Think about the equations and values as directed
#edges and weights on a graph.
#For every equation, add the opposite edge with 1/value
#as its weight.
#given an query C, D. Search for a path (without circles) from
#C to D and multiply the weights. If there is no path or one
#of the edges (C or D) does not exist, return -1.
#
# How to deal with cycles?
# The assumption that there is not contradiction
# in the equations means there are not cycles.
class Solution:
    def calcEquation(self, equations: List[List[str]], values: List[float], queries: List[List[str]]) -> List[float]:
        graph = self.buildGraph(equations, values)
        result : List[float] = [-1.0 for _ in range(len(queries))]
        for idx, query in enumerate(queries):
            result[idx] = self.calcEquationRes(graph, query)
        return result

    
    def calcEquationRes(self, graph, query: List[str]) -> float:
        nodeHisto : dict[str, bool] = dict()
        srcNode : str = query[0]
        dstNode : str = query[1]
        res : float = -1.0
        if srcNode in graph and dstNode in graph:
            res = self.findAndMultPath(graph, nodeHisto, srcNode, dstNode, 1.0)
        
        return res

    def findAndMultPath(self,
                        graph,
                        nodeHisto: dict[str, bool],
                        srcNode: str,
                        dstNode: str,
                        currentMult: float) -> float:
        if srcNode == dstNode:
            return currentMult
        
        for neighborAndWeight in graph[srcNode]:
            neighbor : str = neighborAndWeight[0]
            weight : float = neighborAndWeight[1]
            if neighbor not in nodeHisto or not nodeHisto[neighbor]:
                nodeHisto[neighbor] = True
                res : float = self.findAndMultPath(graph, nodeHisto, neighbor, dstNode, currentMult * weight)
                if res > 0.0:
                    return res
                
                nodeHisto[neighbor] = False
        
        return -1.0


    def buildGraph(self, equations: List[List[str]], values: List[float]):
        graph = dict()
        for idx in range(len(equations)):
            self.addEdge(graph, equations[idx], values[idx])

        return graph


    def addEdge(self, graph, equation: List[str], value: float) -> None:
        self.addEdgeWithWeight(graph, equation[0], equation[1], value)
        self.addEdgeWithWeight(graph, equation[1], equation[0], 1 / value)
        
    def addEdgeWithWeight(self, graph, srcNode: str, dstNode: str, value: float) -> None:
        if srcNode in graph:
            graph[srcNode].append([dstNode, value])
        else:
            graph[srcNode] = [[dstNode, value]]






