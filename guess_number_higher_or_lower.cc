/**
 * https://leetcode.com/problems/guess-number-higher-or-lower
 * #binary search 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */

class Solution {
public:
    int guessNumber(int n) {
        unsigned int left = 0;
        unsigned int right = static_cast<unsigned int>(n);
        unsigned int mid = (right + left) / 2;
        int guessRes = guess(static_cast<int>(mid));
        while(guessRes != 0){
            if(guessRes < 0){
                right = mid - 1;
            }else{
                left = mid + 1;
            }
            mid = (right + left) / 2;
            guessRes = guess(static_cast<int>(mid));
        }
        return static_cast<int>(mid);
    }
};
