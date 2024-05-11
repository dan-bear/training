///-----------------------------------------------------------------------------
/**
 * What's the difference between pointer and reference?
 * 1: Pointer is just a variable holding a typed or untyped 
 *    memory address.
 * 2: Reference - is more restricted (less powerfull) by safer pointer.
 *     2.1: Reference rules:
 *         - Impossible to build levels of indirection, the reference cannot
 *           be referenced (like pointer to pointer) any reference to the
 *           reference just changes the data.
 *         - Impossible to update what the reference is referencing. The 
 *           referenec itself is immutable.
 *         - No null reference, there is no concept of referencing nothing.
 *         - Reference cannot be uninitialized - "int& val" leads to compiler
 *           error.
 *     2.3: Reference technique:
 *         - Using the address-of operator with a reference-variable gives 
 *           the address of the references variable.
 *         - dereferncing a pointer to create a refernce:
 *               int val = 0;
 *               int* pVal = &val;
 *               int& rVal = *pVal; ///rVal becomes a reference to val.
 *         - In general it's possible to implement reference using pointers
 *           which are implicitly dereferenced at each use.
 */

/** Const and reference. */
int main(){
    int mutBal = 5;
    const int immutBal = 7;
    int& rMutBal = mutBal; ///reference to mutable int.
    const int& rImmutBal = immutBal; ///reference to const int.
    ///Note: "int const& rImmutBal = immutBal" 
    ///      Is also a valid syntax as a reference to const int, 
    ///      but it's rarely used.
    ///There is no need for const referece to int syntax: "int& const"
    ///since references are immutable by definition!.
    return 0;
}




