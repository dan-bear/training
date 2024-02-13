/**
 * 
 * https://leetcode.com/problems/recover-binary-search-tree/
 *
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
 *
 * In order traversal: left, middle, right.
 * Example1:
 *            1
 *           2 3
 * In order traversal returns 2 1 3: 2 !<= 1, so 2 is not
 * in place. Since it's the only element that does not 
 * satisfy a[i] <= a[i + 1], the fix is to replace 1 and 2.
 * Example 2:
 *            3
 *          4   2    
 *        1       5
 * In order traversal returns 1, 4, 3, 2, 5
 * note that 4 !<= 3 and 3 !<= 2, in this example replacing
 * 4 and 2 fix the problem. So the intuition is to take
 * find the first a[i] that does not satisfy a[i] < a[i + 1]
 * and the last a[j] that satisfy a[j - 1] !<= a[j] and 
 * replace them.
 * 
 */
class Solution {
public:
    void recoverTree(TreeNode* root) {
        
        int firstVal;
        int secondVal;
        int prevVal;
        bool firstValFound = false;
        bool pPrevValSet = false;
        traverseToFindFirstAndLastNotInOrder(root,
                                             &prevVal,
                                             &firstVal,
                                             &secondVal,
                                             &firstValFound,
                                             &pPrevValSet);
        
        TreeNode* pFirstNodeToReplace = nullptr;
        TreeNode* pSecondNodeToReplace = nullptr;
        findTwoVals(root, 
                   &pFirstNodeToReplace,
                   &pSecondNodeToReplace, 
                   firstVal, 
                   secondVal);

        pFirstNodeToReplace->val = secondVal;
        pSecondNodeToReplace->val = firstVal;
    }

private:
    void traverseToFindFirstAndLastNotInOrder(TreeNode* pNode,
                                              int* pPrevVal,
                                              int* pFirstVal,
                                              int* pSecondVal,
                                              bool* pFirstValFound,
                                              bool* pPrevValSet){
        if(pNode == nullptr){
            return;
        }
        traverseToFindFirstAndLastNotInOrder(pNode->left,
            pPrevVal, pFirstVal, pSecondVal, pFirstValFound, pPrevValSet);
        
        if(!*pPrevValSet){
            *pPrevVal = pNode->val;
            *pPrevValSet = true;
        }else{
            int currentVal = pNode->val;
            if(currentVal < *pPrevVal){
                if(!*pFirstValFound){
                    *pFirstVal = *pPrevVal;
                }
                *pSecondVal = currentVal;
            }
        }

        traverseToFindFirstAndLastNotInOrder(pNode->right,
            pPrevVal, pFirstVal, pSecondVal, pFirstValFound, pPrevValSet);
    }

    void findTwoVals(TreeNode* pNode,
                     TreeNode** pPFirstNodeToReplaceOut,
                     TreeNode** pPSecondNodeToReplaceOut,
                     int firstVal, 
                     int secondVal){

        if((*pPFirstNodeToReplaceOut != nullptr && 
           *pPSecondNodeToReplaceOut != nullptr) || pNode == nullptr){
            return;
        }

        findTwoVals(pNode->left, 
                    pPFirstNodeToReplaceOut, 
                    pPSecondNodeToReplaceOut, 
                    firstVal, 
                    secondVal);

        if(pNode->val == firstVal){
            *pPFirstNodeToReplaceOut = pNode;
        }else if(pNode->val == secondVal){
            *pPSecondNodeToReplaceOut = pNode;
        }

        findTwoVals(pNode->right, 
                    pPFirstNodeToReplaceOut, 
                    pPSecondNodeToReplaceOut, 
                    firstVal, 
                    secondVal);
    }

};
