/**
 * Explain why and how the inorder works.
 * https://leetcode.com/problems/recover-binary-search-tree/
 * 
 * The idea of this algorithm goes as follows:
 * let's assume that node[i] and node[j] are not in
 * place and node[i].val < node[j].val. 
 * It means that:
 * 1: The subtree of node[i] is a valid BST.
 * 2: The subtree of node[j] is a valid BST.
 * 3: The subtree excepted from cutting node[i]'s and node[j]'s
 *    subtree is also a valid BST.
 * So, a sequenec of an inorder traverseal output can be separated
 * to (at most) 3 monotinically increasing runs, when the values
 * of node[i] and node[j] will be the separating elements between
 * the monotonically increasing runs.
 * For example, the tree:
 *          8   
 *     4           6 
 *  2    12     10      14
 * 1 3  5  7   9  11  13  15
 *  
 * switchig 12 and 6 fixes the tree, an inorder traversal leads to:
 * 1 2 3 4 5 12 7 8 6 9 10 11 13 14 15
 * 1 < 2 < 3 < 4 < 5 < 12 is the first runn.
 * 7 < 8 is the second run.
 * 6 < 9 < 10 < 11 < 13 < 14 < 15 is the third run.
 * The first element that is not in place is the first one to
 * not satisfy in_order_arr[i] < in_order_arr[i+1] (last element
 * of the first run).
 * The second element that is not in place it the one satisfying:
 * in_order_array[i-1] > in_order_array[i] (the first element of
 * the third run).
 */

class Solution {
public:
    void recoverTree(TreeNode* root) {
        vector<int> pInOrderTraverse;
        fillInOrder(root, pInOrderTraverse);
        int firstVal = 0;
        int secondVal = 0;
        findValsToFix(pInOrderTraverse, firstVal, secondVal);
        int foundCount = 0;
        fixVals(root, firstVal, secondVal, foundCount);
    }

private:
    void fixVals(TreeNode* pNode, int firstVal, int secondVal, int& pFoundCount){
        if(pNode == nullptr || pFoundCount == 2){
            return;
        }
        fixVals(pNode->left, firstVal, secondVal, pFoundCount);

        if(pNode->val == firstVal){
            pNode->val = secondVal;
            pFoundCount += 1;
        }else if(pNode->val == secondVal){
            pNode->val = firstVal;
            pFoundCount += 1;
        }

        fixVals(pNode->right, firstVal, secondVal, pFoundCount);
        

    }


    void findValsToFix(const vector<int>& inOrderTraverse, int& firstVal, int& secondVal){
        bool bFirstFound = false;
        for(int idx = 1; idx < inOrderTraverse.size(); idx++){
            if(inOrderTraverse[idx] < inOrderTraverse[idx - 1]){
                if(bFirstFound == false){
                    firstVal = inOrderTraverse[idx - 1];
                    bFirstFound = true;
                }
                secondVal = inOrderTraverse[idx];
            }
        }
    }

    void fillInOrder(TreeNode* pNode, vector<int>& pInOrderTraverse){
        if(pNode == nullptr){
            return;
        }
        fillInOrder(pNode->left, pInOrderTraverse);
        pInOrderTraverse.push_back(pNode->val);
        fillInOrder(pNode->right, pInOrderTraverse);
    }
};
