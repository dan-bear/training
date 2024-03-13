/**
 * https://leetcode.com/problems/odd-even-linked-list
 * #list #LIST #linked_list #LINKED_LIST #two_ptrs
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
    ListNode* oddEvenList(ListNode* head) {
        ListNode* pOddListHead = head;
        ListNode* pOddListTail = pOddListHead;
        ListNode* pEvenListHead = head && head->next ? head->next : nullptr;
        ListNode* pEvenListTail = pEvenListHead;
            
        ListNode* pItr = pEvenListTail && pEvenListTail->next ? pEvenListTail->next : nullptr;
        bool oddTurn = true;
        while(pItr){
            if(oddTurn){
                pOddListTail->next = pItr;
                pOddListTail = pItr;
            }else{
                pEvenListTail->next = pItr;
                pEvenListTail = pItr;
            }
            pItr = pItr->next;
            oddTurn = !oddTurn;
        }
        
        if(pOddListTail){
            pOddListTail->next = pEvenListHead;
        }
        if(pEvenListTail){
            pEvenListTail->next = nullptr;
        }
        return pOddListHead;
    }
};
