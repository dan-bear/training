/**
 * https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list
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
    ListNode* deleteMiddle(ListNode* head){
        ///return deleteMiddleWithLenCalc(head);
        return deleteMiddleWithTwoSpeedsIters(head);
    }

    ListNode* deleteMiddleWithTwoSpeedsIters(ListNode* head){
        ListNode* res = nullptr;
        if(head->next){
            res = head;
            ListNode* pSpeedyItr = head;
            ListNode* pSlowItr = head;
            ListNode* pPrevToSlowItr = nullptr;
            
            while(pSpeedyItr && pSpeedyItr->next){
                pSpeedyItr = pSpeedyItr->next->next;
                pPrevToSlowItr = pSlowItr;
                pSlowItr = pSlowItr->next;    
            }

            pPrevToSlowItr->next = pSlowItr->next;
        }///else: nothing to do, res is already set to nullptr. 
        return res;
    }

    ListNode* deleteMiddleWithLenCalc(ListNode* head) {
        int listLen = calcLen(head);
        int targetIdx = listLen / 2;
        ListNode* prevNode = nullptr;
        ListNode* currNode = head;
        moveToMiddleNode(&prevNode, &currNode, targetIdx);
        ListNode* res = deleteMiddleNode(head, prevNode, currNode);
        return res;
    }

private:
    void moveToMiddleNode(ListNode** ppPrevNode, ListNode** ppCurrNode, int targetIdx){
        int currIdx = 0;
        while(currIdx < targetIdx){
            *ppPrevNode = *ppCurrNode;
            *ppCurrNode = (*ppCurrNode)->next;
            currIdx++;
        }
    }

    ListNode* deleteMiddleNode(ListNode* head, 
                               ListNode* prevNode,
                               ListNode* currNode){
        ListNode* res = nullptr;
        ///it's possible that prev = nullptr,
        ///in case the list is of size 1.
        if(prevNode != nullptr){
            prevNode->next = currNode->next;
            res = head;
        }///nothing to do otherwise, the res
         ///is already set to nullptr.
        return res;
    }

    int calcLen(ListNode* head){
        int len = 0;
        while(head){
            head = head->next;
            len++;
        }
        return len;
    }
};
