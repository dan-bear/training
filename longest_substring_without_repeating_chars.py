# Link: https://leetcode.com/problems/longest-substring-without-repeating-characters/
# Name: longest substring without repeating characters.

class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        #return SlowSolution().lengthOfLongestSubstring()
        return MovingWindowSolution().lengthOfLongestSubstring(s)


class MovingWindowSolution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        res = 0
        number_of_ascii_chars = pow(2,8)
        hist = [0 for char in range(number_of_ascii_chars)]
        window_size = 0
        current_idx = 0
        str_len = len(s)
        while current_idx < str_len:
            if hist[ord(s[current_idx])] == 0:
                hist[ord(s[current_idx])] = 1
                window_size += 1
                #update the result.
                res = max(res, window_size)
            else:
                window_size = self.cleanHistAndCalcNewWindowSize(s, current_idx, window_size, hist)

            current_idx += 1 
        
        return res

    def cleanHistAndCalcNewWindowSize(self, s, current_idx, window_size, hist):
        clean_idx = current_idx - window_size
        reoccured_char = s[current_idx]
        while s[clean_idx] != reoccured_char:
            hist[ord(s[clean_idx])] = 0 #clean.
            window_size -= 1
            clean_idx += 1
            # no need to update the window size after
            # the while loop, since current_idx is
            # going to be increased and include the
            # reoccured char.
        return window_size    


# len(s)^2 time.
# O(1) space complexity
class SlowSolution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        max_len = 0
        current_len = 0
        str_len = len(s)
        for char_idx in range(str_len):
            current_len = self.lengthOfLongestSubstringFromCharIdx(s, char_idx)
            if current_len > max_len:
                max_len = current_len
        
        return max_len
    
    def lengthOfLongestSubstringFromCharIdx(self, s: str, char_idx : int) -> int:
        num_of_ascii_chars = pow(2,8) #8 bits ascii.
        histogram = [0 for idx in range(num_of_ascii_chars)]
        length = 0
        str_len = len(s)
        while char_idx < str_len:
            histogram[ord(s[char_idx])] += 1
            if histogram[ord(s[char_idx])] > 1:
                break
            length += 1
            char_idx += 1
        
        return length
