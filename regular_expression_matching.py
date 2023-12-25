#https://leetcode.com/problems/regular-expression-matching
#backtracking solution.
class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        pLen = len(p)
        sLen = len(s)
        if pLen == 0 and sLen == 0:
            return True
        if pLen == 0 and sLen > 0:
            return False
        
        if pLen == 1 or p[1] != '*':
            if sLen == 0:
                return False
            if s[0] == p[0] or p[0] == '.':
                #move on recursively.
                return self.isMatch(s[1:], p[1:])
            else:
                return False
        
        assert p[1] == '*'
        #Now for the hard part, p[1] == '*'
        maxCharsToConsume = 0
        if p[0] == '.': #.* pattern
            maxCharsToConsume = sLen
        else:
            while maxCharsToConsume < sLen and p[0] == s[maxCharsToConsume]:
                maxCharsToConsume += 1
        
        for charsToConsum in range(0, maxCharsToConsume + 1):
            if(self.isMatch(s[0 + charsToConsum:], p[2:])):
                return True
        
        return False
        
    
