/**
 * https://leetcode.com/problems/binary-tree-level-order-traversal/
 * #tree #bfs #binary_tree
 *
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(root){
            queue<TreeNode*> q;
            q.push(root);
            while(!q.empty()){
                int numOfNodesInLevel = q.size();
                vector<int> levelVals;
                for(int nodeNum = 1; nodeNum <= numOfNodesInLevel; nodeNum++){
                    TreeNode* pNode = q.front();
                    q.pop();           
                    levelVals.push_back(pNode->val);
                    if(pNode->left){
                        q.push(pNode->left);
                    }
                    if(pNode->right){
                        q.push(pNode->right);
                    }
                }
                res.push_back(levelVals);
            }
        }
        return res;
    }
private:

};
