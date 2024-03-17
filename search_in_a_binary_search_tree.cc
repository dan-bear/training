/**
 * https://leetcode.com/problems/search-in-a-binary-search-tree
 * #bst #BST #recursion #search
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
    TreeNode* searchBST(TreeNode* root, int val) {
        //return iterativeSearchBST(root, val);
        return recursiveSearchBST(root, val);
    }
private:
    TreeNode* recursiveSearchBST(TreeNode* pRoot, int val){       
        if(!pRoot){
            return nullptr;
        }
        if(pRoot->val == val){
            return pRoot;
        }
        if(pRoot->val > val){
            return searchBST(pRoot->left, val);
        }
        //if(pRoot->val < val)
        return searchBST(pRoot->right, val);
    }

    TreeNode* iterativeSearchBST(TreeNode* pRoot, int val){
        TreeNode* pRes = nullptr;
        while(!pRes && pRoot){
            if(pRoot->val == val){
                pRes = pRoot;
            }else if(pRoot->val > val){
                pRoot = pRoot->left;
            }else{
                pRoot = pRoot->right;
            }
        }
        return pRes;
    }
};
