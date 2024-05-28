/**
 * #bst #BST
 * #pinecone #pinecone db 
 *
 * Passing a BST over network:
 * Implement the method 
 * void passBstThroughNetwork(TreeNode* pRoot, NetworkIntf* pNet)
 * (see TreeNode and NetworkIntf below). 
 * The method gets a bst and passes its values through the
 * network such that when the destination (target) gets the
 * values and apply the bst-insert algorithm (see below),
 * the generated bst in the destination (target) has the
 * same topology (structure) as the bst given as a parameter
 * (the bst in the source).
 *
 * BST insert algorithm:
 *     1: input: val
 *     2: if the tree is empty, create a root and store the
 *        val in the root.
 *     3: if there is a root:
 *         3.1: compare val with root->val
 *         3.2: if val < root->val:
 *             3.2.1: if root->left: restart step 3 with
 *                    root = root->left.
 *             3.2.3: else: allocate a node, store val in it
 *                    and set root->left = allocated node.
 *         3.3: if val > root->val:
 *             3.3.1: if root->right: restart step 3 with
 *                    root = root->right
 *             3.3.2: else: allocate a node, store val in it
 *                    and set root->right = allocated node.
 * 
 * 
 * The TreeNode and NetworkIntf:
 */
struct TreeNode{
    TreeNode* m_pLeft;
    TreeNode* m_pRight;
    int m_val;
};

class NetworkIntf{
public:
    void send(int val) {/** Does something*/};
private:
    /** More non-interesting somethings*/
};

/**
 * SOLUTION
 * 
 * Given a BST
 *      2
 *    1   3
 * in-order (left, middle, right) traversal => {1, 2, 3}
 * pre-order (middle, left, right) traversal => {2, 1, 3}
 * post-order traversal (left, right, middle) => {1, 3, 2}
 *
 * Apply the BST insert algorithm by iterating the results
 * (i.e. insert(traverse[i]) for i in range(traverse.size()))
 * in-order => insert(1), insert(2), insert(3) =>
 *      1
 *        2
 *          3
 * post-order => insert(1), insert(3), insert(2) =>
 *      1
 *        3
 *      2
 * pre-order => insert(2), insert(1), insert(3) =>
 *      2
 *    1   3
 * 
 * All right, the pre-order traversal is the only candidate
 * to be a solution for the problem. It's left to proof (or
 * at least explain) why it's a solution.
 * 
 * Given a BST, the pre-order traverse is:
 * root, left subtree pre-order-trav, right subtree pre-order trav
 * 
 * 1: inserting the root as the first element using the BST
 *    insert algorithm promises that the generated tree has
 *    the same root as the original tree (induction base).
 * 2: All the elements in the left-subtree pre-order-trav 
 *    are smaller than the root's value so they will be 
 *    inserted to the left part of the generated BST. 
 *    Symmetric claim stands for the right-subtree
 *    pre-order-traverse. So, the left-subtree values in the
 *    original tree will be in the left-subtree of the
 *    generated subtree and same for the right-subtree
 *    values (induction step).
 * 3: Now, claim 1 stands for the left-subtree-preorder 
 *    traverse when focusing on the generated tree root's
 *    left subtree and also for the right-subtree-preorder
 *    traverse when focusing on the generated tree root's
 *    right subtree (induction generalization). 
 *  
 */
class Solution{
public:
    void passBstThroughNetwork(TreeNode* bstRoot,
                               NetworkIntf* pNet){
        if(bstRoot != nullptr){
            pNet->send(bstRoot->m_val);
            passBstThroughNetwork(bstRoot->m_pLeft, pNet);
            passBstThroughNetwork(bstRoot->m_pRight, pNet);
        }
    }
    
private:
    /// Note: since this method is recursive, performance 
    ///       wise it's better to avoid passing the pNet
    ///       as a parameter (it saves stack memory), so
    ///       the public method can set the m_pNet member
    ///       to the given pNet parameter and than an
    ///       internal recursive function that access the
    ///       member can be used:
    NetworkIntf* m_pNet{ nullptr };
    void passBstThroughNetworkAux(TreeNode* bstRoot){
        if(bstRoot != nullptr){
            m_pNet->send(bstRoot->m_val);
            passBstThroughNetworkAux(bstRoot->m_pLeft);
            passBstThroughNetworkAux(bstRoot->m_pRight);
        }
    }
};
