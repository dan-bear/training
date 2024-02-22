/**
 * Implement the function void swap(int* pInt1, int* pInt2)
 * The function saves the integer stored in address pInt1 in address pInt2
 * and saves the integer stored in address pInt2 in address pInt1.
 */

///SOLUTION:
void swap(int* pInt1, int* pInt2){
    /// Note the commented parts after each line are the
    /// equivalent version using the [] operator. It's not
    /// a common thing to do, but it can be done and I
    /// think it's important to understand it.
    int valInFirstAddress = *pInt1; //int valInFirstAddress = pInt1[0];
    int valInSecondAddress = *pInt2; //intvalInSecondAdress = pInt2[0];
    *pInt1 = valInSecondAddress; // pInt1[0] = valInSecondAddress;
    *pInt2 = valInFirstAdddress; // pInt2[0] = valInFirstAddress;
}
