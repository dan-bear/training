/**
 * https://leetcode.com/problems/remove-nth-node-from-end-of-list
 *
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        vector<ListNode*> vNodesAddresses(n + 1, nullptr);
        ListNode* pNodeItr = head;
        int nodeIdx = 0;
        while(pNodeItr != nullptr){
            vNodesAddresses[nodeIdx % (n + 1)] = pNodeItr;
            nodeIdx += 1;
            pNodeItr = pNodeItr->next;
        }
              
        int nodeToRemoveIdx = (nodeIdx - n) % (n + 1);
        int prevNodeIdx = nodeToRemoveIdx == 0 ? n : (nodeIdx - n - 1) % (n + 1);
        ListNode* pNodeToRemove = vNodesAddresses[nodeToRemoveIdx];
        ListNode* pPrevNode = vNodesAddresses[prevNodeIdx];
        ListNode* pNextNode = pNodeToRemove->next;
        
        ListNode* pHeadRes = nullptr;
        if(pPrevNode == nullptr){
            //The node to remove is the first one.
            pHeadRes = pNextNode;
        }else{
            pPrevNode->next = pNextNode;
            pHeadRes = head;
        }
        return pHeadRes;
    }
};
