#https://leetcode.com/problems/interleaving-string
#note: the BT solution should work but it exceeds the time
#limit in leet code on one of the last tests. (passed 48/51 
# tests)
#tags: DP BT

class Solution:
    def isInterleave(self, s1: str, s2: str, s3: str) -> bool:
      return DPSolution().isInterleave(s1, s2, s3)
      #return BTSolution().isInterleave(s1, s2, s3)

class BTSolution:
    def isInterleave(self, s1: str, s2: str, s3: str) -> bool:
        if len(s3) == 0:
            if len(s1) == 0 and len(s2) == 0:
                return True #cool
            else:
                return False
        
        #here it's promissed len(s3) > 0
        
        #try to consume s1:
        if len(s1) > 0 and s3[0] == s1[0]:
            if(self.isInterleave(s1[1:], s2, s3[1:])):
                return True
        #try to consume s2.
        if len(s2) > 0 and s3[0] == s2[0]:
            if(self.isInterleave(s1, s2[1:], s3[1:])):
                return True
        #cannot consume
        return False

    
class DPSolution:
    def isInterleave(self, s1: str, s2: str, s3: str) -> bool:
        if len(s1) + len(s2) != len(s3):
            return False

        #dp[i][j] = whether s1[0:i], s2[0:j] interleaves s3[0:i+j]
        #dp[0][0] = True
        #dp[0][j] for j > 0 = dp[0][j - 1] and s1[j] == s3[j]
        #dp[i][0] for i > 0 = dp[i - 1][0] and s2[i] == s3[i]
        #dp[i][j] for i,j > 0 = dp[i - 1][j] and s1[i] == s3[i + j] or
        #                       dp[i][j - 1] and s2[j] == s3[i + j]
        #Note that s[0:0] is the empty string (for each string).
        dpTbl = [[False for col in range(len(s1) + 1)] for row in range(len(s2) + 1)]
        
        for rowIdx in range(len(dpTbl)):
            for colIdx in range(len(dpTbl[0])):
                s1CharIdx = colIdx - 1
                s2CharIdx = rowIdx - 1
                if rowIdx == colIdx == 0:
                    dpTbl[rowIdx][colIdx] = True
                elif rowIdx == 0: #don't use s2, only s1 
                    dpTbl[rowIdx][colIdx] =\
                          dpTbl[rowIdx][colIdx - 1] and\
                              s1[s1CharIdx] == s3[s1CharIdx]
                elif colIdx == 0: #don't use s1, only s2
                    dpTbl[rowIdx][colIdx] =\
                          dpTbl[rowIdx - 1][colIdx] and\
                              s2[s2CharIdx] == s3[s2CharIdx]
                else: #colIdx > 0 and rowIdx > 0
                    dpTbl[rowIdx][colIdx] =\
                          (dpTbl[rowIdx - 1][colIdx] and\
                            s2[s2CharIdx] == s3[s1CharIdx + s2CharIdx + 1])\
                            or (dpTbl[rowIdx][colIdx - 1] and\
                                 s1[s1CharIdx] == s3[s1CharIdx + s2CharIdx + 1]) 
                
        return dpTbl[len(s2)][len(s1)]
