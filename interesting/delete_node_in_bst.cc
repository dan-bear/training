/**
 * https://leetcode.com/problems/delete-node-in-a-bst
 * #bst #recursive #iterative #binary_tree
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
    TreeNode* deleteNode(TreeNode* root, int key) {
        ///return iterativeDeleteNode(root, key);
        return recursiveDeleteNode(root, key);
    }

private:
    TreeNode* recursiveDeleteNode(TreeNode* pRoot, int key){
        if(pRoot){
            if(pRoot->val > key){
                ///gonna delete a node in the left subtree.
                ///so left subtree is about to be updated.
                pRoot->left = recursiveDeleteNode(pRoot->left, key);
            }else if(pRoot->val < key){
                ///gonna delete a node in the right subtree.
                pRoot->right = recursiveDeleteNode(pRoot->right, key);
            }else{
                if(pRoot->right){
                    TreeNode* pSmallestInRightSubtree = getLeftMostLeaf(pRoot->right);
                    pSmallestInRightSubtree->left = pRoot->left;
                    pRoot = pRoot->right;
                }else{
                    pRoot = pRoot->left;
                }
            }
        }

        return pRoot;
    }



    TreeNode* iterativeDeleteNode(TreeNode* root, int key) {
        if(root){
            TreeNode* pPrevNode = nullptr;
            TreeNode* pCurrNode = root;
            traverseToNode(&pCurrNode, &pPrevNode, key);
            
            if(pCurrNode){
                if(!pPrevNode){
                    removeRoot(&root);
                }else{
                    removeNode(pCurrNode, pPrevNode);
                }
            }    
        }
        
        return root;    
    }




    void traverseToNode(TreeNode** ppCurrNode, TreeNode** ppPrevNode, int key){
        while(*ppCurrNode && (*ppCurrNode)->val != key){
                *ppPrevNode = *ppCurrNode;
                *ppCurrNode = (*ppCurrNode)->val > key ?
                              (*ppCurrNode)->left :
                              (*ppCurrNode)->right; 
        }
    }

    void removeRoot(TreeNode** ppRoot){
        TreeNode* pLeft = (*ppRoot)->left;
        TreeNode* pRight = (*ppRoot)->right;
        if(pRight){
            TreeNode* pLeftMostLeafInRightSubtree = getLeftMostLeaf(pRight);
            pLeftMostLeafInRightSubtree->left = pLeft;
            *ppRoot = pRight;
        }else{
            *ppRoot = pLeft;
        }
    }


    void removeNode(TreeNode* pNode, TreeNode* pParent){
        TreeNode* pLeft = pNode->left;
        TreeNode* pRight = pNode->right;
        if(pRight){
            TreeNode* pLeftMostLeafInRightSubtree = getLeftMostLeaf(pRight);
            pLeftMostLeafInRightSubtree->left = pLeft;
            switchPointers(pNode, pParent, pRight);
        }else{
            switchPointers(pNode, pParent, pLeft);
        }
    }

    TreeNode* getLeftMostLeaf(TreeNode* pRoot){
        while(pRoot->left){
            pRoot = pRoot->left;
        }
        return pRoot;
    }

    void switchPointers(TreeNode* pNode, TreeNode* pParent, TreeNode* pReplacement){
        if(pParent->left == pNode){
            pParent->left = pReplacement;
        }else{
            pParent->right = pReplacement;
        }
    }
};
