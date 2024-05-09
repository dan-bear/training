/**
 * https://leetcode.com/problems/clone-graph
 * #graph #GRAHP #bfs #dfs
 * #interesting # INTERESTING # GOOD
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
    Node* cloneGraph(Node* node) {
        if(node == nullptr){
            return nullptr;
        }
        //return copyValuesAndBuildGraph(node);
        //return bfsWithoutCopyingVals(node);
        return dfsSolution(node);
    }

    
private:
    Node* dfsSolution(Node* pStartNode){
        unordered_map<Node*, Node*> originAndCloneMap;
        dfsGraphBuild(originAndCloneMap, pStartNode);
        return originAndCloneMap[pStartNode];
    }

    void dfsGraphBuild(unordered_map<Node*, Node*>& originAndCloneMap, Node* pNode){
        Node* pClone = new Node(pNode->val);
        originAndCloneMap[pNode] = pClone;
        vector<Node*> cloneNeighbors;

        for(Node* pNeighbor : pNode->neighbors){
            if(originAndCloneMap.find(pNeighbor) == originAndCloneMap.end()){
                dfsGraphBuild(originAndCloneMap, pNeighbor);
            }
            cloneNeighbors.push_back(originAndCloneMap[pNeighbor]);
        }
        pClone->neighbors = cloneNeighbors;
    }

    Node* bfsWithoutCopyingVals(Node* pStartNode){
        unordered_map<Node*, Node*> originAndCloneMap;
        queue<Node*> bfsQ;
        bfsQ.push(pStartNode);
        while(!bfsQ.empty()){
            Node* pNode = bfsQ.front();
            bfsQ.pop();
            
            Node* pClone = getOrAllocateClone(originAndCloneMap, pNode);
            vector<Node*> newlyReachedNodes = 
                addNeighborsToClone(originAndCloneMap, pNode, pClone);
            
            for(Node* newNode: newlyReachedNodes){
                bfsQ.push(newNode);
            }
        }
        return originAndCloneMap[pStartNode];
    }

    Node* getOrAllocateClone(unordered_map<Node*, Node*>& originAndCloneMap, Node* pNode){
        Node* pClone = nullptr;
        if(originAndCloneMap.find(pNode) == originAndCloneMap.end()){
            pClone = new Node(pNode->val);
            originAndCloneMap[pNode] = pClone;
        }else{
            pClone = originAndCloneMap[pNode];
        }
        return pClone;
    }
    

    vector<Node*> addNeighborsToClone(unordered_map<Node*, Node*>& originAndCloneMap,
                             Node* pNode,
                             Node* pClone){
        vector<Node*> newlyReachedNodes;
        vector<Node*> neighbors(pNode->neighbors.size(), nullptr);
        for(int idx = 0; idx < neighbors.size(); idx++){
            if(originAndCloneMap.find(pNode->neighbors[idx]) == 
                originAndCloneMap.end()){
                Node* pCloneNeighbor = new Node(pNode->neighbors[idx]->val);
                neighbors[idx] = pCloneNeighbor;
                originAndCloneMap[pNode->neighbors[idx]]= pCloneNeighbor;
                newlyReachedNodes.push_back(pNode->neighbors[idx]);
            }else{
                ///Already added the neighbor to the map.
                neighbors[idx]= originAndCloneMap[pNode->neighbors[idx]];
            }
        }
        pClone->neighbors = neighbors;
        return newlyReachedNodes;
    }
    
    Node* copyValuesAndBuildGraph(Node* pNode){
        unordered_map<int, vector<int>>graph;
        buildGraph(pNode, graph);
        Node* pCloneStart = buildClone(graph);
        return pCloneStart;
    }
    
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
