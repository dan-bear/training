/**
 * https://leetcode.com/problems/unique-number-of-occurrences
 * #hash #sort
 */
class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int, int> histo = fillHisto(arr);
        vector<int> numOfOccurrences = fillOccurrences(histo);
        sort(numOfOccurrences.begin(), numOfOccurrences.end());
        bool res = true;
        for(int idx = 1; idx < numOfOccurrences.size() && res; idx++){
            res = (numOfOccurrences[idx] != numOfOccurrences[idx - 1]);
        }
        return res;
    }

private:
    unordered_map<int, int> fillHisto(const vector<int>& arr){
        unordered_map<int, int> histo;
        for(int elem: arr){
            if(histo.count(elem) == 0){
                histo[elem] = 1;
            }else{
                histo[elem] += 1;
            }
        }
        return histo;
    }

    vector<int> fillOccurrences(const unordered_map<int, int>& histo){
        vector<int> occurrencesArr(histo.size(), 0);
        int occurrencesArrIdx = 0;
        for(const pair<int, int>& keyVal : histo){
            occurrencesArr[occurrencesArrIdx] = keyVal.second;
            occurrencesArrIdx++;
        }
        ///Note, a more modern way:
        // for(auto& [key, value] : histo){
        //     occurrencesArr[occurrencesArrIdx] = keyVal.second;
        //     occurrencesArrIdx++;
        // }
        return occurrencesArr;
    }
};
