/**
 * https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree
 *
 * #bt #BT #binary_tree #recursion
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //return notConciseLCA(root, p, q);
        return findPorQ(root, p, q);
    }

private:
    TreeNode* findPorQ(TreeNode* root, TreeNode* p, TreeNode* q){
        if(!root || root == p || root == q){
            return root;
        }
        ///search for first occurence of p or q in the left subtree.
        TreeNode* pLeft = findPorQ(root->left, p, q);
        ///search for first occurence of p or q in the left subtree.
        TreeNode* pRight = findPorQ(root->right, p, q);
        
        if(!pLeft){
            ///It means that both p and q are in the right subtree.
            ///or that p and q are not in the left and not in the
            ///right subtree.
            ///so the LCA is in the right subtree or above the
            ///current root, so nullptr should be returned.
            return pRight;
        }
        if(!pRight){
            ///It means that both p and q are in the left subtree
            ///so the LCA is in the left subtree.
            return pLeft;
        }
        ///p and q are in separate subtrees, so current root is the LCA.
        return root;
    }
        
    ///Note: this is also a fast solution, and I even find it more self explainatory.
    TreeNode* notConciseLCA(TreeNode* root, TreeNode* p, TreeNode* q){
        m_p = p;
        m_q = q;
        traverse(root);
        return m_pLCA;
    }
    
    TreeNode* m_p{nullptr};
    TreeNode* m_q{nullptr};
    bool m_pFound = false;
    bool m_qFound = false;
    TreeNode* m_pLCA{nullptr};
    
    void traverse(TreeNode* pNode){
        if(pNode && (!m_pFound || !m_qFound)){
            bool bothNotFound = !m_pFound && !m_qFound;
            if(pNode == m_p){
                m_pFound = true;
            }
            if(pNode == m_q){
                m_qFound = true;
            }
            traverse(pNode->left);
            traverse(pNode->right);
            if(!m_pLCA && bothNotFound && m_pFound && m_qFound){
                ///cool, the first node both p and q were found
                ///is here.
                m_pLCA = pNode;
            }
        }
    }
};
