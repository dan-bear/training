/**
 * https://leetcode.com/problems/decode-string
 * #stack #STACK #str #string #STR #STRING
 */
class Solution {
public:
    string decodeString(string s) {
        char rightBracket = ']';
        vector<char> stack;
        for(char& symbol : s){
            if(symbol != rightBracket){
                stack.push_back(symbol);
            }else{
                string addition = popStrFromStack(stack); 
                stack.pop_back();//remove the left-bracket.
                int reps = popRepsFromStack(stack);
                addition = concatenate(addition, reps);
                ///That's the most interesting part here.
                pushToStack(stack, addition);
            }                
        }
        string res = fromStackToStr(stack);
        return res;
    }
private:
    string popStrFromStack(vector<char>& stack){
        string res;
        while(isLetter(stack.back())){
            res.push_back(stack.back());
            stack.pop_back();   
        }
        reverse(res.begin(), res.end());
        return res;
    }

    int popRepsFromStack(vector<char>& stack){
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

    void pushToStack(vector<char>& stack, string addition){
        for(char& c : addition){
            stack.push_back(c);
        }
    }

    string fromStackToStr(const vector<char>& stack){
        return string(stack.begin(), stack.end());
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
