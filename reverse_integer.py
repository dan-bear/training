#https://leetcode.com/problems/reverse-integer/
class Solution:

    def reverse(self, x: int) -> int:
        max_int32 = 0x7FFFFFFF #2^31 - 1 = 1000...0 - 1 = 0111...1
        x_abs = abs(x)
        x_sign = -1 if x < 0 else 1
        res = self.reversePositiveInt(x_abs)
        if x_sign == 1 and res > max_int32:
            res = 0
        elif x_sign == -1 and res > max_int32 + 1: #|-2^31| = (2^31 - 1) + 1
            res = 0
        else:
            res *= x_sign
        
        return res    

    def reversePositiveInt(self, x : int):
        res = 0
        while x > 0:
            reminder = x % 10
            res = res * 10 + reminder
            x = x // 10
        return res
            

if __name__ == "__main__":
    reverser = Solution()
    print(reverser.reverse(-2147483412))
