/**
 * https://leetcode.com/problems/average-of-levels-in-binary-tree
 * #bfs #binary_tree
 */
 
/**
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
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> res;
        queue<TreeNode*> nodesQ;
        nodesQ.push(root);
        while(!nodesQ.empty()){
            int numOfVals = nodesQ.size();
            double sum = 0;
            for(int valIdx = 0; valIdx < numOfVals; valIdx++){
                TreeNode* pNode = nodesQ.front();
                nodesQ.pop();
                sum += pNode->val;
                if(pNode->left){
                    nodesQ.push(pNode->left);
                }
                if(pNode->right){
                    nodesQ.push(pNode->right);
                }
            }
            res.push_back(sum / numOfVals);
        }
        return res;
    }
};
