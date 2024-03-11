/**
 * https://leetcode.com/problems/asteroid-collision
 * #stack #STACK
 */
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> asteroidStack;
        for(int idx = 0; idx < asteroids.size(); idx++){
            int currAsteroidSize = abs(asteroids[idx]);
            while(asteroidStack.size() > 0 && 
                  currAsteroidSize != 0 &&
                  (sign(asteroids[idx]) < 0 && sign(asteroidStack.back()) > 0)){
                
                int lastAsteroidSize = abs(asteroidStack.back());
                if(currAsteroidSize > lastAsteroidSize){
                    asteroidStack.pop_back();
                }else if(currAsteroidSize < lastAsteroidSize){
                    currAsteroidSize = 0;
                }else{
                    currAsteroidSize = 0;
                    asteroidStack.pop_back();
                }
            }

            if(currAsteroidSize != 0){
                asteroidStack.push_back(asteroids[idx]);
            }          
        }
        return asteroidStack;   
    }
private:
    int sign(int x){
        return x >= 0 ? 1 : -1;
    }
};
