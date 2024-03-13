/**
 * https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list
 * #List #list #LINKED_LIST #liked_list
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
    int pairSum(ListNode* head){
        /// O(list_len) time and O(list_len) space
        ///return pairSumWithVector(head);
        /// O(list_len) time and O(1) space.
        return pairSumWithReversing(head);
    }

private:
    int pairSumWithReversing(ListNode* pHead){
        int len = calcLen(pHead);
        ListNode* pMiddle = nullptr;
        ListNode* pPrevToMiddle = nullptr;
        getMiddleAndItsPrev(pHead, len, &pMiddle, &pPrevToMiddle);
        pMiddle = reverseList(pMiddle);
        pPrevToMiddle->next = pMiddle;
        int maxPairSum = calcMaxPairSumFromTwoLists(pHead, pMiddle, len / 2);
        return maxPairSum;
    }

    int calcLen(ListNode* pHead){
        int len = 0;
        while(pHead){
            len++;
            pHead = pHead->next;
        }
        return len;
    }


    void getMiddleAndItsPrev(ListNode* pHead,
                             int len,
                             ListNode** ppMiddle, 
                             ListNode** ppPrevToMiddle){
        int idx = 0;
        while(idx < (len / 2) - 1){
            pHead = pHead->next;
            idx++;
        }
        *ppPrevToMiddle = pHead;
        *ppMiddle = pHead->next;
    }

    ListNode* reverseList(ListNode* pHead){
        ListNode* pRevHead = nullptr;
        ListNode* pItr = pHead;
        ListNode* pCurrNode = nullptr;
        while(pItr){
            pCurrNode = pItr;
            pItr = pItr->next;
            pCurrNode->next = pRevHead;
            pRevHead = pCurrNode;
        }
        return pRevHead;
    }

    int calcMaxPairSumFromTwoLists(ListNode* pHead1, ListNode* pHead2, int len){
        int maxPairSum = 0;
        for(int pairIdx = 0; pairIdx < len; pairIdx++){
            maxPairSum = max(maxPairSum, pHead1->val + pHead2->val);
            pHead1 = pHead1->next;
            pHead2 = pHead2->next;
        }
        return maxPairSum;
    }


    //_________________________________________________________________________

    int pairSumWithVector(ListNode* pHead) {
        vector<int> vals = fillVals(pHead);
        int maxPairSum = calcMaxPairSum(vals);
        return maxPairSum;
    }
    
    vector<int> fillVals(ListNode* pHead){
        vector<int> vals;
        ListNode* pItr = pHead;
        while(pItr){
            vals.push_back(pItr->val);
            pItr = pItr->next;
        }
        return vals;
    }

    int calcMaxPairSum(const vector<int>& vals){
        int maxPairSum = 0;
        int leftIdx = 0;
        int rightIdx = vals.size() - 1;
        while(leftIdx < rightIdx){
            maxPairSum = max(maxPairSum, vals[leftIdx] + vals[rightIdx]);
            leftIdx++;
            rightIdx--;
        }
        return maxPairSum;
    }
};
