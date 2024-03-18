# https://leetcode.com/problems/merge-sorted-array/
# #array #merge #sort
# #meta
class Solution:
    def merge(self, nums1: List[int], m: int, nums2: List[int], n: int) -> None:
        """
        Do not return anything, modify nums1 in-place instead.
        """
        #self.mergeWithSpace(nums1, m, nums2, n)
        self.mergeInPlace(nums1, m, nums2, n)
        

    def mergeInPlace(self, nums1: List[int], len1: int, nums2: List[int], len2: int):
        #working in the opposite direction allows to avoid additioal memory. 
        idx1 = len1 - 1
        idx2 = len2 - 1
        mergeIdx = len1 + len2 - 1
        mergeSpace = nums1
        while idx1 >= 0 and idx2 >= 0:
            if nums1[idx1] >= nums2[idx2]:
                mergeSpace[mergeIdx] = nums1[idx1]
                idx1 -= 1
            else:
                mergeSpace[mergeIdx] = nums2[idx2]
                idx2 -= 1

            mergeIdx -= 1

        reminderIdx = idx1 if idx1 >= 0 else idx2
        reminderList = nums1 if idx1 >= 0 else nums2

        while reminderIdx >= 0:
            mergeSpace[mergeIdx] = reminderList[reminderIdx]
            reminderIdx -= 1
            mergeIdx -= 1
            

    def mergeWithSpace(self,\
                       nums1: List[int],\
                       len1: int,\
                       nums2: List[int],\
                       len2: int):
        
        mergeSpace = nums1
        nums1 = nums1[0 : len1]
        idx1 = 0
        idx2 = 0
        mergeSpaceIdx = 0
        while idx1 < len1 and idx2 < len2:
            if nums1[idx1] <= nums2[idx2]:
                mergeSpace[mergeSpaceIdx] = nums1[idx1]
                idx1 += 1
            else:
                mergeSpace[mergeSpaceIdx] = nums2[idx2]
                idx2 += 1

            mergeSpaceIdx += 1
        
        reminderIdx = idx1 if idx1 < len1 else idx2
        reminderLen = len1 if idx1 < len1 else len2
        reminderList = nums1 if idx1 < len1 else nums2

        while reminderIdx < reminderLen:
            mergeSpace[mergeSpaceIdx] = reminderList[reminderIdx]
            reminderIdx += 1
            mergeSpaceIdx += 1
