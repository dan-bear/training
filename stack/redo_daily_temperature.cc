/**
 * https://leetcode.com/problems/daily-temperatures
 * #stack #array #iteration #monotonic_stack
 */
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        //return noStackDailyTemperatures(vector<int>& temperatures);
        return stackDailyTemperatures(temperatures);
    }
    

private:
    /**
     * 40 30 20 50 60
     * idx = 0 push 0 to stack.
     * idx = 1 push 1 to stack
     * idx = 2 push 2 to stack
     * idx = 3 top stack, get 2 and write (3 - 2) in res[2], pop stack
     *         top stack, get 1 and write (3 - 1) in res[1], pop stack
     *         top stack, get 0 and write (3 - 0) in res[0], pop stack
     *         push 3 to stack
     * idx = 4 top stack, get 3 and write (4 - 3) in res[3], pop stack
     *         push 4 to stack.
     * 
     */
    vector<int> stackDailyTemperatures(vector<int>& temps){
        vector<int> res(temps.size(), 0);
        stack<int> idxStack;
        for(int tempIdx = 0; tempIdx < temps.size(); tempIdx++){
            while(!idxStack.empty() && temps[idxStack.top()] < temps[tempIdx]){
                res[idxStack.top()] = tempIdx - idxStack.top();
                idxStack.pop();
            }
            idxStack.push(tempIdx);
        }
        return res;
    }

    vector<int> noStackDailyTemperatures(vector<int>& temperatures) {
        int tempSize = temperatures.size();
        vector<int> res(tempSize, 0);
        for(int idx = tempSize - 2; idx >= 0; idx--){
            if(temperatures[idx] < temperatures[idx + 1]){
                res[idx] = 1;
            }else{
                int warmerDayIdx = searchWarmerDay(temperatures, res, idx);
                res[idx] = warmerDayIdx > idx ? warmerDayIdx - idx : 0;
            }
        }
        return res;
    }

    int searchWarmerDay(const vector<int>& temperatures, 
                        const vector<int>& res,
                        int idx){
        int currIdx = idx + 1;
        while(currIdx < res.size() && 
              temperatures[idx] >= temperatures[currIdx] &&
              res[currIdx] != 0){
              currIdx += res[currIdx];
        }
        int warmerDayIdx = currIdx;
        if(currIdx == res.size() || temperatures[idx] >= temperatures[currIdx]){
            warmerDayIdx = -1;
        }
        return warmerDayIdx;
    }
};
