/**
 * https://leetcode.com/problems/majority-element
 * #hash #array #sort #random #algorithm
 */
#include <random>
class Solution {
public:
    /**
     * Option1: sort the nums, then start iteration with occurences 
     *          counter till you reach an element whose count is greater
     *          then lower(n / 2) => O(n*log(n)) time and space
     * Option2: use a hash table as an histogram => amortized O(n) time 
     *          and space
     * Option3: Using random algorithm:
     *          choose number of samples which is indepedent on nums.size().
     *          randomly choose indexes and save the values in a separate
     *          array and run option1 algorithm over that array.
     *          Since the sample size is indepndent of nums.size(), the
     *          time and space is O(sampleSize) = O(1).
     * Option4: Moore's voting algorithm
     *          Think about each element as a vote to a candidate.
     *          The fact that one of the candidates recieved more
     *          than floor(n/2) votes allows to figure out the 
     *          winner without knowing the exact number of votes.
     *          Start with a candidate as votes[0] and number of
     *          votes is 1.
     *          for any each vote:
     *              if the candidate's vote counter is 0:
     *                  select the candidate to be the current vote.
     *                  set the vote counter to 1.
     *              else:
     *                  if the vote goes for the current candidte:
     *                      increase the vote counter by 1. 
     *                  else: 
     *                      decrease the vote counter by 1.
     *           
     *          
     */
    int majorityElement(vector<int>& nums) {
        return mooreVotingApproach(nums); /*17ms*/
        ///return sortAndCountApproach(nums); /*17ms*/
        ///return hashApproach(nums);
        ///The random approach is very sensitive for
        ///test cases where nums.size() ~ sampleSize
        ///and there are only two values which have
        ///almost the same number of ocurrences.
        ///return randomApproach(nums); 
    }
private:
    int hashApproach(const vector<int>& nums){
        int res = nums[0];
        int countTarget = nums.size() / 2;
        unordered_map<int, int> valsHisto;
        for(int num : nums){
            if(valsHisto.find(num) == valsHisto.end()){
                valsHisto[num] = 1;
            }else{
                valsHisto[num]++;
                if(valsHisto[num] > countTarget){
                    res = num;
                    break;
                }
            }
        }
        return res;
    }


    int sortAndCountApproach(vector<int>& nums){
        ranges::sort(nums);
        int currVal = nums[0];
        int currCount = 1;
        int maxCount = 1;
        int maxCountVal = currVal;
        for(int idx = 1; idx < nums.size(); idx++){
            if(nums[idx] == currVal){
                currCount++;
            }else{
                if(currCount > maxCount){
                    maxCount = currCount;
                    maxCountVal = currVal;
                }
                currCount = 1;
                currVal = nums[idx];
            }
        }
        /// One more time since the last value
        /// might not be counted
        maxCountVal = currCount > maxCount ? currVal : maxCountVal;
        return maxCountVal;
    }

    int mooreVotingApproach(const vector<int>& votes){
        // int votesCount = 0;
        // int candidate = 0;
        // for(int vote : votes){
        //     if(votesCount == 0){
        //         candidate = vote;
        //         votesCount = 1;
        //     }else{
        //         votesCount += (vote == candidate ? 1 : -1);
        //     }
        // }
        // return candidate;

        ///It's pretty amazing that the iterator based for loop 
        ///is much slower than working with idx based loop.
        int votesCount = 0;
        int candidate = 0;
        for(int voteIdx = 0 ; voteIdx < votes.size(); voteIdx++){
            if(votesCount == 0){
                candidate = votes[voteIdx];
                votesCount = 1;
            }else{
                votesCount += (votes[voteIdx] == candidate ? 1 : -1);
            }
        }
        return candidate;
    }

    static constexpr int skSamplesSize{1000};
    int randomApproach(vector<int>& nums){
        // if(nums.size() <= skSamplesSize){
        //     return sortAndCountApproach(nums);
        // }
        vector<int> samples(skSamplesSize);
        drawSamples(nums, samples);
        return sortAndCountApproach(samples);
    }

    void drawSamples(const vector<int>& nums, vector<int>& samples){
        for(int idx = 0; idx < samples.size(); idx++){
            int rIdx = randomIdx(0, nums.size() - 1);
            samples[idx] = nums[rIdx];
        }
    }

    int randomIdx(int leftIdx, int rightIdx){
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(leftIdx, rightIdx);
        return dist6(rng);
    }
};
