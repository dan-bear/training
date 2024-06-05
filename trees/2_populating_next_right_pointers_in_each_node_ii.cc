/**
 * https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii
 * #bfs #binary_tree
 */

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        if(root){
            queue<Node*> bfsQ;
            bfsQ.push(root);
            while(bfsQ.empty() == false){
                int currentLayerSize = bfsQ.size();
                Node* pNode = nullptr;
                for(int nodeIdx = 0; nodeIdx < currentLayerSize - 1; nodeIdx++){
                    pNode = bfsQ.front();
                    bfsQ.pop();
                    pNode->next = bfsQ.front();
                    pushDecendents(pNode, bfsQ);
                }
                ///One more time for the last node in the layer 
                ///(to avoid additional condition in the for loop).
                pNode = bfsQ.front();
                bfsQ.pop();
                pushDecendents(pNode, bfsQ);
            }
        }
        return root;
    }
private:
    void pushDecendents(Node* pNode, queue<Node*>& bfsQ){
        if(pNode->left){
            bfsQ.push(pNode->left);
        }
        if(pNode->right){
            bfsQ.push(pNode->right);
        }
    }
};
