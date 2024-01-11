/**
 * https://leetcode.com/problems/partition-list
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
    ListNode* partition(ListNode* head, int x) {
        
        ListNode* predecessor = nullptr;
        ListNode* predecessorsHead = nullptr;
        ListNode* successor = nullptr;
        ListNode* successorsHead = nullptr;
        
        ListNode* itr = head;
        while(itr){
            if(itr->val < x){
                if(predecessor == nullptr){
                    predecessorsHead = itr;
                }else{
                    predecessor->next = itr;
                }
                predecessor = itr;
            }else{
                if(successor == nullptr){
                    successorsHead = itr;
                }else{
                    successor->next = itr;
                }
                successor = itr;
            }
            itr = itr->next;
        }

        if(successor != nullptr){
            successor->next = nullptr;
        }
        
        if(predecessor != nullptr){
            predecessor->next = successorsHead;
        }else{
            predecessorsHead = successorsHead;
        }

        return predecessorsHead;
    }
};
