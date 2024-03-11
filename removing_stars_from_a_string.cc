/**
 * https://leetcode.com/problems/removing-stars-from-a-string
 * #stack #string #STACK #STRING #STR #str
 */
class Solution {
public:
    string removeStars(string s) {
        string stackStr;
        char star = '*';
        for(int charIdx = 0; charIdx < s.length(); charIdx++){
            if(s[charIdx] == star){
                stackStr.pop_back();
            }else{
                stackStr.push_back(s[charIdx]);
            }
        }
        return stackStr;    
    }
};
