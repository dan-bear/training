# https://leetcode.com/problems/powx-n/
# #recursion #log(n)
class Solution:
    
    def myPow(self, x: float, n: int) -> float:
        return self.recursiveMyPow(x, n)
        #return self.iterativeMyPow(x, n)

    def iterativeMyPow(self, x: float, n: int) -> float:
        if n == 0:
            return 1
        
        absN = n if n > 0 else -1 * n
        res = 1
        while absN > 0:
            if absN % 2 == 0:
                x *= x
                absN //= 2
            else:
                res *= x
                absN -= 1
        
        ## Another approach that I personally find more
        ## intuitive.
        # step = 1
        # while step < absN:
        #     if step * 2 <= absN:
        #         res *= res
        #         step *= 2
        #     else:
        #         res *= x
        #         step += 1

        res = res if n > 0 else 1 / res
        return res


    def recursiveMyPow(self, x: float, n: int) -> float:
        absN = n if n > 0 else -1 * n
        res = self.myPowAux(x, absN)
        res = res if n > 0 else 1/res
        return res
        
    def myPowAux(self, x: float, nonNegativeN: int):
        if nonNegativeN == 0:
            return 1
        if nonNegativeN % 2 == 0:
            res = self.myPowAux(x, nonNegativeN / 2)
            return res * res
        else:
            return x * self.myPowAux(x, nonNegativeN - 1)
