

/**
 * Implement the function int* allocateAndFillArray(int len)
 * The function allocates an integer array of lengh len and
 * fill its cells with the values 0, 1, 2,..., len - 1 (i.e.
 * the i'th element = i.
 * The function returns the allocated array to the user and
 * DOES NOT FREE THE MEMORY!
 * See usage example:
 */
#include <stdlib.h>
#include <stdio.h>

int* allocatedAndFillArray(int len);
int main(){
    int lastNumber;
    printf("Hey Kama till what number do you want me to print?\n");
    scanf("%d", &lastNumber);/// remember &x is the address of x,
                             /// so now we know the second parameter
                             /// of scanf is a pointer!
    int* pArrWithNums = allocateAndFillArray(lastNumber + 1);
    for(int idx = 0; idx < lastNumber + 1; idx++){
        printf("%d ", pArrWithNums[idx]);
    }
    printf("\n");
    /// main() asked for allocation, so main() will free the memory.
    free(pArrWithNums);
}


//SOLUTION:
int* allocatedAndFillArray(int len){
    /// Note: Make sure you understand the need for casting!
    /// since malloc() returns void* but we need int*.
    int* pArr = (int*)malloc(len * sizeof(int));
    for(int idx = 0; idx < len; idx++){
        pArr[idx] = idx;
        //Note: make sure your understand that the next
        //syntax does the same thing!
        // *(pArr + idx) = idx;
    }
    return pArr;
}
