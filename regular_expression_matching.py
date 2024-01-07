#https://leetcode.com/problems/regular-expression-matching

class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        solver = DPSolution()
        #solver = ExplainatoryDPSolution()
        #solver = BTSolution()
        return solver.isMatch(s, p)    

#A hard to read dp solution (see more explanatory after).
class DPSolution:
    kAsterisk = '*'
    kDot = '.'

    def isMatch(self, s: str, p: str) -> bool:
        res = False
        dpTbl = [[False for col in range(len(s) + 1)] for row in range(len(p) + 1)]
        self.fillDpTbl(s, p, dpTbl)
        res = dpTbl[len(p)][len(s)]
        return res

    def fillDpTbl(self, s, p , dpTbl):
          
        for pIdx in range(-1,len(p)):
            for sIdx in range(-1, len(s)):
                dpRowIdx = pIdx + 1
                dpColIdx = sIdx + 1
                
                if pIdx < 0 and sIdx < 0:
                    dpTbl[dpRowIdx][dpColIdx] = True
                elif pIdx < 0 and sIdx >= 0:
                    dpTbl[dpRowIdx][dpColIdx] = False
                elif pIdx >= 0 and sIdx < 0:
                    #in practice, that's what catches the empty string case.
                    if p[pIdx] == self.kAsterisk and dpTbl[dpRowIdx - 2][dpColIdx]:
                        dpTbl[dpRowIdx][dpColIdx] = True
                else: #pIdx >= 0 and sIdx >= 0
                    if p[pIdx] == self.kDot or p[pIdx] == s[sIdx]:
                        if dpTbl[dpRowIdx - 1][dpColIdx - 1]:
                            dpTbl[dpRowIdx][dpColIdx] = True
                    elif p[pIdx] == self.kAsterisk:
                        #try not to use the asterisk
                        if dpRowIdx >= 2 and dpTbl[dpRowIdx - 2][dpColIdx]:
                            dpTbl[dpRowIdx][dpColIdx] = True
                        #try to use it:
                        elif p[pIdx - 1] == self.kDot or p[pIdx - 1] == s[sIdx]:
                            #try use p[pIdx - 1] if for the first time:
                            if dpRowIdx >= 2 and dpTbl[dpRowIdx - 2][dpColIdx - 1]:
                                dpTbl[dpRowIdx][dpColIdx] = True
                            #use p[pIdx - 1] again
                            if dpTbl[dpRowIdx][dpColIdx - 1]:
                                dpTbl[dpRowIdx][dpColIdx] = True




#A dp solution that is more explanatory, but demands some
#edge case adjustments and auxilery functions.
class ExplainatoryDPSolution:
    asterisk = '*'
    dot = '.'

    def isMatch(self, s: str, p: str) -> bool:
        res = False
        
        if len(s) == 0 or len(p) == 0:
            res = self.testEmptyStrings(s, p)
        else:
            dpTbl = [[False for col in range(len(s))] for row in range(len(p))]
            self.fillDpTbl(s, p, dpTbl)
            res = dpTbl[len(p) - 1][len(s) - 1]
            
        return res


    def testEmptyStrings(self, s, p):
        sLen = len(s)
        pLen = len(p)            
        res = False

        #start
        if sLen == 0 and pLen == 0:
            #both strings are empty
            res = True
    
        elif pLen > 0: # and sLen == 0
            #If p matches an empty string it's fine.
            res = self.pMatchEmptyString(p)

        #else: sLen > 0 and pLen == 0, p cannot match s.             
        return res 

    def pMatchEmptyString(self, p):
        

        bRes = True
        if len(p) % 2 == 1:
            bRes = False
        elif len(p) > 0:
            for idx in range(1, len(p), 2):
                if p[idx] != DPSolution.asterisk:
                    bRes = False
                    break
        
        return bRes


    def fillDpTbl(self, s, p , dpTbl):
          
        for pIdx in range(len(p)):
            for sIdx in range(len(s)):

                if p[pIdx] == DPSolution.asterisk:
                    #Try not to use it at all:
                    if pIdx >= 2 and dpTbl[pIdx - 2][sIdx]:
                        dpTbl[pIdx][sIdx] = True
                    else:
                        #Try to use it if possible:
                        if p[pIdx - 1] == DPSolution.dot or p[pIdx - 1] == s[sIdx]:
                            #depends on previous results
                            if pIdx >= 2 and sIdx >= 1:
                                #use p[pIdx - 1] for the first time?
                                if dpTbl[pIdx - 2][sIdx - 1]:
                                    dpTbl[pIdx][sIdx] = True
                                #use p[pIdx - 1] again:
                                elif dpTbl[pIdx][sIdx - 1]:
                                    dpTbl[pIdx][sIdx] = True
                            #No previous results p[0...pIdx-1]
                            #matches an empty string:
                            if self.pMatchEmptyString(p[0:pIdx - 1]):
                                if sIdx == 0:
                                    #use p[pIdx] for the first time.
                                    dpTbl[pIdx][sIdx] = True
                                else: #sIdx > 0:
                                    #use p[pIdx] again:
                                    if dpTbl[pIdx][sIdx - 1]:
                                        dpTbl[pIdx][sIdx] = True 

                        
                if p[pIdx] == s[sIdx] or p[pIdx] == DPSolution.dot:
                    #it's possible that p[0...pIdx - 1] matches the
                    #empty string, thus, p[0...pIdx] matches s[0].
                    if sIdx == 0 and self.pMatchEmptyString(p[0: pIdx]):
                        dpTbl[pIdx][sIdx] = True
                    elif pIdx > 0 and sIdx > 0 and dpTbl[pIdx - 1][sIdx - 1]:
                        dpTbl[pIdx][sIdx] = True



#backtracking solution.
class BTSolution:
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
        
    
