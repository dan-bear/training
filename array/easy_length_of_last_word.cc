/**
 * https://leetcode.com/problems/length-of-last-word
 * #string  
 */
class Solution {
private:
    static constexpr char skSpace = ' ';
public:
    int lengthOfLastWord(string s) {
        int len = 0;
        for(auto itr = s.rbegin(); itr != s.rend(); itr++){
            if(*itr != skSpace){
                len += 1;
            }else{
                if(len > 0){
                    ///At least one letter was found and
                    ///a space is reached
                    break;
                }
            }
        }
        return len;
    }
};
