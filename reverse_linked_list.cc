/**
 * https://leetcode.com/problems/reverse-linked-list
 * #list #LIST #linked_list #LINKED_LIST 
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
    ListNode* reverseList(ListNode* head) {
        ListNode* pRevHead = nullptr;
        ListNode* pItr = head;
        while(pItr){
            ListNode* currNode = pItr;
            pItr = pItr->next;
            currNode->next = pRevHead;
            pRevHead = currNode;
        }
        return pRevHead;
    }
};
