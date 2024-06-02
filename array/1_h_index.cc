/**
 * https://leetcode.com/problems/h-index
 * #sort #binary_search
 */
class Solution {
public:
    /**
     * Given citations is sorted.
     * If citations[i] = k.
     * The are citations.size() - i papers with at least k publications.
     * so, the h index is at least min(k, citations.size() - i).
     * If k < citations.size() - i:
     *     there is no need to check index j < i, since min(citations[j], citations.size() - j)
     *     is citations[j] which is smaller than citations[i] = k.
     *     But, it's possible that there is index m > i, such that:
     *     k < citations.size() - m < citations[k].
     * If k >= citations.size() - i:
     *     There is no need to check index m > i, since min(citations[m], citations.size() - m)
     *     is citations.size() - m < citations.size() - i.
     *     But, it's possible that there is index j < i such that:
     *     min(citations[j], citations.size() - j) = citations.size() - j > k > citations.size() - i 
     */
    int hIndex(vector<int>& citations) {
        ranges::sort(citations);
        int hIdx = 0;
        int citationsLen = citations.size();
        int leftIdx = 0;
        int rightIdx = citationsLen - 1;
        while(leftIdx <= rightIdx){
            int midIdx = (leftIdx + rightIdx) / 2;
            int citationsCount = citations[midIdx];
            int numOfPapers = citationsLen - midIdx;    
            hIdx = max(hIdx, min(citationsCount, numOfPapers));
            if(citationsCount < numOfPapers){
                leftIdx = midIdx + 1;
            }else{
                rightIdx = midIdx - 1;
            }
        }
        return hIdx;
    }
};
