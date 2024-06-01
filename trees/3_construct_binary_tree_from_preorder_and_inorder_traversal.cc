/**
 * https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal
 * #recursion #binary_tree #bst
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
#include <span>

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        ///That's the coolest approach in my opinion, but its slower.

        ///return bstApproach(preorder, inorder);
        ///return recursiveApproach(preorder, inorder);

        ///Identical logic to the refursive approach, easier to read
        ///but with performance degradation.
        span<int> preorderSpan(preorder.data(), preorder.size());
        span<int> inorderSpan(inorder.data(), inorder.size());
        return recursiveApproachUsingCpp20Spans(preorderSpan, inorderSpan);
    }
private:
    /**
     * Given preorder, the root value is in preorder[0].
     * find the index of the root in the inorder vector,
     * the inorder[0 : rootValIndex] is the left subtree.
     * the inorder[rootValIndex + 1 : inorder.size()] is the
     * right subtree.
     * So restart with the inorder slices, and the corresponding
     * preorder slices. 
     * The left subtree slice size is: rootValIndex.
     * the right subtree slice size is:
     * current-tree-size - left-subtree-size - 1 (1 for the root).
     * 
     * The inorder left subtree slice is: inorder[0 : leftSubtreeSize]
     * The inorder right subtree slice is:
     * inorder[leftSubtreeSize + 1 : leftSubtreeSize + 1 + rightSubtreeSize] 
     * The preorder left subtree slice is preorder[1 : leftSubtreeSize]
     * The preorder right subtree slice is:
     * preoder[1 + leftSubtreeSize : 1 + leftSubtreeSize + rightSubtreeSize]
     * So the recursive call should be done with the corresponding slices.
     */
    TreeNode* recursiveApproachUsingCpp20Spans(const span<int>& preorderSpan,
                                               const span<int>& inorderSpan){
        
        if(preorderSpan.size() == 0){
            return nullptr;
        }

        int rootVal = preorderSpan[0];
        TreeNode* pRoot = new TreeNode(rootVal);

        int rootValIdx = findRootValIdx(inorderSpan, rootVal);
        int leftSubtreeSize = rootValIdx;
        int rightSubtreeSize = preorderSpan.size() - 1 - leftSubtreeSize;
        
        pRoot->left = recursiveApproachUsingCpp20Spans(
            span<int>(preorderSpan.data() + 1, leftSubtreeSize),
            span<int>(inorderSpan.data(), leftSubtreeSize));

        pRoot->right = recursiveApproachUsingCpp20Spans(
            span<int>(preorderSpan.data() + 1 + leftSubtreeSize, rightSubtreeSize),
            span<int>(inorderSpan.data() + 1 + leftSubtreeSize, rightSubtreeSize));
        
        return pRoot;                               
    }

    int findRootValIdx(const span<int>& inorder, int rootVal){
        int res = -1;
        for(int idx = 0; idx < inorder.size() && res < 0; idx++){
            if(rootVal == inorder[idx]){
                res = idx;
            }
        }
        //assert(res >= 0);
        return res;
    }
    

    TreeNode* recursiveApproach(const vector<int>& preorder,
                                     const vector<int>& inorder){
        TreeNode* pRoot = recursiveApproachAux(preorder, 
                                               inorder,
                                               0,
                                               0,
                                               inorder.size());
        return pRoot;
    }

    TreeNode* recursiveApproachAux(
            const vector<int>& preorder,
            const vector<int>& inorder,
            int preorderStartIdx,
            int inorderStartIdx,
            int treeSize){
        
        if(treeSize == 0){
            return nullptr;
        }

        int rootVal = preorder[preorderStartIdx];
        int rootInorderIdx = findRootInOrderIdx(inorder,
                                                inorderStartIdx,
                                                treeSize,
                                                rootVal);
        
        int leftSubtreeSize = rootInorderIdx - inorderStartIdx;
        int rightSubtreeSize = (treeSize - 1) - leftSubtreeSize;
        int leftPreorderStartIdx = preorderStartIdx + 1;
        int rightPreorderStartIdx = (preorderStartIdx + 1) + leftSubtreeSize;
        int leftInorderStartIdx = inorderStartIdx;
        int rightInorderStartIdx = rootInorderIdx + 1;

        TreeNode* pRoot = new TreeNode(rootVal);
        pRoot->left = recursiveApproachAux(preorder,
                                           inorder,
                                           leftPreorderStartIdx,
                                           leftInorderStartIdx,
                                           leftSubtreeSize);
        
        pRoot->right = recursiveApproachAux(preorder,
                                            inorder,
                                            rightPreorderStartIdx,
                                            rightInorderStartIdx,
                                            rightSubtreeSize);
        
        return pRoot;
    }

    int findRootInOrderIdx(const vector<int>& inorder,
                           int inorderStartIdx,
                           int treeSize,
                           int rootVal){
        int res = -1;
        for(int idx = inorderStartIdx;
            idx < inorderStartIdx + treeSize && res < 0;
            idx++){
            if(inorder[idx] == rootVal){
                res = idx;
            }
        }
        return res;
    }

    class Comparator{
    public:
        Comparator(const vector<int>& order){
            for(int idx = 0; idx < order.size(); idx++){
                m_valToIndexHash[order[idx]] = idx;
            }
        }

        ///Note: the comparator assumes val1 and val2 are
        ///      comparable.
        bool isLessThan(int val1, int val2) const{
            return m_valToIndexHash.find(val1)->second < 
                m_valToIndexHash.find(val2)->second;
        }
        
    private:
        unordered_map<int, int> m_valToIndexHash;
    };
    
    /**
     * BST approach:
     * It's the same question like passing a BST through a network
     * the only difference is that the inorder traversal determines
     * the order of the between the values.
     */
    TreeNode* bstApproach(vector<int>& preorder, vector<int>& inorder) {
        Comparator comparator(inorder);
        TreeNode* pRoot = new TreeNode(preorder[0]);
        for(int idx = 1; idx < preorder.size(); idx++){
            insert(pRoot, preorder[idx], comparator);
        }
        return pRoot;
    }

    void insert(TreeNode* pRoot, int val, const Comparator& comparator){
        TreeNode** ppSubTreeRoot = 
            comparator.isLessThan(val, pRoot->val) ?
            &pRoot->left : &pRoot->right;
        
        if(*ppSubTreeRoot != nullptr){
            insert(*ppSubTreeRoot, val, comparator);
        }else{
            *ppSubTreeRoot = new TreeNode(val);
        }
    }

    bool isLessThan(int val1, int val2, const vector<int>& inorder){
        bool res = false;
        for(int val : inorder){
            if(val == val1){
                res =  true; ///val1 appears before val2.
                break;
            }else if(val == val2){
                res = false; ///val2 appears before val1.
                break;
            }
        }
        return res;
    }
};
