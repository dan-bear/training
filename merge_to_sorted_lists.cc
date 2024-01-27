/**
 * https://leetcode.com/problems/merge-two-sorted-lists/
 * Tag: linked list.
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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        
        ListNode* pResHead = nullptr;
        ListNode* pResTail = nullptr;
        ListNode* pItr1 = list1;
        ListNode* pItr2 = list2;
        
        //single if to avoid unnecessary iffs in the while loop5
        if(pItr1 || pItr2){
            int val1 = pItr1 ? pItr1->val : skAboveMaxVal;
            int val2 = pItr2 ? pItr2->val : skAboveMaxVal;
            if(val1 <= val2){
                pResHead = pItr1;
                pItr1 = pItr1->next;
            }else{
                pResHead = pItr2;
                pItr2 = pItr2->next;
            }
            
            pResTail = pResHead;
        }

        while(pItr1 || pItr2){
            int val1 = pItr1 ? pItr1->val : skAboveMaxVal;
            int val2 = pItr2 ? pItr2->val : skAboveMaxVal;
            if(val1 <= val2){
                pResTail->next = pItr1;
                pResTail = pItr1;
                pItr1 = pItr1 ? pItr1->next : pItr1;
            }else{
                pResTail->next = pItr2;
                pResTail = pItr2;
                pItr2 = pItr2 ? pItr2->next : pItr2;
            }
        }

        return pResHead;
    }
private:
    static const int skAboveMaxVal{200};

};
