/**
 * Knapsack problem:
 * implement the function:
 * int knapsack(int* weights, int* prices, int len, int maxCap)
 * where:
 * 1: weights is an array representing a set of weights:
 *    weights[0]...weights[len - 1]
 * 2: prices is an array representing the price attached to
 *    any weight: prices[0]...prices[len-1].
 * 3: len the length of both the weights ad prices arrays.
 * 4: maxCap - a maximal weight capacity cap.
 * The function calculates and returns the maximal price
 * that can be reached by picking elements from the arrays
 * such that their weights' sum does not cross the maximal
 * capacity bound.
 * 
 * Example1:
 * weights = [1, 2, 4]
 * prices =  [11, 22, 30]
 * maxCap = 4
 * So, the maximal price one can get without crossing the
 * maxCap is by picking the first and second elements.
 * 
 * Example2:
 * weights = [1, 2, 4]
 * prices = [10, 20, 31]
 * maxCap = 4
 * The maximal price one can get without crossing the maxCap
 * is by picking the last element.
 * 
 * Example3:
 * weights = [1, 2, 4]
 * prices = [10, 20, 31]
 * maxCap = 0
 * The maximal price one can get without crossing the maxCap
 * is by not picking any element.
 * 
 */
///SOLUTION:
int calcMax(int x, int y);
int knapsack(int* weights, int* prices, int len, int maxCap){
    if(maxCap == 0 || len == 0){
        return 0;
    }
    int priceWithCurrElem = 0;
    int priceWithoutCurrElem = 0;
    
    if(maxCap - weights[0] >= 0){
        priceWithCurrElem = prices[0] + knapsack(weights + 1,
                                                 prices + 1,
                                                 len - 1,
                                                 maxCap - weights[0]);
    }
    
    priceWithoutCurrElem +=
      knapsack(weights + 1, prices + 1, len - 1, maxCap);

    return calcMax(priceWithCurrElem, priceWithoutCurrElem);
}

int calcMax(int x, int y){
    return x > y ? x : y;
}
}
