/**
 * https://leetcode.com/problems/linked-list-cycle
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(!head || !head->next){
            return false;
        }

        ListNode* oneItr = head;
        ListNode* twoItr = head->next;
        while(oneItr != nullptr && twoItr != nullptr && oneItr != twoItr){
            //advance oneItr by 1 node.
            oneItr = oneItr->next;
            //asvance twoItr by 2 nodes.
            twoItr = twoItr->next ? twoItr->next->next : twoItr->next;
        }
        if(!oneItr || !twoItr){
            return false;
        }
        return true;
    }
};
