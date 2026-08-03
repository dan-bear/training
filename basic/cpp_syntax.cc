#include <string>
#include <ranges>
// backword iteration on a string
void backwardStrIterator(str string){
    // using views and ranges - from cpp20
    for(char c : str | std::views::reverse) {
        // do something with c
    }
    // index based
    for(int idx = str.size() - 1; idx >= 0; idx--){
        char c = str[idx];
    }
    //with iterators
    for(std::reverse_iterator<std::string::iterator> itr = s.rbegin(); itr != s.rend(); ++itr){
        // note could use auto itr in modern versions
        char c = *itr;
    }
}
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
