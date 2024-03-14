/**
 * https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree
 * #bt #BT #binary_tree #BINARY_TREE #recursion
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
    int longestZigZag(TreeNode* root) {
        //return tooSlowLongestZigZag(root);
        //return slowLongestZigZag(root);
        return fastLongestZigZag(root);
    }
    
private:
    enum class Turn : uint32_t{
        kLeft,
        kRight
    };
    
    int fastLongestZigZag(TreeNode* root) {
        traverse(root->left, Turn::kRight, 0);
        traverse(root->right, Turn::kLeft, 0);
        return m_longestPath;
    }

    void traverse(TreeNode* pNode, Turn dirToTake, int count){
        if(!pNode){
            m_longestPath = max(m_longestPath, count);
        }else{
            if(dirToTake == Turn::kLeft){
                traverse(pNode->left, Turn::kRight, count += 1);
                traverse(pNode->right, Turn::kLeft, 0);
            }else{
                traverse(pNode->right, Turn::kLeft, count += 1);
                traverse(pNode->left, Turn::kRight, 0);
            }
        }
    }
    
    
    //_________________________________________________________________________
    ///correct but still slow solution:
    int slowLongestZigZag(TreeNode* root) {
        int longestLeftZigzag = 0;
        int longestRightZigzag = 0;
        traverseZigzag(root, longestLeftZigzag, longestRightZigzag);
        return m_longestPath;
    }

    void traverseZigzag(TreeNode* pNode, int& longestLeftZigzag, int& longestRightZigzag){
        if(!pNode){
            longestLeftZigzag = -1;
            longestRightZigzag = -1;
        }else{
            int currLongestLeftZigzag = 0;
            int currLongestRightZigzag = 0;
            traverseZigzag(pNode->left,
                           currLongestLeftZigzag,
                           currLongestRightZigzag);
            longestLeftZigzag = 1 + currLongestRightZigzag;
            traverseZigzag(pNode->right, 
                           currLongestLeftZigzag, 
                           currLongestRightZigzag);
            longestRightZigzag = 1 + currLongestLeftZigzag;
            m_longestPath = max(m_longestPath,
                                max(longestLeftZigzag, longestRightZigzag));
        }
    }

    //_________________________________________________________________________
    ///correct but too slow slution (time limit exceeded in 56/58 test)
    int tooSlowLongestZigZag(TreeNode* root) {
        if(root){
            bool turnLeft = true;
            int currentLongest = max(longestTraverse(root, turnLeft), longestTraverse(root, !turnLeft));
            m_longestPath = max(m_longestPath, currentLongest);
            longestZigZag(root->left);
            longestZigZag(root->right); 
        }
        return m_longestPath;
    }


    int m_longestPath{0};
    
    int longestTraverse(TreeNode* pNode, bool turnLeft){
        if(!pNode){
            return -1;
        }
        if(turnLeft){
            return 1 + longestTraverse(pNode->left, !turnLeft);   
        }else{
            return 1 + longestTraverse(pNode->right, !turnLeft);
        }
    }
};
