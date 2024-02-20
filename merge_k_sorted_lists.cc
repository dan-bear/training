/**
 * https://leetcode.com/problems/merge-k-sorted-lists/
 * #linked-list #list #linked #linked list
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* pResHead = iterateListsFront(lists);
        ListNode* pResTail = pResHead;
        ListNode* pCurrNode = nullptr;
        while(pResTail != nullptr){
            pCurrNode = iterateListsFront(lists);
            pResTail->next = pCurrNode;
            pResTail = pCurrNode;
        }
        return pResHead;
    }
private:
    ListNode* iterateListsFront(vector<ListNode*>& lists){
        //Since nullptrs are possible, the flag is used
        //as one cannot set minVal to lists[0]->val;
        bool bFirstValFound = false;
        int minVal = 0;
        int minValListIdx = 0;
        ListNode* pMinNodeInFront = nullptr;

        ListNode* pCurrentListHead = nullptr;
        for(int listIdx = 0; listIdx < lists.size(); listIdx++){
            pCurrentListHead = lists[listIdx];
            if(pCurrentListHead){
                //cool it's not nullptr.
                if(bFirstValFound == false || minVal > pCurrentListHead->val){
                    minVal = pCurrentListHead->val;
                    pMinNodeInFront = pCurrentListHead;
                    minValListIdx = listIdx;
                    bFirstValFound = true;
                }
            }
        }

        if(pMinNodeInFront){
            //not exhausted yet, update the lists!
            lists[minValListIdx] = pMinNodeInFront->next;
        }

        return pMinNodeInFront;
           
    }
};
