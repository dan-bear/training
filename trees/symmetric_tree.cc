/**
 * https://leetcode.com/problems/symmetric-tree
 * #binary_tree #recursion
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
    /**
     * inorder traversal - left, middle, right
     * reverse-in-order traversal - right, middle, left
     * Approach1: use memory, run the traversals and save the results in a vector,
     *            then compare the results.
     * Approach2: Use two iterators and stack and use the next() and compare method.
     *            It demands O(tree height) space.
     * Approach3: Iterate using recursion (O(#nodes) time O(tree_height) space).
     *            1: start with itr1, itr2 both starts by pointing to root->left
     *               and root->right.
     *            2: If one of the iterators is nullptr:
     *               return true iff both iterators are nullptrs.
     *            3: compare the values in the iterators, if they are not equal
     *               return false.
     *            4: recursive call with: itr1->left, itr2->right
     *            5: if previous call returns true, recursive call with:
     *               itr1->right, itr2->left.
     *
     */
    bool isSymmetric(TreeNode* root) {
        return isSymmetricTwoItrsRecursion(root->left, root->right);
    }
private:
    bool isSymmetricTwoItrsRecursion(TreeNode* pItr1, TreeNode* pItr2){
        if(pItr1 == nullptr || pItr2 == nullptr){
            return pItr1 == pItr2;///true iff both ptrs are nullptrs.
        }
        if(pItr1->val != pItr2->val){
            return false;
        }else{
            if(isSymmetricTwoItrsRecursion(pItr1->left, pItr2->right)){
                if(isSymmetricTwoItrsRecursion(pItr1->right, pItr2->left)){
                    return true;
                }
            }
            return false;
        }
    }
};
