/**
 * https://leetcode.com/problems/count-good-nodes-in-binary-tree
 * #bst #BST #recursion
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
    int goodNodes(TreeNode* root) {
        int max = numeric_limits<int>::lowest();
        int count = 0;
        goodNodesCounter(root, max, count);
        return count;
    }

private:
    void goodNodesCounter(TreeNode* pNode, int maxTillHere, int& rCount){
        if(pNode){
            if(pNode->val >= maxTillHere){
                rCount += 1;
                maxTillHere = pNode->val;
            }
            goodNodesCounter(pNode->left, maxTillHere, rCount);
            goodNodesCounter(pNode->right, maxTillHere, rCount);     
        }
    }
};
