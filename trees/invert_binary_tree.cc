/**
 * https://leetcode.com/problems/invert-binary-tree
 * #binary_tree
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
    TreeNode* invertTree(TreeNode* root) {
        invertTreeInternal(root);
        return root;
    }
private:
    void invertTreeInternal(TreeNode* pRoot){
        if(pRoot){
            TreeNode* pLeft = pRoot->left;
            TreeNode* pRight = pRoot->right;
            pRoot->left = pRight;
            pRoot->right = pLeft;
            invertTree(pRoot->left);
            invertTree(pRoot->right);
        }
    }
};
