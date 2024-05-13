#include <iostream>
#include <vector>
#include <ranges>
using namespace std;

void printInt(int val){
    cout << val << "\n";
}

class VectorExample{
public:
    void example(){
        ///Allocate a vector explicitly.
        vector<int> vec1 = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
        ///Allocate a vector of given size
        vector<int> vec2(10);
        ///Allocate a vector of a given size and given value
        vector<int> vec3(10, 31415);
        ///Get the last element in the vector.
        printInt(vec1.back());
        ///Sort a vector:
        ///using the ranges library.
        ranges.sort(vec1);
        ///using std sort.
        sort(vec2.begin(), vec2.end());
        ///using std sort with lambda function as compare function.
        sort(vec2.begin(), vec2.end(), [](int& val1, int& val2){return val1 < val2;});


        ///reverse iterators
        printInt(vec1.rbegin()[0]);///gets last element.
        printInt(vec1.rbegin()[1]);///gets one before last element.
        for(vector<int>::reverse_iterator rItr = vec2.rbegin();
            rItr != vec2.rend(); rItr++){
            cout << *rItr << "\n";
        }
    }  

private:
};



