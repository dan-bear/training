# https://leetcode.com/problems/kth-largest-element-in-an-array/
# #heap #max-heap #min-heap

import heapq
class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        return self.minHeapFindKthLargest(nums, k)
        #return self.maxHeapFindKthLargest(nums, k)
        
    def maxHeapFindKthLargest(self, nums: List[int], k: int) -> int:
        heap = []
        for num in nums:
            heappush(heap, -1*num)
        for _ in range(k - 1):
            heappop(heap)
        return -1*heap[0]
        
        #note: another option is:
        # heapq.heapify(nums)
        # heapq._heapify_max(nums)
        # for _ in range(k - 1):
        #     heapq._heappop_max(nums)
        # return nums[0]


    def minHeapFindKthLargest(self, nums: List[int], k: int) -> int:
        heapq.heapify(nums)
        for _ in range(len(nums) - k):
            heappop(nums)
        return nums[0]
