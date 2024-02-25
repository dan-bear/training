/**
 * https://leetcode.com/problems/unique-binary-search-trees-ii/
 * #BST #bst #TREE #tree #binary-tree
 * #recursion #RECURSION #DP #dp
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
     * for i < j: define trees[i][j] to be all the BSTs containing
     * the range {i, i+1,...,j}.
     * trees[i][i] - is a tree containing only a node.
     * trees[i][i+1] can be calculated by iterating {i, i+1} and:
     * 1: create a root with val = i and connect the trees in 
     *    trees[i+1][i+1] (as right subtrees).
     * 2: create a root with val = i+1 and connect the trees in
     *    trees[i][i] (as left subtree).
     * Let's make another step to make the recursion a little bit more
     * clear.
     * trees[i][]i+2] can be calculating by iterating {i, i+1, i+2} and:
     * 1: create a root with val = i and connect the trees in trees[i+1][i+2]
     *    as right subtrees.
     * 2: create a root with val = i + 1 and connect the trees in trees[i][i]
     *    as left subtrees and the trees in trees[i+2][i+2] as right subtrees.
     * 3: create a root with val = i + 2 and connect the trees in trees[i][i+1]
     *    as left subtrees.
     *
     * So, in general, for trees[i][j]:
     * - itereate i <= k <= j
     *   - create root with val = k.
     *   - add all the trees in trees[i][k-1] to its left subtree.
     *   - add all the trees in trees[k+1][j] to its right subtree.
     *   - add the trees to trees[i][j]. 
     * Note: trees[i][i-1] is defined to be an empty list of trees,
     *       this way the algorithm above is well defined for k = i 
     *       and k = j.
     */


    vector<TreeNode*> generateTrees(int n) {
        vector<vector<vector<TreeNode*>>> dpTbl(n, vector<vector<TreeNode*>>(n));
        for(int diagIdx = 0; diagIdx < n; diagIdx++){
            for(int rowIdx = 0; rowIdx < n - diagIdx; rowIdx++){
                int colIdx = diagIdx + rowIdx;
                calcTrees(dpTbl, rowIdx, colIdx);
            }
        }
        return dpTbl[0][n - 1];
    }


private:
    void calcTrees(vector<vector<vector<TreeNode*>>>& dpTbl, int rowIdx, int colIdx){
        vector<TreeNode*>& trees = dpTbl[rowIdx][colIdx];
        
        for(int idx = rowIdx; idx <= colIdx; idx++){
                         
            vector<TreeNode*> emptyVec;
            vector<TreeNode*>& leftTrees = idx == rowIdx ? emptyVec : dpTbl[rowIdx][idx - 1];
            vector<TreeNode*>& rightTrees = idx == colIdx ? emptyVec : dpTbl[idx + 1][colIdx];

            //+1 since values start from 1 and not 0.
            int rootVal = idx + 1;
            if(leftTrees.size() == 0 && rightTrees.size() == 0){
                TreeNode* pTreeNode = new TreeNode(rootVal);
                trees.push_back(pTreeNode);
            }else if(leftTrees.size() == 0){
                //insert only right.
                for(TreeNode* pTree : rightTrees){
                    TreeNode* pRoot = new TreeNode(rootVal);
                    pRoot->right = pTree;
                    trees.push_back(pRoot);
                }
            }else if(rightTrees.size() == 0){
                // insert only left.
                for(TreeNode* pTree : leftTrees){                    
                    TreeNode* pRoot = new TreeNode(rootVal);
                    pRoot->left = pTree;
                    trees.push_back(pRoot);
                }
            }else{
                //for every tree to the left, insert all the trees to the right.
                for(TreeNode* pLeftTree: leftTrees){
                    for(TreeNode* pRightTree : rightTrees){
                        TreeNode* pRoot = new TreeNode(rootVal);
                        pRoot->right = pRightTree;
                        pRoot->left = pLeftTree;
                        trees.push_back(pRoot);
                    }
                }
            }
        }
    }
};
