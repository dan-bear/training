#https://leetcode.com/problems/median-of-two-sorted-arrays


class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        median = self.findMedianInList(nums1, nums2)
        if median == None:
           median =  self.findMedianInList(nums2, nums1)
        return median

    def findMedianInList(self, list, other_list) -> float:
        len_list = len(list)
        len_other_list = len(other_list)
        total_len = len_list + len_other_list
        start_idx = 0
        end_idx = len_list - 1
        search_idx = None
        after_median = total_len // 2
        idx_to_check_in_other = None
        
        while start_idx <= end_idx:
            
            search_idx = int((start_idx + end_idx) // 2)
            after_in_list = len_list - 1 - search_idx
            left_for_median =\
                None if after_median < after_in_list\
                else after_median - after_in_list
            idx_to_check_in_other =\
                None if left_for_median == None\
                or len_other_list < left_for_median\
                else len_other_list - left_for_median
            
            if left_for_median == None:
                #The number is too small.
                start_idx = search_idx + 1
            elif idx_to_check_in_other == None:
                #there are not enough numbers in
                #the other list, so more numbers
                #from the current list are needed,
                #it means a smaller number is needed
                #from this list.
                end_idx = search_idx - 1 
            elif idx_to_check_in_other == len_other_list:
                #the value is the median only if it's
                #greater-eq than all elements in the other
                #list.
                if len_other_list == 0 or list[search_idx] >= other_list[-1]:
                    break
                else: 
                    #the value is too small to be the median
                    start_idx = search_idx + 1
            else:
                right_cond =\
                    list[search_idx] <= other_list[idx_to_check_in_other]
                left_cond =\
                    idx_to_check_in_other == 0 or\
                    other_list[idx_to_check_in_other - 1] <= list[search_idx]
                if right_cond and left_cond:
                    #found the potential median, might need 
                    #its successor.
                    break
                elif right_cond: # and not left cond:
                    #there are more numbers greater than the
                    #candidate, so a bigger number is needed
                    start_idx = search_idx + 1
                else: # left_cond and not right cond
                    #too many numbers to the left, need
                    #a smaller number
                    end_idx = search_idx - 1

        res = None
        if start_idx > end_idx:
            res = None
        elif total_len % 2 == 1:
            res =  list[search_idx]
        else: #total_len % 2 == 0
            successor_in_list = \
                None if search_idx == len_list - 1\
                else list[search_idx + 1]
            successor_in_other =\
                None if len_other_list == 0\
                or list[search_idx] > other_list[-1]\
                else other_list[idx_to_check_in_other]
            successor =\
                self.optionalMin(successor_in_list, successor_in_other)
            res = float(list[search_idx] + successor) / 2
        
        return res

    
    def optionalMin(self, maybe_val_1, maybe_val_2):
        res = None
        if maybe_val_1 == None and maybe_val_2 == None:
            res = None
        elif maybe_val_1 == None:
            res =  maybe_val_2
        elif maybe_val_2 == None:
            res =  maybe_val_1
        else:
            res = min(maybe_val_1, maybe_val_2) 
        return res   
