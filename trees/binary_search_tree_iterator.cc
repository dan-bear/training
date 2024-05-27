/**
 * https://leetcode.com/problems/binary-search-tree-iterator/
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
 *
 * Algorithm:
 * 1: On initialization, get to the left-most leaf and keep the search-path
 *    in a stack.
 * 2: When next is called:
 *    print the value of the node stored in the stack's top.
 *    pop it from the stack.
 *    if it has a right descendent:
 *        Go to the left most leaf in the right subtree and add the search
 *        path to the stack.
 *
 * Note: hasNext asks whether it's the last node in the traverse or not.
 *       It's not phrased very well.
 */
class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        reachLeftMostInSubtree(root);
    }
    
    int next() {
        TreeNode* pCurrNode = m_path.top();
        m_path.pop();
        reachLeftMostInSubtree(pCurrNode->right);
        return pCurrNode->val;
    }
    
    bool hasNext() {
        return !m_path.empty();
    }
private:
    stack<TreeNode*> m_path;

    void reachLeftMostInSubtree(TreeNode* root){
        while(root != nullptr){
            m_path.push(root);
            root = root->left;
        }
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
