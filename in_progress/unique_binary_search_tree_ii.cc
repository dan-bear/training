/**
 * https://leetcode.com/problems/unique-binary-search-trees-ii/
 * #BST #bst #TREE #tree #binary-tree
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
    vector<TreeNode*> generateTrees(int n) {
        
    }
private:
    /// It's assumed pRoot is not nullptr.
    /// i.e. the tree is not completely empty.
    void insert(TreeNode* pRoot, int newVal){
        if(pRoot->val < newVal){
            if(pRoot->right->val > newVal){
                insert(pRoot->right, newVal);
            }else{
                //need to be the root right decendent
                TreeNode* pNewNode = new TreeNode;
                pNewNode->val = newVal;
                pNewNode->left = pRoot->right;
                pNewNode->right = nullptr;
                pRoot->right = pNewNode;
            }
        }
    }

};



//1 2 3
//BST => in order leads to 1 2 3
//if the insert algorithm is correct, does the order
//of insert makes it work?
//1 -> 2 -> 3
//1 -> 3 -> 2
//2 -> 1 -> 3 when the root is the middle value
//2 -> 3 -> 1 the trees are the same.
//3 -> 1 -> 2
//3 -> 2 -> 1


1 2
//1 -> 2 //1 is root, 2 is inserted to its right.
//2 -> 1 //2 is root, 1 is inserted to its left.

