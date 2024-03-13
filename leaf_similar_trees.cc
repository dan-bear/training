/**
 * https://leetcode.com/problems/leaf-similar-trees
 * #bst #BST #inorder-traversal
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
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int> leaves1Vals;
        vector<int> leaves2Vals;
        fillLeaves(root1, leaves1Vals);
        fillLeaves(root2, leaves2Vals);
        bool res = leaves1Vals.size() == leaves2Vals.size();
        for(int idx = 0; res && idx < leaves1Vals.size(); idx++){
            res = (leaves1Vals[idx] == leaves2Vals[idx]);
        }
        return res;
    }

private:
    void fillLeaves(TreeNode* pRoot, vector<int>& leavesVals){
        if(isLeaf(pRoot)){
            leavesVals.push_back(pRoot->val);
        }else{
            if(pRoot->left){
                fillLeaves(pRoot->left, leavesVals);
            }
            if(pRoot->right){
                fillLeaves(pRoot->right, leavesVals);
            }
        }
    }

    bool isLeaf(TreeNode* pNode){
        return ((!pNode->left) && (!pNode->right));
    }
};
