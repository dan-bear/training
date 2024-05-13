///https://medium.com/geekculture/c-inheritance-memory-model-eac9eb9c56b5
/**
 * The data members are layout with respect to the 
 * inheritance order. If Cn <- Cn-1 <- ... <- C1 <- C0
 * Cn instance data layout is:
 * |C0 members |C1 members|...|Cn members|
 * And a pointer to Cn instance holds the address 
 * where the first C0 members is stored.
 * This chararteristic allows to hold a static pointer
 * of type C0 to a dynamic variable of type Cn.
 * '''
 * int main(){
 *     C0 *pCo = new Cn;
 *     ...
 * }
 * '''
 *
 * When virtual inheritance is involved a virtual table
 * is used to determine which function to call.
 * The memory layout of Cn is:
 * |vtable_ptr|C0 members|...|Cn members|
 * The virtual table holds pointer to functions, this way
 * the correct implementation can be calle for Cn versions
 * (due to override option).
 * In order to hold static-base-pointer to dynamic-derived-instance
 * the order of the functions in the vtables have to correspond.
 *
 */
