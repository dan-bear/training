/**
 * https://leetcode.com/problems/successful-pairs-of-spells-and-potions
 * #binary serach
 */
class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        ranges::sort(potions);
        vector<int> pairs(spells.size(), 0);
        for(int spellIdx = 0; spellIdx < spells.size(); spellIdx++){
            pairs[spellIdx] = 
            countSuccessfulPairs(spells, potions, success, spellIdx);
        }
        return pairs;
    }

private:
    int countSuccessfulPairs(const vector<int>& spells,
                             const vector<int>& sortedPotions,
                             long long success,
                             int spellIdx){
        long long reminder = success % spells[spellIdx];
        long long floorDiv = success / spells[spellIdx];
        long long minPotionVal = reminder > 0 ? floorDiv + 1 : floorDiv;
        
        int supremumIdx = findSupremumIdx(sortedPotions, minPotionVal);
        int res = supremumIdx >= 0 ? sortedPotions.size() - supremumIdx : 0;
        return res;
    }

    int findSupremumIdx(const vector<int>& sortedVec, long long val){
        int leftIdx = 0;
        int rightIdx = sortedVec.size() - 1;
        int midIdx = 0;
        long long midVal = 0;
        while(leftIdx <= rightIdx){
            ///if val is found, I got the index and all is well.
            ///if leftIdx > rightIdx (stopped) it means that val was
            ///not found, but the leftIdx is the index where val
            ///would have been placed in case it was added to the
            ///array.
            ///Example: sortedVec = [1, 3]
            ///target = 0 => rightIdx = -1, leftIdx = 0. [0, 1, 3]
            ///target = 2 => rightIdx = 0, leftIdx = 1.  [1, 2, 3]
            ///target = 4 => rightIdx = 1, leftIdx = 2.  [1, 3, 4]
            
            midIdx = (leftIdx + rightIdx) / 2;
            midVal = sortedVec[midIdx];
            if(midVal == val && (midIdx == 0 || sortedVec[midIdx - 1] != val)){
                break;
            }else if(midVal < val){
                leftIdx = midIdx + 1;
            }else{ // midVal > val || midVal == val but also vec[midIdx - 1] == val
                rightIdx = midIdx - 1;
            }
        }
        int res = midVal == val ? midIdx : leftIdx;
        return res;
    }
};
