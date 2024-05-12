https://stackoverflow.com/questions/367633/what-are-all-the-common-undefined-behaviours-that-a-c-programmer-should-know-a

#include <iostream>

using namespace std;
/**
 * Dereferencing a nullptr. 
 */
void case1{
    int* ptrToNull = nullptr;
    int x = *ptrToNull; //undefined behaviour.
    cout << x << "\n";
}

/**
 * Dereferencing a pointer returned by a "new" allocation
 * of a zero size.
 */
void case2{
    ///new int[0] is legal, it allocate an int "c-array" of
    ///size 0, so it's a zero-size allocation.
    ///Dereferencing it leads to undefined behaviour.
    cout << *(new int[0]) << "\n;
}

https://stackoverflow.com/questions/12092933/calling-virtual-function-from-destructor
void case3{
    
}







