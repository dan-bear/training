/**
 * https://leetcode.com/problems/dota2-senate
 * #queue
 */
class Solution {
public:
    ///right1: ban one senator's right. (kill a another senator.)
    ///right2: if all the left senators are from the same party,
    ///        victory can be announced.
    ///
    string predictPartyVictory(string senate) {
        queue<int> dIdxs;
        queue<int> rIdxs;
        fillIdxQueus(senate, dIdxs, rIdxs);
        
        while(!dIdxs.empty() && !rIdxs.empty()){
            if(dIdxs.front() < rIdxs.front()){
                rIdxs.pop();
                dIdxs.push(dIdxs.front() + senate.length());
                dIdxs.pop();
            }else{
                dIdxs.pop();
                rIdxs.push(rIdxs.front() + senate.length());
                rIdxs.pop();
            }
        }
        string res = rIdxs.empty() ? string("Dire") : string("Radiant");
        return res;
    }
private:
    void fillIdxQueus(const string& senate, queue<int>& dIdxs, queue<int>& rIdxs){
        for(int idx = 0; idx < senate.length(); idx++){
            if(senate[idx] == 'D'){
                dIdxs.push(idx);
            }else{
                rIdxs.push(idx);
            }
        }
    }
};
