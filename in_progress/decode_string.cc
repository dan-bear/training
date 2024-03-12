//"3[z]2[2[y]pq4[2[jk]e1[f]]]ef"
//https://leetcode.com/problems/decode-string

class Solution {
public:
    string decodeString(string s) {
        char leftBracket = '[';
        char rightBracket = ']';
        vector<int> stack;
        string res;
        string addition;
        for(char& symbol : s){
            if(symbol != rightBracket){
                if(isLetter(symbol) && stack.empty()){
                     res += symbol;
                }else{
                    stack.push_back(symbol);
                }
            }else{
                string addition = popStrFromStack(stack) + addition;
                cout << "addition " << addition << "\n";
                stack.pop_back();//remove the left-bracket.
                int reps = popRepsFromStack(stack);
                cout << "reps " << reps << "\n";
                addition = concatenate(addition, reps);
                cout << "addition " << addition << "\n";
                if(stack.empty()){
                     res += addition;
                     addition = "";
                     
                }
                cout << "res " << res << "\n";
            }                
        }
        return res;
    }
private:
    string popStrFromStack(vector<int>& stack){
        string res;
        while(isLetter(stack.back())){
            res.push_back(stack.back());
            stack.pop_back();   
        }
        reverse(res.begin(), res.end());
        return res;
    }

    int popRepsFromStack(vector<int>& stack){
        int reps = 0;
        int tenPower = 1;
        while(!stack.empty() && isDigit(stack.back())){
            reps += (toDigit(stack.back()) * tenPower);
            tenPower *= 10;
            stack.pop_back();
        }
        return reps;
    }

    string concatenate(const string& s, int reps){
        string res;
        for(int rep = 1; rep <= reps; rep++){
            res += s;
        }
        return res;
    }

    bool isLetter(char c){
        return (c >= 'a' && c <= 'z');
    }
    
    bool isDigit(char c){
        return c >= '0' && c <= '9';
    }
   
    int toDigit(char asciiDigit){
        return static_cast<int>(asciiDigit - '0');
    }
};
