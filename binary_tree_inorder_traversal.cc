/**
 * https://leetcode.com/problems/binary-tree-inorder-traversal/
 * Tag: Binary Tree
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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> traverseRes;
        if(root){
            traverse(root, traverseRes);    
        }
        return traverseRes;
    }

private:
    void traverse(TreeNode* currentNode, vector<int>& traverseOut){
        if(currentNode->left){
            traverse(currentNode->left, traverseOut);
        }
        traverseOut.push_back(currentNode->val);
        if(currentNode->right){
            traverse(currentNode->right, traverseOut);
        }
    }
