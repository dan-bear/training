/**
 * https://leetcode.com/problems/path-sum-iii
 * #bst #BST #recursion #recursive
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
    int pathSum(TreeNode* root, int targetSum) {
        if(root){
            ///count the number of summed paths from the root.
            calcNumOfSummedPathes(root, static_cast<int64_t>(targetSum));
            ///now let's do it again without the root.
            pathSum(root->left, static_cast<int64_t>(targetSum));
            pathSum(root->right, static_cast<int64_t>(targetSum));
        }
        return m_count;
    }
private:
    int m_count = 0;

    void calcNumOfSummedPathes(TreeNode* pRoot, int64_t targetSum){
        if(pRoot){
            targetSum -= static_cast<int64_t>(pRoot->val);
            if(targetSum == 0){
                m_count++;
            }
            calcNumOfSummedPathes(pRoot->left, targetSum);
            calcNumOfSummedPathes(pRoot->right, targetSum);
        }
    }
};
