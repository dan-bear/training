/**
 * https://leetcode.com/problems/binary-tree-right-side-view
 * #binary_tree #BINARY_TREE #bfs #bt #BT
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
    vector<int> rightSideView(TreeNode* root){
        ///First one is faster that's why it's not commented out.
        return rightSideViewWithArrayDepthHisto(root);
        //return rightSideViewWithMapDepthHisto(root);

    }

private:
    vector<int> rightSideViewWithArrayDepthHisto(TreeNode* pRoot) {        
        if(!pRoot){
            return vector<int>();
        }
        
        int height = calcHeight(pRoot);
        int invalidVal = numeric_limits<int>::lowest();
        vector<int> resAndDepthHistogram(height + 1, invalidVal);
        queue<pair<TreeNode*, int>> nodesDepthQueue;
        nodesDepthQueue.push(pair<TreeNode*, int>(pRoot, 0));
        
        int depth;
        TreeNode* pNode;
        while(!nodesDepthQueue.empty()){
            pNode = nodesDepthQueue.front().first;
            depth = nodesDepthQueue.front().second;
            if(pNode->right){
                nodesDepthQueue.push(pair<TreeNode*, int>(pNode->right, depth + 1));
            }
            if(pNode->left){
                nodesDepthQueue.push(pair<TreeNode*, int>(pNode->left, depth + 1));
            }
            if(resAndDepthHistogram[depth] == invalidVal){
                resAndDepthHistogram[depth] = pNode->val;
            }
            nodesDepthQueue.pop();    
        }
        return resAndDepthHistogram;
    }

    vector<int> rightSideViewWithMapDepthHisto(TreeNode* pRoot) {
        vector<int> res;
        if(!pRoot){
            return res;
        }
        
        queue<pair<TreeNode*, int>> nodesDepthQueue;
        unordered_map<int, int> depthHash;

        nodesDepthQueue.push(pair<TreeNode*, int>(pRoot, 0));
        int depth;
        TreeNode* pNode;
        while(!nodesDepthQueue.empty()){
            pNode = nodesDepthQueue.front().first;
            depth = nodesDepthQueue.front().second;
            if(pNode->right){
                nodesDepthQueue.push(pair<TreeNode*, int>(pNode->right, depth + 1));
            }
            if(pNode->left){
                nodesDepthQueue.push(pair<TreeNode*, int>(pNode->left, depth + 1));
            }
            if(!depthHash.count(depth)){
                depthHash[depth] = 0;//just keep there something.
                res.push_back(pNode->val);
            }
            nodesDepthQueue.pop();    
        }
        
        return res;
    }

    int calcHeight(TreeNode* pRoot){
        if(!pRoot){
            return -1;
        }
        return 1 + max(calcHeight(pRoot->left), calcHeight(pRoot->right));
    }
 
    vector<int> getValsLayerByLayerFromRightToLeft(TreeNode* root){
        queue<TreeNode*> nodes;
        vector<int> res;
        if(root){
            nodes.push(root);
            TreeNode* pCurrNode = nullptr;
            while(!nodes.empty()){
                pCurrNode = nodes.front();
                if(pCurrNode->right){
                    nodes.push(pCurrNode->right);
                }
                if(pCurrNode->left){
                    nodes.push(pCurrNode->left);
                }
                res.push_back(pCurrNode->val);
                nodes.pop();    
            }
        }
        return res;
    }
};
