/**
 * #binary_tree #mobileye
 * 
 * Description: you are given a binary tree node struct
 * with pointers to both descendents and a pointer to the
 * parent node. Print all the nodes' values (each value
 * must be printed only once) and do it in O(1) additional
 * memory.
 */
#include <iostream>

struct Node{
    Node* pParent;
    Node* pLeft;
    Node* pRight;
    int val;
};

class Solution{
public:
    void loopIteration(Node* root){
        Node* pCameFrom = nullptr;
        Node* pItr = root;
        
        while(pItr){
            if((!pCameFrom || pCameFrom == pItr->pParent) &&
                pItr->pLeft){
                ///Visit the left subtree.
                pCameFrom = pItr;
                pItr = pItr->pLeft;
            }else if((!pItr->pLeft || pItr->pLeft == pCameFrom) &&
                      pItr->pRight){
                ///Visit the right subtree.
                pCameFrom = pItr;
                pItr = pItr->pRight;
            }else{
                ///print yourself and go back to the parent.
                std::cout << pItr->val << "\n";
                pCameFrom = pItr;
                ///Note: in case pItr is the root, 
                ///      pItr->pParent == nullptr and the
                ///      loop ends.
                pItr = pItr->pParent;
            }
        }    
    }
};

