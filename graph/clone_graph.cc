/**
 * https://leetcode.com/problems/clone-graph
 * #graph #GRAHP #bfs #dfs
 */

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    /**
     * 1: There might be cycles in the graph.
     *   1.1: How to avoid cycles in BFS run?
     *   1.2: How to avoid cycles in DFS run?
     */
    Node* cloneGraph(Node* node) {
        if(!node){
            return nullptr;
        }
        unordered_map<int, vector<int>>graph;
        buildGraph(node, graph);
        Node* pCloneStart = buildClone(graph);
        return pCloneStart;
    }
private:
    Node* buildClone(unordered_map<int, vector<int>>& graph){
        vector<Node*> nodes(graph.size(), nullptr);
        for(int idx = 0; idx < graph.size(); idx++){
            nodes[idx] = new Node(idx + 1);
        }
        for(int idx = 0; idx < graph.size(); idx++){
            for(int neighbor : graph[idx + 1]){
                nodes[idx]->neighbors.push_back(nodes[neighbor - 1]);
            }
        }
        return nodes[0];
    }

    void buildGraph(Node* pStartNode, unordered_map<int, vector<int>>& graph){
        queue<Node*> bfsQ;
        bfsQ.push(pStartNode);
        while(!bfsQ.empty()){
            Node* pNode = bfsQ.front();
            bfsQ.pop();
            vector<int> neighborsVals(pNode->neighbors.size(), 0);
            for(int idx = 0; idx < pNode->neighbors.size(); idx++){
                ///Save the neighbors values.
                neighborsVals[idx] = pNode->neighbors[idx]->val;
                if(graph.find(neighborsVals[idx]) == graph.end()){
                    ///have not visited it yet, so add it to the bfsQ
                    bfsQ.push(pNode->neighbors[idx]);
                }
            }
            graph[pNode->val] = neighborsVals;
        }
    }
};
