/**
 * Explain why and how the inorder works.
 * https://leetcode.com/problems/recover-binary-search-tree/
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
